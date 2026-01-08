#ifndef CONFIG_H
#define CONFIG_H

#include <string>

// Deprecated: prefer config/app_config.env and ConfigLoader.
// These values are retained for legacy includes and local defaults.
const std::string AWS_REGION = "us-west-2";
const std::string S3_ROOT = "local_s3";
const std::string S3_BUCKET_NAME = "awsmltrainer-demo";
const std::string TRAINING_DATA_KEY = "training-data.csv";
const std::string MODEL_OUTPUT_KEY = "model-output";
const std::string TRAINING_JOB_NAME = "local-training-job";
const std::string TRAINING_DATA_PATH = "examples/example_data/training-data.csv";
const std::string OUTPUT_DIR = "output";
const std::string LOGS_DIR = "logs";

#endif // CONFIG_H
