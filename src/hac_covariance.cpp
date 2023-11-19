// Author: Alberto Quaini

#include "hac_covariance.h"

//////////////////////////////////////////
//////// HACCovarianceMatrixCpp //////////

arma::mat HACCovarianceMatrixCpp(
  arma::mat& series,
  int n_lags,
  const bool prewhite
) {

  // Compute the number of observations from the input series
  const unsigned int n_observations = series.n_rows;

  // If n_lags is negative
  // Determine the number of lags using the Newey-West plug-in procedure
  if (n_lags < 0) {

    n_lags = std::floor(
      4 * std::pow(static_cast<double>(0.01 * n_observations), 2.0 / 9.0)
    );

  }

  // Ensure n_observations is greater than n_lags
  if (n_observations <= std::max(n_lags, 0)) {

    Rcpp::stop("Number of observations must be greater than the number of lags.");

  }

  // If prewhite is selected, fit an AR(1) to prewhite the series
  arma::mat coefficients;
  if (prewhite) HACPrewhiteningCpp(series, coefficients);

  // Initialize the covariance matrix with the outer product of the series
  arma::mat hac_covariance = series.t() * series /
    static_cast<double>(n_observations);

  // Vector of matrices to hold the transposed lagged series for efficiency
  std::vector<arma::mat> transposed_lagged_series(n_lags);
  for (int lag = 1; lag <= n_lags; ++lag) {

    // Store the transposed lagged series to avoid recomputing
    transposed_lagged_series[lag - 1] = series.tail_rows(n_observations - lag).t();

  }

  // Iteratively update the covariance matrix for each lag
  for (int lag = 1; lag <= n_lags; ++lag) {

    // Calculate the weight for the current lag
    const double lag_weight = 1. - static_cast<double>(lag) / (n_lags + 1.0);

    // Add the weighted lagged covariance to the estimate
    hac_covariance += lag_weight * (transposed_lagged_series[lag - 1] *
      series.head_rows(n_observations - lag)) /
      static_cast<double>(n_observations);

  }

  // If prewhite was selected, revert it
  if (prewhite) HACRevertPrewhiteningCpp(coefficients, hac_covariance);

  // Scale the covariance matrix by the number of observations
  return hac_covariance;

}

////////////////////////////////////////
//////// HACStandardErrorsCpp //////////

arma::vec HACStandardErrorsCpp(
  const arma::mat& series,
  int n_lags
) {

  const arma::uword n_observations = series.n_rows;

  // If n_lags is negative
  // Determine the number of lags using the Newey-West plug-in procedure
  if (n_lags < 0) {

    n_lags = std::floor(
      4 * std::pow(static_cast<double>(0.01 * n_observations), 2.0 / 9.0)
    );

  }

  // Ensure n_observations is greater than n_lags
  if (n_observations <= std::max(n_lags, 0)) {

    Rcpp::stop("Number of observations must be greater than the number of lags.");

  }

  // Compute the diagonal elements of the covariance matrix for lag 0
  arma::rowvec diagonal_of_covariance = arma::sum(arma::square(series), 0) /
    static_cast<double>(n_observations);

  // Loop to compute the standard errors for lags >= 1
  for (int lag = 1; lag <= n_lags; ++lag) {

    // set the lag weight
    const double lag_weight = 1. - lag / (n_lags + 1.);

    // Loop over observations and update the diagonal with lagged contributions
    for (int obs = lag; obs < n_observations; ++obs) {

      diagonal_of_covariance += 2. * lag_weight * (
        series.row(obs - lag) % series.row(obs)
      ) / static_cast<double>(n_observations);

    }

  }

  // Return the standard errors as the square root of the marginal variances
  return arma::sqrt(diagonal_of_covariance).t();

}

//////////////////////////////////
//////// HACVarianceCpp //////////

double HACVarianceCpp(
  arma::vec& series,
  int n_lags,
  const bool prewhite
) {

  // Compute the number of observations in the series
  const unsigned int n_observations = series.n_elem;

  // If n_lags is negative
  // Determine the number of lags using the Newey-West plug-in procedure
  if (n_lags < 0) {

    n_lags = std::floor(
      4 * std::pow(static_cast<double>(0.01 * n_observations), 2.0 / 9.0)
    );

  }

  // Ensure n_observations is greater than n_lags
  if (n_observations <= std::max(n_lags, 0)) {

    Rcpp::stop("Number of observations must be greater than the number of lags.");

  }

  // If prewhite was selected, fit an AR(1) to prewhite the series
  double coefficient = 0.0;
  if (prewhite) HACPrewhiteningScalarCpp(series, coefficient);

  // Initialize variance with the sum of squared observations (lag 0)
  double variance = arma::dot(series, series) /
    static_cast<double>(n_observations);

  // Loop over each lag to update the variance estimate
  for (int lag = 1; lag <= n_lags; ++lag) {
    // Calculate the Newey-West weight for the current lag
    const double lag_weight = 1. - static_cast<double>(lag) / (n_lags + 1.0);

    // Sum the weighted cross products of the series with its lagged self
    variance += 2 * lag_weight * arma::dot(
      series.tail(n_observations - lag),
      series.head(n_observations - lag)
    ) / static_cast<double>(n_observations);
  }

  // Adjust the variance using the prewhitening coefficient if prewhite is true
  if (prewhite) HACRevertPrewhiteningScalarCpp(coefficient, variance);

  // Adjust the variance by the number of observations
  return variance;

}

/////////////////////////////////////////////
///////// Prewhitening /////////////////////

// Matrix series
void HACPrewhiteningCpp(arma::mat& series, arma::mat& coefficients) {

  const unsigned int n_observations = series.n_rows;

  const arma::mat head = series.head_rows(n_observations - 1);

  const arma::mat tail = series.tail_rows(n_observations - 1);

  // compute the coefficients of an AR(1)
  coefficients = arma::solve(head, tail);

  // Prewhite the series using the coefficients
  series = tail - head * coefficients;

}

// Scalar series
void HACPrewhiteningScalarCpp(arma::vec& series, double coefficient) {

  const unsigned int n_observations = series.n_rows;

  const arma::vec head = series.head(n_observations - 1);

  const arma::vec tail = series.tail(n_observations - 1);

  // compute the coefficients of an AR(1)
  coefficient = arma::dot(head, tail) / arma::dot(head, head);

  // Prewhite the series using the coefficients
  series = tail - head * coefficient;

}

// Matrix series
void HACRevertPrewhiteningCpp(
  const arma::mat& coefficients,
  arma::mat& hac_covariance
) {

  const unsigned int n_variables = coefficients.n_rows;

  const arma::mat inv_temp = arma::inv(
    arma::eye(n_variables, n_variables) - coefficients.t()
  );

  // Adjust the HAC covariance matrix using the inverse of the prewhitening transformation
  hac_covariance = inv_temp * hac_covariance * inv_temp.t();

}

// Scalar series
void HACRevertPrewhiteningScalarCpp(
  const double coefficient,
  double hac_covariance
) {

  const double temp = 1./(1. - coefficient);

  // Adjust the HAC covariance matrix using the inverse of the prewhitening transformation
  hac_covariance = temp * temp * hac_covariance;

}
