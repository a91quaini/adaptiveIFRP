// Author: Alberto Quaini

#ifndef FRP_H
#define FRP_H

#include <RcppArmadillo.h>

/////////////////////////////////////////////////
////////////  Factor Risk Premia ////////////////
/////////////////////////////////////////////////

//' Compute factor risk premia from data
//'
//' @name FRPCpp
//' @description Computes the Fama-MachBeth (1973) <doi:10.1086/260061> factor
//' risk premia:
//' `FMFRP = (beta' * beta)^{-1} * beta' * E[R]` where
//' `beta = Cov[R, F] * V[F]^{-1}`
//' or the misspecification-robust factor risk premia of Kan-Robotti-Shanken (2013)
//' <doi:10.1111/jofi.12035>:
//' `KRSFRP = (beta' * V[R]^{-1} * beta)^{-1} * beta' * V[R]^{-1} * E[R]`
//' from data on factors `F` and test
//' asset excess returns `R`. Optionally computes the corresponding
//' heteroskedasticity and autocorrelation robust standard errors using the
//' Newey-West (1994) <doi:10.2307/2297912> plug-in procedure to select the
//' number of relevant lags, i.e., `n_lags = 4 * (n_observations/100)^(2/9)`.
//'
//' @param returns `n_observations x n_returns`-dimensional matrix of test asset
//' excess returns.
//' @param factors `n_observations x n_factors`-dimensional matrix of factors.
//' @param misspecification_robust boolean `TRUE` for the
//' "misspecification-robust" Kan-Robotti-Shanken (2013) GLS approach using the
//' inverse covariance matrix of returns; `FALSE` for standard Fama-MacBeth
//' risk premia. Default is `TRUE`.
//' @param include_standard_errors boolean `TRUE` if you want to compute the
//' factor risk premia HAC standard errors; `FALSE` otherwise.
//' Default is `FALSE`.
//'
//' @return a list containing `n_factors`-dimensional vector of factor
//' risk premia in `"risk_premia"`; if `include_standard_errors=TRUE`, then
//' it further includes `n_factors`-dimensional vector of factor risk
//' premia standard errors in `"standard_errors"`.
//'
//' @noRd
//'
// [[Rcpp::export]]
Rcpp::List FRPCpp(
  const arma::mat& returns,
  const arma::mat& factors,
  const bool misspecification_robust = true,
  const bool include_standard_errors = false
);

// Function for internal use
// Computes Fama-MacBeth (1973) <doi:10.1086/260061> factor risk premia from
// moments extracted from data
arma::vec FMFRPCpp(
  const arma::mat& beta,
  const arma::vec& mean_returns
);

// Function for internal use
// Computes the misspecification robust factor risk premia of
// Kan-Robotti-Shanken (2013) <doi:10.1111/jofi.12035> from moments extracted from data
arma::vec KRSFRPCpp(
  const arma::mat& beta,
  const arma::vec& mean_returns,
  const arma::mat& weighting_matrix
);

// Function for internal use
// Compute the standard errors of the Fama-MacBeth (1973) <doi:10.1086/260061>
// factor risk premia from moments using the heteroskedasticity and
// autocorrelation robust standard errors using the Newey-West (1994)
// <doi:10.2307/2297912> plug-in procedure to select the number of relevant lags,
// i.e., `n_lags = 4 * (n_observations/100)^(2/9)`.
arma::vec StandardErrorsFRPCpp(
  const arma::vec& frp,
  const arma::mat& returns,
  const arma::mat& factors,
  const arma::mat& beta,
  const arma::mat& covariance_factors_returns,
  const arma::mat& variance_returns,
  const arma::vec& mean_returns
);

// Function for internal use
// Compute the standard errors of the Kan-Robotti-Shanken (2013) <doi:10.1111/jofi.12035>
// factor risk premia from moments using the heteroskedasticity and
// autocorrelation robust standard errors using the Newey-West (1994)
// <doi:10.2307/2297912> plug-in procedure to select the number of relevant lags,
// i.e., `n_lags = 4 * (n_observations/100)^(2/9)`.
arma::vec StandardErrorsKRSFRPCpp(
  const arma::vec& krs_frp,
  const arma::mat& returns,
  const arma::mat& factors,
  const arma::mat& beta,
  const arma::mat& covariance_factors_returns,
  const arma::mat& variance_returns,
  const arma::vec& mean_returns
);

#endif
