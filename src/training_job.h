#ifndef TRAINING_JOB_H
#define TRAINING_JOB_H

#include "config_loader.h"
#include "csv_reader.h"
#include "linear_regression.h"
#include <string>

struct TrainingJobResult {
    RegressionModel model;
    RegressionMetrics metrics;
    std::string modelPath;
    std::string manifestPath;
};

class TrainingJob {
public:
    TrainingJob(const AppConfig &config);
    TrainingJobResult run(const std::string &inputPath, const std::string &outputDir);

private:
    AppConfig config;
    CsvReader reader;
    LinearRegression regression;

    std::string currentTimestamp() const;
};

#endif // TRAINING_JOB_H
