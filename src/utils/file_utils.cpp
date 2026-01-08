#include "file_utils.h"
#include "path_utils.h"
#include <filesystem>
#include <fstream>
#include <stdexcept>

bool FileUtils::fileExists(const std::string &filePath) {
    return std::filesystem::exists(filePath) && std::filesystem::is_regular_file(filePath);
}

bool FileUtils::directoryExists(const std::string &dirPath) {
    return std::filesystem::exists(dirPath) && std::filesystem::is_directory(dirPath);
}

void FileUtils::createDirectory(const std::string &dirPath) {
    if (dirPath.empty()) {
        return;
    }
    std::filesystem::create_directories(dirPath);
}

void FileUtils::createParentDirectories(const std::string &filePath) {
    const auto normalized = PathUtils::normalize(filePath);
    const auto position = normalized.find_last_of('/');
    if (position == std::string::npos) {
        return;
    }
    createDirectory(normalized.substr(0, position));
}

std::vector<std::string> FileUtils::readLines(const std::string &filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file: " + filePath);
    }
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    return lines;
}

void FileUtils::writeLines(const std::string &filePath, const std::vector<std::string> &lines) {
    createParentDirectories(filePath);
    std::ofstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to write file: " + filePath);
    }
    for (const auto &line : lines) {
        file << line << '\n';
    }
}
