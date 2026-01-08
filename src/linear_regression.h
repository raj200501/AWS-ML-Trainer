#ifndef LINEAR_REGRESSION_H
#define LINEAR_REGRESSION_H

#include "csv_reader.h"

struct RegressionModel {
    double slope = 0.0;
    double intercept = 0.0;
};

struct RegressionMetrics {
    double mse = 0.0;
    double r2 = 0.0;
};

class LinearRegression {
public:
    RegressionModel fit(const Dataset &dataset) const;
    double predict(const RegressionModel &model, double feature) const;
    RegressionMetrics evaluate(const Dataset &dataset, const RegressionModel &model) const;
};

#endif // LINEAR_REGRESSION_H
