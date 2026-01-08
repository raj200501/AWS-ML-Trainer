#include "sagemaker_manager.h"
#include "logger.h"
#include "path_utils.h"
#include "training_job.h"
#include "utils/file_utils.h"
#include <stdexcept>

SageMakerManager::SageMakerManager(const AppConfig &config)
    : config(config) {}

std::string SageMakerManager::jobDirectory(const std::string &jobName) const {
    return PathUtils::join({config.outputDir, "jobs", jobName});
}

std::string SageMakerManager::outputPathForJob(const std::string &jobName) const {
    return PathUtils::join(jobDirectory(jobName), "artifacts");
}

void SageMakerManager::createTrainingJob(const std::string &jobName, const std::string &inputPath, const std::string &outputPath) {
    if (jobName.empty()) {
        throw std::runtime_error("Training job name cannot be empty");
    }
    Logger::info("[LocalSageMaker] Creating training job: " + jobName);

    const std::string jobDir = jobDirectory(jobName);
    FileUtils::createDirectory(jobDir);
    FileUtils::writeLines(PathUtils::join(jobDir, "status.txt"), {"CREATED"});
    FileUtils::writeLines(PathUtils::join(jobDir, "input.txt"), {inputPath});
    FileUtils::writeLines(PathUtils::join(jobDir, "output.txt"), {outputPath});
}

void SageMakerManager::waitForTrainingJob(const std::string &jobName) {
    const std::string jobDir = jobDirectory(jobName);
    const std::string statusPath = PathUtils::join(jobDir, "status.txt");

    Logger::info("[LocalSageMaker] Starting training job: " + jobName);
    FileUtils::writeLines(statusPath, {"IN_PROGRESS"});

    const auto inputPathLines = FileUtils::readLines(PathUtils::join(jobDir, "input.txt"));
    const auto outputPathLines = FileUtils::readLines(PathUtils::join(jobDir, "output.txt"));
    if (inputPathLines.empty() || outputPathLines.empty()) {
        throw std::runtime_error("Training job missing input/output paths: " + jobName);
    }

    TrainingJob job(config);
    job.run(inputPathLines.front(), outputPathLines.front());

    FileUtils::writeLines(statusPath, {"COMPLETED"});
    Logger::info("[LocalSageMaker] Training job completed: " + jobName);
}
