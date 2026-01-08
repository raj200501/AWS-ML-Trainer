#include "training_job.h"
#include "model_artifacts.h"
#include "path_utils.h"
#include "utils/file_utils.h"
#include "logger.h"
#include <chrono>
#include <iomanip>
#include <sstream>

TrainingJob::TrainingJob(const AppConfig &config)
    : config(config) {}

std::string TrainingJob::currentTimestamp() const {
    const auto now = std::chrono::system_clock::now();
    const auto time = std::chrono::system_clock::to_time_t(now);
    std::tm tm{};
    gmtime_r(&time, &tm);
    std::ostringstream stream;
    stream << std::put_time(&tm, "%Y-%m-%dT%H:%M:%SZ");
    return stream.str();
}

TrainingJobResult TrainingJob::run(const std::string &inputPath, const std::string &outputDir) {
    Logger::info("Training job started for input: " + inputPath);
    Dataset dataset = reader.read(inputPath);
    RegressionModel model = regression.fit(dataset);
    RegressionMetrics metrics = regression.evaluate(dataset, model);

    ModelArtifact artifact{model, metrics, config.trainingJobName, currentTimestamp()};
    const std::string modelPath = PathUtils::join(outputDir, "model.json");
    const std::string manifestPath = PathUtils::join(outputDir, "manifest.txt");
    FileUtils::writeLines(manifestPath, ModelArtifacts::buildManifest(artifact));

    FileUtils::createParentDirectories(modelPath);
    FileUtils::writeLines(modelPath, {ModelArtifacts::serializeModel(artifact)});

    Logger::info("Training job finished. Model saved to " + modelPath);

    return {model, metrics, modelPath, manifestPath};
}
