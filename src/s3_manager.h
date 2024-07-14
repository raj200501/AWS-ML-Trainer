#ifndef S3_MANAGER_H
#define S3_MANAGER_H

#include <aws/s3/S3Client.h>
#include <memory>
#include <string>

class S3Manager {
public:
    S3Manager(const std::string &accessKey, const std::string &secretKey, const std::string &region);
    void uploadFile(const std::string &filePath, const std::string &bucketName, const std::string &objectKey);
    void downloadFile(const std::string &bucketName, const std::string &objectKey, const std::string &downloadFilePath);

private:
    std::shared_ptr<Aws::S3::S3Client> client;
};

#endif // S3_MANAGER_H
