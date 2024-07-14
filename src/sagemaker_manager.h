#ifndef SAGEMAKER_MANAGER_H
#define SAGEMAKER_MANAGER_H

#include <aws/sagemaker/SageMakerClient.h>
#include <memory>
#include <string>

class SageMakerManager {
public:
    SageMakerManager(const std::string &region);
    void createTrainingJob(const std::string &jobName, const std::string &trainingImage, const std::string &roleArn,
                           const std::string &inputBucket, const std::string &inputKey,
                           const std::string &outputBucket, const std::string &outputKey);
    void waitForTrainingJob(const std::string &jobName);

private:
    std::shared_ptr<Aws::SageMaker::SageMakerClient> client;
};

#endif // SAGEMAKER_MANAGER_H
