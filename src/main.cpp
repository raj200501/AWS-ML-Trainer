#include <iostream>
#include "s3_manager.h"
#include "sagemaker_manager.h"
#include "logger.h"
#include "error_handler.h"
#include "config.h"

int main() {
    Logger::init();
    Logger::info("AWSMLTrainer: Starting ML model training on AWS");

    try {
        S3Manager s3Manager(AWS_ACCESS_KEY, AWS_SECRET_KEY, AWS_REGION);
        SageMakerManager sageMakerManager(AWS_REGION);

        // Upload training data to S3
        s3Manager.uploadFile("examples/example_data/training-data.csv", S3_BUCKET_NAME, TRAINING_DATA_KEY);

        // Create a SageMaker training job
        std::string trainingJobName = "my-training-job";
        sageMakerManager.createTrainingJob(trainingJobName, TRAINING_IMAGE, ROLE_ARN, S3_BUCKET_NAME, TRAINING_DATA_KEY, S3_BUCKET_NAME, MODEL_OUTPUT_KEY);

        // Wait for the training job to complete
        sageMakerManager.waitForTrainingJob(trainingJobName);

        // Download the trained model from S3
        s3Manager.downloadFile(S3_BUCKET_NAME, MODEL_OUTPUT_KEY + "/output/model.tar.gz", "output/model.tar.gz");

        Logger::info("Training complete. Model downloaded to output/model.tar.gz");
    } catch (const std::exception& e) {
        ErrorHandler::handleError(e.what());
    }

    Logger::shutdown();
    return 0;
}
