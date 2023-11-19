// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <RcppArmadillo.h>
#include <Rcpp.h>

using namespace Rcpp;

#ifdef RCPP_USE_GLOBAL_ROSTREAM
Rcpp::Rostream<true>&  Rcpp::Rcout = Rcpp::Rcpp_cout_get();
Rcpp::Rostream<false>& Rcpp::Rcerr = Rcpp::Rcpp_cerr_get();
#endif

// FRPCpp
Rcpp::List FRPCpp(const arma::mat& returns, const arma::mat& factors, const bool misspecification_robust, const bool include_standard_errors);
RcppExport SEXP _intrinsicFRP_FRPCpp(SEXP returnsSEXP, SEXP factorsSEXP, SEXP misspecification_robustSEXP, SEXP include_standard_errorsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const arma::mat& >::type returns(returnsSEXP);
    Rcpp::traits::input_parameter< const arma::mat& >::type factors(factorsSEXP);
    Rcpp::traits::input_parameter< const bool >::type misspecification_robust(misspecification_robustSEXP);
    Rcpp::traits::input_parameter< const bool >::type include_standard_errors(include_standard_errorsSEXP);
    rcpp_result_gen = Rcpp::wrap(FRPCpp(returns, factors, misspecification_robust, include_standard_errors));
    return rcpp_result_gen;
END_RCPP
}
// HACCovarianceMatrixCpp
arma::mat HACCovarianceMatrixCpp(arma::mat& series, int n_lags, const bool prewhite);
RcppExport SEXP _intrinsicFRP_HACCovarianceMatrixCpp(SEXP seriesSEXP, SEXP n_lagsSEXP, SEXP prewhiteSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< arma::mat& >::type series(seriesSEXP);
    Rcpp::traits::input_parameter< int >::type n_lags(n_lagsSEXP);
    Rcpp::traits::input_parameter< const bool >::type prewhite(prewhiteSEXP);
    rcpp_result_gen = Rcpp::wrap(HACCovarianceMatrixCpp(series, n_lags, prewhite));
    return rcpp_result_gen;
END_RCPP
}
// HACVarianceCpp
double HACVarianceCpp(arma::vec& series, int n_lags, const bool prewhite);
RcppExport SEXP _intrinsicFRP_HACVarianceCpp(SEXP seriesSEXP, SEXP n_lagsSEXP, SEXP prewhiteSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< arma::vec& >::type series(seriesSEXP);
    Rcpp::traits::input_parameter< int >::type n_lags(n_lagsSEXP);
    Rcpp::traits::input_parameter< const bool >::type prewhite(prewhiteSEXP);
    rcpp_result_gen = Rcpp::wrap(HACVarianceCpp(series, n_lags, prewhite));
    return rcpp_result_gen;
END_RCPP
}
// ChenFang2019BetaRankTestCpp
Rcpp::List ChenFang2019BetaRankTestCpp(const arma::mat& returns, const arma::mat& factors, const unsigned int n_bootstrap, const double target_level_kp2006_rank_test);
RcppExport SEXP _intrinsicFRP_ChenFang2019BetaRankTestCpp(SEXP returnsSEXP, SEXP factorsSEXP, SEXP n_bootstrapSEXP, SEXP target_level_kp2006_rank_testSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const arma::mat& >::type returns(returnsSEXP);
    Rcpp::traits::input_parameter< const arma::mat& >::type factors(factorsSEXP);
    Rcpp::traits::input_parameter< const unsigned int >::type n_bootstrap(n_bootstrapSEXP);
    Rcpp::traits::input_parameter< const double >::type target_level_kp2006_rank_test(target_level_kp2006_rank_testSEXP);
    rcpp_result_gen = Rcpp::wrap(ChenFang2019BetaRankTestCpp(returns, factors, n_bootstrap, target_level_kp2006_rank_test));
    return rcpp_result_gen;
END_RCPP
}
// IterativeKleibergenPaap2006BetaRankTestCpp
Rcpp::List IterativeKleibergenPaap2006BetaRankTestCpp(const arma::mat& returns, const arma::mat& factors, const double target_level);
RcppExport SEXP _intrinsicFRP_IterativeKleibergenPaap2006BetaRankTestCpp(SEXP returnsSEXP, SEXP factorsSEXP, SEXP target_levelSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const arma::mat& >::type returns(returnsSEXP);
    Rcpp::traits::input_parameter< const arma::mat& >::type factors(factorsSEXP);
    Rcpp::traits::input_parameter< const double >::type target_level(target_levelSEXP);
    rcpp_result_gen = Rcpp::wrap(IterativeKleibergenPaap2006BetaRankTestCpp(returns, factors, target_level));
    return rcpp_result_gen;
END_RCPP
}
// HJMisspecificationTestCpp
Rcpp::List HJMisspecificationTestCpp(const arma::mat& returns, const arma::mat& factors);
RcppExport SEXP _intrinsicFRP_HJMisspecificationTestCpp(SEXP returnsSEXP, SEXP factorsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const arma::mat& >::type returns(returnsSEXP);
    Rcpp::traits::input_parameter< const arma::mat& >::type factors(factorsSEXP);
    rcpp_result_gen = Rcpp::wrap(HJMisspecificationTestCpp(returns, factors));
    return rcpp_result_gen;
END_RCPP
}
// OracleTFRPGCVCpp
Rcpp::List OracleTFRPGCVCpp(const arma::mat& returns, const arma::mat& factors, const arma::mat& covariance_factors_returns, const arma::mat& variance_returns, const arma::vec& mean_returns, const arma::vec& penalty_parameters, const char weighting_type, const bool one_stddev_rule, const bool gcv_scaling_n_assets, const bool gcv_identification_check, const double target_level_kp2006_rank_test, const bool relaxed, const bool include_standard_errors);
RcppExport SEXP _intrinsicFRP_OracleTFRPGCVCpp(SEXP returnsSEXP, SEXP factorsSEXP, SEXP covariance_factors_returnsSEXP, SEXP variance_returnsSEXP, SEXP mean_returnsSEXP, SEXP penalty_parametersSEXP, SEXP weighting_typeSEXP, SEXP one_stddev_ruleSEXP, SEXP gcv_scaling_n_assetsSEXP, SEXP gcv_identification_checkSEXP, SEXP target_level_kp2006_rank_testSEXP, SEXP relaxedSEXP, SEXP include_standard_errorsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const arma::mat& >::type returns(returnsSEXP);
    Rcpp::traits::input_parameter< const arma::mat& >::type factors(factorsSEXP);
    Rcpp::traits::input_parameter< const arma::mat& >::type covariance_factors_returns(covariance_factors_returnsSEXP);
    Rcpp::traits::input_parameter< const arma::mat& >::type variance_returns(variance_returnsSEXP);
    Rcpp::traits::input_parameter< const arma::vec& >::type mean_returns(mean_returnsSEXP);
    Rcpp::traits::input_parameter< const arma::vec& >::type penalty_parameters(penalty_parametersSEXP);
    Rcpp::traits::input_parameter< const char >::type weighting_type(weighting_typeSEXP);
    Rcpp::traits::input_parameter< const bool >::type one_stddev_rule(one_stddev_ruleSEXP);
    Rcpp::traits::input_parameter< const bool >::type gcv_scaling_n_assets(gcv_scaling_n_assetsSEXP);
    Rcpp::traits::input_parameter< const bool >::type gcv_identification_check(gcv_identification_checkSEXP);
    Rcpp::traits::input_parameter< const double >::type target_level_kp2006_rank_test(target_level_kp2006_rank_testSEXP);
    Rcpp::traits::input_parameter< const bool >::type relaxed(relaxedSEXP);
    Rcpp::traits::input_parameter< const bool >::type include_standard_errors(include_standard_errorsSEXP);
    rcpp_result_gen = Rcpp::wrap(OracleTFRPGCVCpp(returns, factors, covariance_factors_returns, variance_returns, mean_returns, penalty_parameters, weighting_type, one_stddev_rule, gcv_scaling_n_assets, gcv_identification_check, target_level_kp2006_rank_test, relaxed, include_standard_errors));
    return rcpp_result_gen;
END_RCPP
}
// OracleTFRPCVCpp
Rcpp::List OracleTFRPCVCpp(const arma::mat& returns, const arma::mat& factors, const arma::mat& covariance_factors_returns, const arma::mat& variance_returns, const arma::vec& mean_returns, const arma::vec& penalty_parameters, const char weighting_type, const bool one_stddev_rule, const unsigned int n_folds, const bool relaxed, const bool include_standard_errors);
RcppExport SEXP _intrinsicFRP_OracleTFRPCVCpp(SEXP returnsSEXP, SEXP factorsSEXP, SEXP covariance_factors_returnsSEXP, SEXP variance_returnsSEXP, SEXP mean_returnsSEXP, SEXP penalty_parametersSEXP, SEXP weighting_typeSEXP, SEXP one_stddev_ruleSEXP, SEXP n_foldsSEXP, SEXP relaxedSEXP, SEXP include_standard_errorsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const arma::mat& >::type returns(returnsSEXP);
    Rcpp::traits::input_parameter< const arma::mat& >::type factors(factorsSEXP);
    Rcpp::traits::input_parameter< const arma::mat& >::type covariance_factors_returns(covariance_factors_returnsSEXP);
    Rcpp::traits::input_parameter< const arma::mat& >::type variance_returns(variance_returnsSEXP);
    Rcpp::traits::input_parameter< const arma::vec& >::type mean_returns(mean_returnsSEXP);
    Rcpp::traits::input_parameter< const arma::vec& >::type penalty_parameters(penalty_parametersSEXP);
    Rcpp::traits::input_parameter< const char >::type weighting_type(weighting_typeSEXP);
    Rcpp::traits::input_parameter< const bool >::type one_stddev_rule(one_stddev_ruleSEXP);
    Rcpp::traits::input_parameter< const unsigned int >::type n_folds(n_foldsSEXP);
    Rcpp::traits::input_parameter< const bool >::type relaxed(relaxedSEXP);
    Rcpp::traits::input_parameter< const bool >::type include_standard_errors(include_standard_errorsSEXP);
    rcpp_result_gen = Rcpp::wrap(OracleTFRPCVCpp(returns, factors, covariance_factors_returns, variance_returns, mean_returns, penalty_parameters, weighting_type, one_stddev_rule, n_folds, relaxed, include_standard_errors));
    return rcpp_result_gen;
END_RCPP
}
// OracleTFRPRVCpp
Rcpp::List OracleTFRPRVCpp(const arma::mat& returns, const arma::mat& factors, const arma::mat& covariance_factors_returns, const arma::mat& variance_returns, const arma::vec& mean_returns, const arma::vec& penalty_parameters, const char weighting_type, const bool one_stddev_rule, const unsigned int n_train_observations, const unsigned int n_test_observations, const unsigned int roll_shift, const bool relaxed, const bool include_standard_errors);
RcppExport SEXP _intrinsicFRP_OracleTFRPRVCpp(SEXP returnsSEXP, SEXP factorsSEXP, SEXP covariance_factors_returnsSEXP, SEXP variance_returnsSEXP, SEXP mean_returnsSEXP, SEXP penalty_parametersSEXP, SEXP weighting_typeSEXP, SEXP one_stddev_ruleSEXP, SEXP n_train_observationsSEXP, SEXP n_test_observationsSEXP, SEXP roll_shiftSEXP, SEXP relaxedSEXP, SEXP include_standard_errorsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const arma::mat& >::type returns(returnsSEXP);
    Rcpp::traits::input_parameter< const arma::mat& >::type factors(factorsSEXP);
    Rcpp::traits::input_parameter< const arma::mat& >::type covariance_factors_returns(covariance_factors_returnsSEXP);
    Rcpp::traits::input_parameter< const arma::mat& >::type variance_returns(variance_returnsSEXP);
    Rcpp::traits::input_parameter< const arma::vec& >::type mean_returns(mean_returnsSEXP);
    Rcpp::traits::input_parameter< const arma::vec& >::type penalty_parameters(penalty_parametersSEXP);
    Rcpp::traits::input_parameter< const char >::type weighting_type(weighting_typeSEXP);
    Rcpp::traits::input_parameter< const bool >::type one_stddev_rule(one_stddev_ruleSEXP);
    Rcpp::traits::input_parameter< const unsigned int >::type n_train_observations(n_train_observationsSEXP);
    Rcpp::traits::input_parameter< const unsigned int >::type n_test_observations(n_test_observationsSEXP);
    Rcpp::traits::input_parameter< const unsigned int >::type roll_shift(roll_shiftSEXP);
    Rcpp::traits::input_parameter< const bool >::type relaxed(relaxedSEXP);
    Rcpp::traits::input_parameter< const bool >::type include_standard_errors(include_standard_errorsSEXP);
    rcpp_result_gen = Rcpp::wrap(OracleTFRPRVCpp(returns, factors, covariance_factors_returns, variance_returns, mean_returns, penalty_parameters, weighting_type, one_stddev_rule, n_train_observations, n_test_observations, roll_shift, relaxed, include_standard_errors));
    return rcpp_result_gen;
END_RCPP
}
// TFRPCpp
Rcpp::List TFRPCpp(const arma::mat& returns, const arma::mat& factors, const bool include_standard_errors);
RcppExport SEXP _intrinsicFRP_TFRPCpp(SEXP returnsSEXP, SEXP factorsSEXP, SEXP include_standard_errorsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const arma::mat& >::type returns(returnsSEXP);
    Rcpp::traits::input_parameter< const arma::mat& >::type factors(factorsSEXP);
    Rcpp::traits::input_parameter< const bool >::type include_standard_errors(include_standard_errorsSEXP);
    rcpp_result_gen = Rcpp::wrap(TFRPCpp(returns, factors, include_standard_errors));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_intrinsicFRP_FRPCpp", (DL_FUNC) &_intrinsicFRP_FRPCpp, 4},
    {"_intrinsicFRP_HACCovarianceMatrixCpp", (DL_FUNC) &_intrinsicFRP_HACCovarianceMatrixCpp, 3},
    {"_intrinsicFRP_HACVarianceCpp", (DL_FUNC) &_intrinsicFRP_HACVarianceCpp, 3},
    {"_intrinsicFRP_ChenFang2019BetaRankTestCpp", (DL_FUNC) &_intrinsicFRP_ChenFang2019BetaRankTestCpp, 4},
    {"_intrinsicFRP_IterativeKleibergenPaap2006BetaRankTestCpp", (DL_FUNC) &_intrinsicFRP_IterativeKleibergenPaap2006BetaRankTestCpp, 3},
    {"_intrinsicFRP_HJMisspecificationTestCpp", (DL_FUNC) &_intrinsicFRP_HJMisspecificationTestCpp, 2},
    {"_intrinsicFRP_OracleTFRPGCVCpp", (DL_FUNC) &_intrinsicFRP_OracleTFRPGCVCpp, 13},
    {"_intrinsicFRP_OracleTFRPCVCpp", (DL_FUNC) &_intrinsicFRP_OracleTFRPCVCpp, 11},
    {"_intrinsicFRP_OracleTFRPRVCpp", (DL_FUNC) &_intrinsicFRP_OracleTFRPRVCpp, 13},
    {"_intrinsicFRP_TFRPCpp", (DL_FUNC) &_intrinsicFRP_TFRPCpp, 3},
    {NULL, NULL, 0}
};

RcppExport void R_init_intrinsicFRP(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
