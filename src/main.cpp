#include "config_loader.h"
#include "error_handler.h"
#include "logger.h"
#include "path_utils.h"
#include "s3_manager.h"
#include "sagemaker_manager.h"
#include "utils/file_utils.h"
#include <iostream>

namespace {
struct CliOptions {
    std::string configPath = "config/app_config.env";
    bool showHelp = false;
};

CliOptions parseArgs(int argc, char **argv) {
    CliOptions options;
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--help" || arg == "-h") {
            options.showHelp = true;
            return options;
        }
        if (arg == "--config" && i + 1 < argc) {
            options.configPath = argv[++i];
            continue;
        }
    }
    return options;
}

void printHelp() {
    std::cout << "AWSMLTrainer (local mode)\n"
              << "Usage: ./AWSMLTrainer [--config path]\n\n"
              << "Options:\n"
              << "  --config <path>   Path to the config env file (default: config/app_config.env)\n"
              << "  -h, --help        Show this help message\n";
}
}

int main(int argc, char **argv) {
    const auto options = parseArgs(argc, argv);
    if (options.showHelp) {
        printHelp();
        return 0;
    }

    try {
        AppConfig config = ConfigLoader::load(options.configPath);
        Logger::init(PathUtils::join(config.logsDir, "awsmltrainer.log"));
        Logger::info("AWSMLTrainer: Starting local ML model training");

        FileUtils::createDirectory(config.outputDir);

        S3Manager s3Manager(config.s3Root, config.awsRegion);
        SageMakerManager sageMakerManager(config);

        const std::string trainingObjectKey = config.trainingDataKey;
        s3Manager.uploadFile(config.trainingDataPath, config.s3BucketName, trainingObjectKey);

        const std::string inputPath = s3Manager.objectPath(config.s3BucketName, trainingObjectKey);
        const std::string jobOutputPath = sageMakerManager.outputPathForJob(config.trainingJobName);
        sageMakerManager.createTrainingJob(config.trainingJobName, inputPath, jobOutputPath);
        sageMakerManager.waitForTrainingJob(config.trainingJobName);

        const std::string modelObjectKey = PathUtils::join(config.modelOutputKey, "model.json");
        const std::string s3ModelPath = PathUtils::join(jobOutputPath, "model.json");
        s3Manager.uploadFile(s3ModelPath, config.s3BucketName, modelObjectKey);

        const std::string downloadPath = PathUtils::join(config.outputDir, "model.json");
        s3Manager.downloadFile(config.s3BucketName, modelObjectKey, downloadPath);

        Logger::info("Training complete. Model downloaded to " + downloadPath);
        Logger::shutdown();
        return 0;
    } catch (const std::exception &e) {
        ErrorHandler::handleError(e.what());
        Logger::shutdown();
        return 1;
    }
}
