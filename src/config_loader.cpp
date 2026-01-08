#include "config_loader.h"
#include "utils/string_utils.h"
#include "utils/file_utils.h"
#include <cstdlib>
#include <stdexcept>
#include <unordered_map>

namespace {
std::unordered_map<std::string, std::string> parseConfigLines(const std::vector<std::string> &lines) {
    std::unordered_map<std::string, std::string> values;
    for (const auto &line : lines) {
        const auto trimmed = StringUtils::trim(line);
        if (trimmed.empty() || StringUtils::startsWith(trimmed, "#")) {
            continue;
        }
        const auto parts = StringUtils::split(trimmed, '=');
        if (parts.size() < 2) {
            continue;
        }
        const auto key = StringUtils::trim(parts[0]);
        const auto value = StringUtils::trim(trimmed.substr(trimmed.find('=') + 1));
        values[key] = value;
    }
    return values;
}

std::string getEnvOrDefault(const std::string &key, const std::string &defaultValue) {
    const char *env = std::getenv(key.c_str());
    if (env == nullptr) {
        return defaultValue;
    }
    return std::string(env);
}
}

AppConfig ConfigLoader::load(const std::string &configPath) {
    if (!FileUtils::fileExists(configPath)) {
        throw std::runtime_error("Config file not found: " + configPath);
    }
    const auto lines = FileUtils::readLines(configPath);
    const auto values = parseConfigLines(lines);

    AppConfig config;
    config.awsRegion = values.count("AWS_REGION") ? values.at("AWS_REGION") : "us-west-2";
    config.s3Root = values.count("S3_ROOT") ? values.at("S3_ROOT") : "local_s3";
    config.s3BucketName = values.count("S3_BUCKET") ? values.at("S3_BUCKET") : "awsmltrainer-demo";
    config.trainingDataKey = values.count("TRAINING_DATA_KEY") ? values.at("TRAINING_DATA_KEY") : "training-data.csv";
    config.modelOutputKey = values.count("MODEL_OUTPUT_KEY") ? values.at("MODEL_OUTPUT_KEY") : "model-output";
    config.trainingJobName = values.count("TRAINING_JOB_NAME") ? values.at("TRAINING_JOB_NAME") : "local-training-job";
    config.trainingDataPath = values.count("TRAINING_DATA_PATH") ? values.at("TRAINING_DATA_PATH") : "examples/example_data/training-data.csv";
    config.outputDir = values.count("OUTPUT_DIR") ? values.at("OUTPUT_DIR") : "output";
    config.logsDir = values.count("LOGS_DIR") ? values.at("LOGS_DIR") : "logs";

    return loadFromEnvironment(config);
}

AppConfig ConfigLoader::loadFromEnvironment(const AppConfig &defaults) {
    AppConfig config = defaults;
    config.awsRegion = getEnvOrDefault("AWSMLTRAINER_AWS_REGION", config.awsRegion);
    config.s3Root = getEnvOrDefault("AWSMLTRAINER_S3_ROOT", config.s3Root);
    config.s3BucketName = getEnvOrDefault("AWSMLTRAINER_S3_BUCKET", config.s3BucketName);
    config.trainingDataKey = getEnvOrDefault("AWSMLTRAINER_TRAINING_DATA_KEY", config.trainingDataKey);
    config.modelOutputKey = getEnvOrDefault("AWSMLTRAINER_MODEL_OUTPUT_KEY", config.modelOutputKey);
    config.trainingJobName = getEnvOrDefault("AWSMLTRAINER_TRAINING_JOB_NAME", config.trainingJobName);
    config.trainingDataPath = getEnvOrDefault("AWSMLTRAINER_TRAINING_DATA_PATH", config.trainingDataPath);
    config.outputDir = getEnvOrDefault("AWSMLTRAINER_OUTPUT_DIR", config.outputDir);
    config.logsDir = getEnvOrDefault("AWSMLTRAINER_LOGS_DIR", config.logsDir);
    return config;
}
