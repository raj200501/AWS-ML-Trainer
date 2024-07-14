#include "sagemaker_manager.h"
#include "logger.h"
#include <aws/core/Aws.h>
#include <aws/sagemaker/SageMakerClient.h>
#include <aws/sagemaker/model/CreateTrainingJobRequest.h>
#include <aws/sagemaker/model/DescribeTrainingJobRequest.h>
#include <aws/sagemaker/model/DescribeTrainingJobResult.h>
#include <iostream>
#include <thread>
#include <chrono>

SageMakerManager::SageMakerManager(const std::string &region) {
    Aws::Client::ClientConfiguration config;
    config.region = region;
    client = std::make_shared<Aws::SageMaker::SageMakerClient>(config);
}

void SageMakerManager::createTrainingJob(const std::string &jobName, const std::string &trainingImage, const std::string &roleArn,
                                         const std::string &inputBucket, const std::string &inputKey,
                                         const std::string &outputBucket, const std::string &outputKey) {
    Aws::SageMaker::Model::CreateTrainingJobRequest request;
    request.SetTrainingJobName(jobName.c_str());
    request.SetAlgorithmSpecification(Aws::SageMaker::Model::AlgorithmSpecification()
        .WithTrainingImage(trainingImage.c_str())
        .WithTrainingInputMode(Aws::SageMaker::Model::TrainingInputMode::File));
    request.SetRoleArn(roleArn.c_str());
    request.SetInputDataConfig({ Aws::SageMaker::Model::Channel()
        .WithChannelName("training")
        .WithDataSource(Aws::SageMaker::Model::DataSource()
            .WithS3DataSource(Aws::SageMaker::Model::S3DataSource()
                .WithS3Uri("s3://" + inputBucket + "/" + inputKey)
                .WithS3DataType(Aws::SageMaker::Model::S3DataType::S3Prefix)
                .WithS3DataDistributionType(Aws::SageMaker::Model::S3DataDistributionType::FullyReplicated)))
        .WithContentType("text/csv") });
    request.SetOutputDataConfig(Aws::SageMaker::Model::OutputDataConfig()
        .WithS3OutputPath("s3://" + outputBucket + "/" + outputKey));
    request.SetResourceConfig(Aws::SageMaker::Model::ResourceConfig()
        .WithInstanceCount(1)
        .WithInstanceType(Aws::SageMaker::Model::TrainingInstanceType::MlC4Xlarge)
        .WithVolumeSizeInGB(10));
    request.SetStoppingCondition(Aws::SageMaker::Model::StoppingCondition()
        .WithMaxRuntimeInSeconds(3600));

    auto outcome = client->CreateTrainingJob(request);
    if (!outcome.IsSuccess()) {
        Logger::error("Failed to create SageMaker training job: " + outcome.GetError().GetMessage());
    } else {
        Logger::info("Successfully created SageMaker training job: " + jobName);
    }
}

void SageMakerManager::waitForTrainingJob(const std::string &jobName) {
    bool isTraining = true;
    while (isTraining) {
        std::this_thread::sleep_for(std::chrono::minutes(1));
        Aws::SageMaker::Model::DescribeTrainingJobRequest request;
        request.SetTrainingJobName(jobName.c_str());

        auto outcome = client->DescribeTrainingJob(request);
        if (!outcome.IsSuccess()) {
            Logger::error("Failed to describe SageMaker training job: " + outcome.GetError().GetMessage());
            return;
        }

        auto status = outcome.GetResult().GetTrainingJobStatus();
        Logger::info("SageMaker training job status: " + status);
        if (status == Aws::SageMaker::Model::TrainingJobStatus::Completed ||
            status == Aws::SageMaker::Model::TrainingJobStatus::Failed ||
            status == Aws::SageMaker::Model::TrainingJobStatus::Stopped) {
            isTraining = false;
        }
    }
    Logger::info("SageMaker training job completed: " + jobName);
}
