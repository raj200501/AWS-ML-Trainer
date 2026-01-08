#include "config_loader.h"
#include "sagemaker_manager.h"
#include "test_framework.h"
#include "test_paths.h"
#include "utils/file_utils.h"

TEST_CASE(SageMakerManagerTrainingJobProducesArtifacts) {
    AppConfig config;
    config.awsRegion = "us-west-2";
    config.s3Root = TestPaths::output("test_s3");
    config.s3BucketName = "bucket";
    config.trainingDataKey = "training-data.csv";
    config.modelOutputKey = "model-output";
    config.trainingJobName = "unit-test-job";
    config.trainingDataPath = TestPaths::fixture("linear-data.csv");
    config.outputDir = TestPaths::output("test_jobs");
    config.logsDir = TestPaths::output("test_logs");

    SageMakerManager manager(config);
    const std::string outputPath = manager.outputPathForJob(config.trainingJobName);

    manager.createTrainingJob(config.trainingJobName, config.trainingDataPath, outputPath);
    manager.waitForTrainingJob(config.trainingJobName);

    REQUIRE(FileUtils::fileExists(outputPath + "/model.json"));
    REQUIRE(FileUtils::fileExists(outputPath + "/manifest.txt"));
}
