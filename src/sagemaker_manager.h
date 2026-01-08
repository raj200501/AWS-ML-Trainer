#ifndef SAGEMAKER_MANAGER_H
#define SAGEMAKER_MANAGER_H

#include "config_loader.h"
#include <string>

class SageMakerManager {
public:
    SageMakerManager(const AppConfig &config);
    void createTrainingJob(const std::string &jobName, const std::string &inputPath, const std::string &outputPath);
    void waitForTrainingJob(const std::string &jobName);
    std::string outputPathForJob(const std::string &jobName) const;

private:
    AppConfig config;
    std::string jobDirectory(const std::string &jobName) const;
};

#endif // SAGEMAKER_MANAGER_H
