#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "sagemaker_manager.h"
#include "config.h"

TEST_CASE("SageMakerManager Training Job", "[sagemaker]") {
    SageMakerManager sageMakerManager(AWS_REGION);

    SECTION("Create and wait for training job") {
        std::string trainingJobName = "test-training-job";
        REQUIRE_NOTHROW(sageMakerManager.createTrainingJob(trainingJobName, TRAINING_IMAGE, ROLE_ARN, S3_BUCKET_NAME, TRAINING_DATA_KEY, S3_BUCKET_NAME, MODEL_OUTPUT_KEY));
        REQUIRE_NOTHROW(sageMakerManager.waitForTrainingJob(trainingJobName));
    }
}
