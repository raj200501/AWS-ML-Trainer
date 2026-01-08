#ifndef TEST_PATHS_H
#define TEST_PATHS_H

#include "path_utils.h"
#include <string>

class TestPaths {
public:
    static std::string root() {
#ifdef AWSMLTRAINER_SOURCE_DIR
        return std::string(AWSMLTRAINER_SOURCE_DIR);
#else
        return std::string(".");
#endif
    }

    static std::string fixture(const std::string &name) {
        return PathUtils::join(root(), PathUtils::join("tests/fixtures", name));
    }

    static std::string output(const std::string &name) {
        return PathUtils::join(root(), PathUtils::join("output", name));
    }
};

#endif // TEST_PATHS_H
