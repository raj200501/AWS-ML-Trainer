#ifndef S3_MANAGER_H
#define S3_MANAGER_H

#include <string>

class S3Manager {
public:
    S3Manager(const std::string &rootDir, const std::string &region);

    void uploadFile(const std::string &filePath, const std::string &bucketName, const std::string &objectKey);
    void downloadFile(const std::string &bucketName, const std::string &objectKey, const std::string &downloadFilePath);
    std::string objectPath(const std::string &bucketName, const std::string &objectKey) const;

private:
    std::string rootDir;
    std::string region;
};

#endif // S3_MANAGER_H
