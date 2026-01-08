#include "s3_manager.h"
#include "logger.h"
#include "path_utils.h"
#include "utils/file_utils.h"
#include <fstream>
#include <stdexcept>

S3Manager::S3Manager(const std::string &rootDir, const std::string &region)
    : rootDir(rootDir), region(region) {
    if (rootDir.empty()) {
        throw std::runtime_error("S3 root directory cannot be empty");
    }
}

std::string S3Manager::objectPath(const std::string &bucketName, const std::string &objectKey) const {
    return PathUtils::join(rootDir, PathUtils::join(bucketName, objectKey));
}

void S3Manager::uploadFile(const std::string &filePath, const std::string &bucketName, const std::string &objectKey) {
    if (!FileUtils::fileExists(filePath)) {
        throw std::runtime_error("Upload source file does not exist: " + filePath);
    }

    const std::string destinationPath = objectPath(bucketName, objectKey);
    FileUtils::createParentDirectories(destinationPath);

    std::ifstream source(filePath, std::ios::binary);
    std::ofstream destination(destinationPath, std::ios::binary);
    if (!source.is_open() || !destination.is_open()) {
        throw std::runtime_error("Failed to open files for upload: " + filePath + " -> " + destinationPath);
    }

    destination << source.rdbuf();
    Logger::info("[LocalS3:" + region + "] Uploaded " + filePath + " to s3://" + bucketName + "/" + objectKey);
}

void S3Manager::downloadFile(const std::string &bucketName, const std::string &objectKey, const std::string &downloadFilePath) {
    const std::string sourcePath = objectPath(bucketName, objectKey);
    if (!FileUtils::fileExists(sourcePath)) {
        throw std::runtime_error("Download source object does not exist: " + sourcePath);
    }

    FileUtils::createParentDirectories(downloadFilePath);
    std::ifstream source(sourcePath, std::ios::binary);
    std::ofstream destination(downloadFilePath, std::ios::binary);
    if (!source.is_open() || !destination.is_open()) {
        throw std::runtime_error("Failed to open files for download: " + sourcePath + " -> " + downloadFilePath);
    }

    destination << source.rdbuf();
    Logger::info("[LocalS3:" + region + "] Downloaded s3://" + bucketName + "/" + objectKey + " to " + downloadFilePath);
}
