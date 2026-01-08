#include "config_loader.h"
#include "test_framework.h"
#include "test_paths.h"
#include "utils/file_utils.h"

TEST_CASE(ConfigLoaderReadsDefaultsAndOverrides) {
    const std::string configPath = TestPaths::output("test_configs/app_config.env");
    FileUtils::writeLines(configPath, {
        "AWS_REGION=us-east-1",
        "S3_ROOT=output/local_s3",
        "S3_BUCKET=demo-bucket",
        "TRAINING_DATA_KEY=data.csv",
        "MODEL_OUTPUT_KEY=model-output",
        "TRAINING_JOB_NAME=test-job",
        "TRAINING_DATA_PATH=tests/fixtures/linear-data.csv",
        "OUTPUT_DIR=output/test_run",
        "LOGS_DIR=output/test_logs"
    });

    AppConfig config = ConfigLoader::load(configPath);

    REQUIRE_EQ(config.awsRegion, std::string("us-east-1"));
    REQUIRE_EQ(config.s3Root, std::string("output/local_s3"));
    REQUIRE_EQ(config.s3BucketName, std::string("demo-bucket"));
    REQUIRE_EQ(config.trainingDataKey, std::string("data.csv"));
    REQUIRE_EQ(config.modelOutputKey, std::string("model-output"));
    REQUIRE_EQ(config.trainingJobName, std::string("test-job"));
    REQUIRE_EQ(config.trainingDataPath, std::string("tests/fixtures/linear-data.csv"));
    REQUIRE_EQ(config.outputDir, std::string("output/test_run"));
    REQUIRE_EQ(config.logsDir, std::string("output/test_logs"));
}
