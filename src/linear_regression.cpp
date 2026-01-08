#include "linear_regression.h"
#include <cmath>
#include <stdexcept>

RegressionModel LinearRegression::fit(const Dataset &dataset) const {
    if (dataset.rows.size() < 2) {
        throw std::runtime_error("Need at least two rows to fit linear regression");
    }

    double sumX = 0.0;
    double sumY = 0.0;
    double sumXY = 0.0;
    double sumXX = 0.0;

    for (const auto &row : dataset.rows) {
        sumX += row.feature;
        sumY += row.target;
        sumXY += row.feature * row.target;
        sumXX += row.feature * row.feature;
    }

    const double n = static_cast<double>(dataset.rows.size());
    const double denominator = (n * sumXX - sumX * sumX);
    if (std::abs(denominator) < 1e-12) {
        throw std::runtime_error("Cannot fit linear regression: variance of feature is zero");
    }

    RegressionModel model;
    model.slope = (n * sumXY - sumX * sumY) / denominator;
    model.intercept = (sumY - model.slope * sumX) / n;
    return model;
}

double LinearRegression::predict(const RegressionModel &model, double feature) const {
    return model.slope * feature + model.intercept;
}

RegressionMetrics LinearRegression::evaluate(const Dataset &dataset, const RegressionModel &model) const {
    if (dataset.rows.empty()) {
        throw std::runtime_error("Cannot evaluate model on empty dataset");
    }

    double sumSquaredError = 0.0;
    double sumSquaredTotal = 0.0;
    double meanTarget = 0.0;

    for (const auto &row : dataset.rows) {
        meanTarget += row.target;
    }
    meanTarget /= static_cast<double>(dataset.rows.size());

    for (const auto &row : dataset.rows) {
        const double prediction = predict(model, row.feature);
        const double error = row.target - prediction;
        sumSquaredError += error * error;
        const double total = row.target - meanTarget;
        sumSquaredTotal += total * total;
    }

    RegressionMetrics metrics;
    metrics.mse = sumSquaredError / static_cast<double>(dataset.rows.size());
    metrics.r2 = sumSquaredTotal < 1e-12 ? 1.0 : (1.0 - (sumSquaredError / sumSquaredTotal));
    return metrics;
}
