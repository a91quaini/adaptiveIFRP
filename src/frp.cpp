// Author: Alberto Quaini

#include "frp.h"
#include "hac_covariance.h"
#include "gkr_factor_screening.h"

/////////////////
///// FRPCpp ////

Rcpp::List FRPCpp(
  const arma::mat& returns,
  const arma::mat& factors,
  const bool misspecification_robust,
  const bool include_standard_errors,
  const bool hac_prewhite,
  const double target_level_gkr2014_screening
) {

  // If target_level_gkr2014_screening > 0, perform the GKR screening procedure
  if (target_level_gkr2014_screening > 0.) {

    // Store the indices of the selected factors
    const arma::uvec selected_factor_indices = static_cast<arma::uvec>(
      GKRFactorScreeningCpp(
        returns,
        factors,
        target_level_gkr2014_screening,
        hac_prewhite
      )["selected_factor_indices"]
    );

    // If the GKR procedure removed all the factors, return a list containing empty vectors.
    if (selected_factor_indices.empty()) return include_standard_errors ?
      Rcpp::List::create(
        Rcpp::Named("risk_premia") = arma::vec(),
        Rcpp::Named("standard_errors") = arma::vec(),
        Rcpp::Named("selected_factor_indices") = selected_factor_indices
      ) :
      Rcpp::List::create(
        Rcpp::Named("risk_premia") = arma::vec(),
        Rcpp::Named("selected_factor_indices") = selected_factor_indices
      );

    // Store the potentially new factors
    const arma::mat factors_new = factors.cols(selected_factor_indices);

    // return list of results, with selected factor indices
    return ReturnFRPCpp(
      returns,
      factors_new,
      misspecification_robust,
      include_standard_errors,
      hac_prewhite,
      selected_factor_indices
    );

  }

  // Otherwise, return list of results without selected factor indices
  return ReturnFRPCpp(
    returns,
    factors,
    misspecification_robust,
    include_standard_errors,
    hac_prewhite
  );

}

////////////////////////
////// ReturnFRPCpp ////

Rcpp::List ReturnFRPCpp(
  const arma::mat& returns,
  const arma::mat& factors,
  const bool misspecification_robust,
  const bool include_standard_errors,
  const bool hac_prewhite,
  const arma::uvec selected_factor_indices
) {

  // Check if standard errors are to be included in the calculation
  if (include_standard_errors) {

    // Compute covariance matrices and mean returns
    const arma::mat covariance_factors_returns = arma::cov(factors, returns);
    const arma::mat variance_returns = arma::cov(returns);
    const arma::vec mean_returns = arma::mean(returns).t();

    // Solve for beta coefficients
    const arma::mat beta = arma::solve(
      arma::cov(factors),
      covariance_factors_returns,
      arma::solve_opts::likely_sympd
    ).t();

    // Compute risk premia based on whether misspecification is robust or not
    const arma::vec frp = misspecification_robust ?
    KRSFRPCpp(beta, mean_returns, variance_returns) :
      FMFRPCpp(beta, mean_returns);

    // Return risk premia and standard errors in a list
    return selected_factor_indices.empty() ?
      Rcpp::List::create(
        Rcpp::Named("risk_premia") =  frp,
        Rcpp::Named("standard_errors") = misspecification_robust ?
          StandardErrorsKRSFRPCpp(
            frp,
            returns,
            factors,
            beta,
            covariance_factors_returns,
            variance_returns,
            mean_returns,
            hac_prewhite
          ) :
          StandardErrorsFRPCpp(
            frp,
            returns,
            factors,
            beta,
            covariance_factors_returns,
            variance_returns,
            mean_returns,
            hac_prewhite
          )
      ) :
      Rcpp::List::create(
        Rcpp::Named("risk_premia") =  frp,
        Rcpp::Named("standard_errors") = misspecification_robust ?
          StandardErrorsKRSFRPCpp(
            frp,
            returns,
            factors,
            beta,
            covariance_factors_returns,
            variance_returns,
            mean_returns,
            hac_prewhite
          ) :
          StandardErrorsFRPCpp(
            frp,
            returns,
            factors,
            beta,
            covariance_factors_returns,
            variance_returns,
            mean_returns,
            hac_prewhite
          ),
        Rcpp::Named("selected_factor_indices") = selected_factor_indices
    );

  } else {

    // Solve for beta coefficients when standard errors are not included
    const arma::mat beta = arma::solve(
      arma::cov(factors),
      arma::cov(factors, returns),
      arma::solve_opts::likely_sympd
    ).t();

    // Return risk premia only in a list
    return selected_factor_indices.empty() ?
      Rcpp::List::create(
        Rcpp::Named("risk_premia") = misspecification_robust ?
          KRSFRPCpp(beta, arma::mean(returns).t(), arma::cov(returns)) :
          FMFRPCpp(beta, arma::mean(returns).t())
      ) :
      Rcpp::List::create(
        Rcpp::Named("risk_premia") = misspecification_robust ?
          KRSFRPCpp(beta, arma::mean(returns).t(), arma::cov(returns)) :
          FMFRPCpp(beta, arma::mean(returns).t()),
        Rcpp::Named("selected_factor_indices") = selected_factor_indices
    );

  }

}

////////////////////
////// FMFRPCpp ////

arma::vec FMFRPCpp(
  const arma::mat& beta,
  const arma::vec& mean_returns
) {

  // Solve for risk premia using Fama-MacBeth method
  return arma::solve(
    beta.t() * beta,
    beta.t(),
    arma::solve_opts::likely_sympd) * mean_returns;

}

////////////////////
///// KRSFRPCpp ////

arma::vec KRSFRPCpp(
  const arma::mat& beta,
  const arma::vec& mean_returns,
  const arma::mat& weighting_matrix
) {

  // Solve for beta coefficients with the weighting matrix
  const arma::mat beta_t_wei_mat_inv = arma::solve(
    weighting_matrix,
    beta,
    arma::solve_opts::likely_sympd
  ).t();

  // Compute risk premia using Kan-Robotti-Shanken method
  return arma::solve(
    beta_t_wei_mat_inv * beta,
    beta_t_wei_mat_inv,
    arma::solve_opts::likely_sympd
  ) * mean_returns;

}

///////////////////////////////
///// StandardErrorsFRPCpp ////

arma::vec StandardErrorsFRPCpp(
  const arma::vec& frp,
  const arma::mat& returns,
  const arma::mat& factors,
  const arma::mat& beta,
  const arma::mat& covariance_factors_returns,
  const arma::mat& variance_returns,
  const arma::vec& mean_returns,
  const bool hac_prewhite
) {

  // Compute the matrix H as the inverse of beta' * beta
  const arma::mat h_matrix  = arma::inv_sympd(beta.t() * beta);

  // Compute matrix A used in the standard error calculation
  const arma::mat a_matrix = h_matrix * beta.t();

  // Center the returns and factors
  const arma::mat returns_centred = returns.each_row() - mean_returns.t();
  const arma::vec mean_factors = arma::mean(factors).t();
  const arma::mat factors_centred = factors.each_row() - mean_factors.t();

  // Intermediate matrices for standard error calculation
  const arma::mat gamma = returns_centred * a_matrix.t();
  const arma::vec gamma_true = a_matrix * mean_returns;
  const arma::mat phi = gamma - factors;
  const arma::mat phi_centred = phi.each_row() - (gamma_true - mean_factors).t();

  // Compute variance of factors and solve for fac_centred_var_fac_inv
  const arma::mat variance_factors = arma::cov(factors);
  const arma::mat fac_centred_var_fac_inv = arma::solve(
    variance_factors,
    factors_centred.t(),
    arma::solve_opts::likely_sympd
  ).t();

  // Compute matrix Z used in standard error calculation
  const arma::mat z = fac_centred_var_fac_inv.each_col() % (
    returns_centred * (mean_returns - beta * frp)
  );

  arma::mat series =
    // mean term
    (gamma.each_row() - (a_matrix * mean_returns).t()) -
    // beta term
    phi_centred.each_col() % (factors_centred * arma::solve(
        variance_factors,
        gamma_true,
        arma::solve_opts::likely_sympd
    )) +
    // error term
    (fac_centred_var_fac_inv.each_col() % (
        returns_centred * (mean_returns - beta * frp)
    )) * h_matrix;

  // Return the HAC standard errors of the estimator
  return HACStandardErrorsCpp(series, hac_prewhite) /
    std::sqrt(static_cast<double>(returns.n_rows));

}

//////////////////////////////////
///// StandardErrorsKRSFRPCpp ////

arma::vec StandardErrorsKRSFRPCpp(
  const arma::vec& krs_frp,
  const arma::mat& returns,
  const arma::mat& factors,
  const arma::mat& beta,
  const arma::mat& covariance_factors_returns,
  const arma::mat& variance_returns,
  const arma::vec& mean_returns,
  const bool hac_prewhite
) {

  // Compute the inverse of variance_returns and useful matrices that use it
  const arma::mat var_ret_inv = arma::inv_sympd(variance_returns);
  const arma::mat var_ret_inv_beta = var_ret_inv * beta;
  const arma::vec var_ret_inv_mean_ret = var_ret_inv * mean_returns;

  // Compute matrix A used in the standard error calculation
  const arma::mat a_matrix = arma::solve(
    beta.t() * var_ret_inv_beta,
    var_ret_inv_beta.t(),
    arma::solve_opts::likely_sympd
  );

  // Center returns and factors
  const arma::mat returns_centred = returns.each_row() - mean_returns.t();
  const arma::mat factors_centred = factors.each_row() - arma::mean(factors);

  // Compute intermediate terms for standard error calculation
  const arma::vec var_ret_inv_err_krs = var_ret_inv_mean_ret -
    var_ret_inv_beta * krs_frp;
  const arma::mat var_fac_inv = arma::inv_sympd(arma::cov(factors));
  const arma::mat hkrs_var_fac_inv = arma::solve(
    beta.t() * var_ret_inv_beta,
    var_fac_inv,
    arma::solve_opts::likely_sympd
  );

  // Compute terms used in the standard error calculation
  const arma::mat term1 = returns_centred * a_matrix.t();
  const arma::mat fac_cen_hkrs_var_fac_inv =
    factors_centred * hkrs_var_fac_inv.t();
  const arma::mat term2 = fac_cen_hkrs_var_fac_inv.each_col() %
    (returns_centred * var_ret_inv_err_krs);
  const arma::mat term3 = term1.each_col() % (returns_centred * var_ret_inv_err_krs);
  const arma::mat akrs_ret_cen_minus_fac_cen = term1 - factors_centred;
  const arma::mat term4 = akrs_ret_cen_minus_fac_cen.each_col() %
    (factors_centred * var_fac_inv * a_matrix * mean_returns);

  arma::mat series = term1 + term2 - term3 - term4;

  // Return the HAC standard errors of the estimator
  return HACStandardErrorsCpp(series, hac_prewhite) /
    std::sqrt(static_cast<double>(returns.n_rows));

}
