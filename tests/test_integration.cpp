#include "config_loader.h"
#include "logger.h"
#include "path_utils.h"
#include "s3_manager.h"
#include "sagemaker_manager.h"
#include "test_framework.h"
#include "test_paths.h"
#include "utils/file_utils.h"

TEST_CASE(IntegrationPipelineGeneratesModel) {
    AppConfig config;
    config.awsRegion = "us-west-2";
    config.s3Root = TestPaths::output("integration_s3");
    config.s3BucketName = "integration-bucket";
    config.trainingDataKey = "training-data.csv";
    config.modelOutputKey = "model-output";
    config.trainingJobName = "integration-job";
    config.trainingDataPath = TestPaths::fixture("linear-data.csv");
    config.outputDir = TestPaths::output("integration_output");
    config.logsDir = TestPaths::output("integration_logs");

    Logger::init(PathUtils::join(config.logsDir, "integration.log"));

    S3Manager s3Manager(config.s3Root, config.awsRegion);
    SageMakerManager sageMakerManager(config);

    s3Manager.uploadFile(config.trainingDataPath, config.s3BucketName, config.trainingDataKey);

    const std::string inputPath = s3Manager.objectPath(config.s3BucketName, config.trainingDataKey);
    const std::string jobOutputPath = sageMakerManager.outputPathForJob(config.trainingJobName);

    sageMakerManager.createTrainingJob(config.trainingJobName, inputPath, jobOutputPath);
    sageMakerManager.waitForTrainingJob(config.trainingJobName);

    const std::string modelPath = PathUtils::join(jobOutputPath, "model.json");
    REQUIRE(FileUtils::fileExists(modelPath));

    Logger::shutdown();
}
