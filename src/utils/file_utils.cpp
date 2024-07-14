#include "file_utils.h"
#include <fstream>

bool FileUtils::fileExists(const std::string &filePath) {
    std::ifstream file(filePath);
    return file.good();
}
