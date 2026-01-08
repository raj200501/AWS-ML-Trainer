#ifndef MODEL_ARTIFACTS_H
#define MODEL_ARTIFACTS_H

#include "linear_regression.h"
#include <string>
#include <vector>

struct ModelArtifact {
    RegressionModel model;
    RegressionMetrics metrics;
    std::string trainingJobName;
    std::string trainedAt;
};

class ModelArtifacts {
public:
    static std::string serializeModel(const ModelArtifact &artifact);
    static std::vector<std::string> buildManifest(const ModelArtifact &artifact);
};

#endif // MODEL_ARTIFACTS_H
