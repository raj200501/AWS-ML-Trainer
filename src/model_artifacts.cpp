#include "model_artifacts.h"
#include <iomanip>
#include <sstream>

std::string ModelArtifacts::serializeModel(const ModelArtifact &artifact) {
    std::ostringstream stream;
    stream << "{\n";
    stream << "  \"training_job\": \"" << artifact.trainingJobName << "\",\n";
    stream << "  \"trained_at\": \"" << artifact.trainedAt << "\",\n";
    stream << std::fixed << std::setprecision(6);
    stream << "  \"model\": {\n";
    stream << "    \"slope\": " << artifact.model.slope << ",\n";
    stream << "    \"intercept\": " << artifact.model.intercept << "\n";
    stream << "  },\n";
    stream << "  \"metrics\": {\n";
    stream << "    \"mse\": " << artifact.metrics.mse << ",\n";
    stream << "    \"r2\": " << artifact.metrics.r2 << "\n";
    stream << "  }\n";
    stream << "}\n";
    return stream.str();
}

std::vector<std::string> ModelArtifacts::buildManifest(const ModelArtifact &artifact) {
    return {
        "training_job=" + artifact.trainingJobName,
        "trained_at=" + artifact.trainedAt,
        "model.slope=" + std::to_string(artifact.model.slope),
        "model.intercept=" + std::to_string(artifact.model.intercept),
        "metrics.mse=" + std::to_string(artifact.metrics.mse),
        "metrics.r2=" + std::to_string(artifact.metrics.r2)
    };
}
