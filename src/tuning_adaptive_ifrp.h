// Author: Alberto Quaini

#ifndef TUNING_ADAPTIVE_IFRP_H
#define TUNING_ADAPTIVE_IFRP_H

#include <RcppArmadillo.h>

// Function for internal use
// Computes the Generalized Cross Validation score of the adaptive intrinsic
// factor risk premia for each penalty parameter value.
arma::vec GCVScoreAdaptiveIFRPCpp(
  const arma::mat& aifrp,
  const arma::mat& covariance_factors_returns,
  const arma::mat& variance_returns,
  const arma::vec& mean_returns,
  const unsigned int n_observations,
  const bool gcv_scaling_n_assets = false
);

// Function for internal use
// Computes the Identified Generalized Cross Validation score of the adaptive
// intrinsic factor risk premia for each penalty parameter value.
arma::vec IGCVScoreAdaptiveIFRPCpp(
  const arma::mat& aifrp,
  const arma::mat& returns,
  const arma::mat& factors,
  const arma::mat& covariance_factors_returns,
  const arma::mat& variance_returns,
  const arma::vec& mean_returns,
  const bool gcv_scaling_n_assets = false,
  const double target_level_kp2006_rank_test = 0.05
);

// Function for internal use
// Computes the Generalized Cross Validation score of the adaptive intrinsic
// factor risk premia for each penalty parameter value. The numerator in the
// score is weighted by the variance matrix of asset excess returns.
arma::vec WeightedGCVScoreAdaptiveIFRPCpp(
  const arma::mat& afrp,
  const arma::mat& covariance_factors_returns,
  const arma::mat& variance_returns,
  const arma::vec& mean_returns,
  const unsigned int n_observations,
  const bool gcv_scaling_n_assets = false
);

// Function for internal use
// Computes the Identified Generalized Cross Validation score of the adaptive
// intrinsic factor risk premia for each penalty parameter value. The numerator
// in the score is weighted by the variance matrix of asset excess returns.
arma::vec WeightedIGCVScoreAdaptiveIFRPCpp(
  const arma::mat& afrp,
  const arma::mat& returns,
  const arma::mat& factors,
  const arma::mat& covariance_factors_returns,
  const arma::mat& variance_returns,
  const arma::vec& mean_returns,
  const unsigned int n_observations,
  const bool gcv_scaling_n_assets = false,
  const double target_level_kp2006_rank_test = 0.05
);

// Function for internal use
// Computes the Cross Validation score of the adaptive intrinsic factor risk
// premia for each penalty parameter value.
arma::vec CVScoreAdaptiveIFRPCpp(
  const arma::mat& returns,
  const arma::mat& factors,
  const arma::vec& penalty_parameters,
  const char weighting_type = 'c',
  const unsigned int n_folds = 5
);

// Function for internal use
// Computes the Rolling Validation score of the adaptive intrinsic factor risk
// premia for each penalty parameter value.
arma::vec RVScoreAdaptiveIFRPCpp(
  const arma::mat& returns,
  const arma::mat& factors,
  const arma::vec& penalty_parameters,
  const char weighting_type = 'c',
  const unsigned int n_train_observations = 120,
  const unsigned int n_test_observations = 12,
  const unsigned int roll_shift = 12
);

// Function for internal use
// Computes the prediction error given information on the train and test data.
double ComputePredictionErrorCpp(
  const arma::vec& aifrp_train,
  const arma::mat& covariance_factor_returns_train,
  const arma::mat& variance_returns_train,
  const arma::vec& mean_returns_test,
  const arma::vec& variance_returns_test
);

#endif
