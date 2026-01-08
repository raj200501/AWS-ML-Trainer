#ifndef CONFIG_LOADER_H
#define CONFIG_LOADER_H

#include <string>

struct AppConfig {
    std::string awsRegion;
    std::string s3Root;
    std::string s3BucketName;
    std::string trainingDataKey;
    std::string modelOutputKey;
    std::string trainingJobName;
    std::string trainingDataPath;
    std::string outputDir;
    std::string logsDir;
};

class ConfigLoader {
public:
    static AppConfig load(const std::string &configPath);
    static AppConfig loadFromEnvironment(const AppConfig &defaults);
};

#endif // CONFIG_LOADER_H
