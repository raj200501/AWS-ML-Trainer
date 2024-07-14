#include "s3_manager.h"
#include "logger.h"
#include <aws/core/Aws.h>
#include <aws/s3/S3Client.h>
#include <aws/s3/model/PutObjectRequest.h>
#include <aws/s3/model/GetObjectRequest.h>
#include <aws/core/utils/Outcome.h>
#include <fstream>
#include <iostream>

S3Manager::S3Manager(const std::string &accessKey, const std::string &secretKey, const std::string &region) {
    Aws::Client::ClientConfiguration config;
    config.region = region;

    Aws::Auth::AWSCredentials credentials(accessKey, secretKey);
    client = std::make_shared<Aws::S3::S3Client>(credentials, config);
}

void S3Manager::uploadFile(const std::string &filePath, const std::string &bucketName, const std::string &objectKey) {
    Aws::S3::Model::PutObjectRequest request;
    request.SetBucket(bucketName.c_str());
    request.SetKey(objectKey.c_str());

    std::shared_ptr<Aws::IOStream> inputData = Aws::MakeShared<Aws::FStream>("SampleAllocationTag", filePath.c_str(), std::ios_base::in | std::ios_base::binary);
    request.SetBody(inputData);

    auto outcome = client->PutObject(request);
    if (!outcome.IsSuccess()) {
        Logger::error("Failed to upload file to S3: " + outcome.GetError().GetMessage());
    } else {
        Logger::info("Successfully uploaded file to S3: " + objectKey);
    }
}

void S3Manager::downloadFile(const std::string &bucketName, const std::string &objectKey, const std::string &downloadFilePath) {
    Aws::S3::Model::GetObjectRequest request;
    request.SetBucket(bucketName.c_str());
    request.SetKey(objectKey.c_str());

    auto outcome = client->GetObject(request);
    if (!outcome.IsSuccess()) {
        Logger::error("Failed to download file from S3: " + outcome.GetError().GetMessage());
    } else {
        auto &retrievedFile = outcome.GetResultWithOwnership().GetBody();
        std::ofstream outputFile(downloadFilePath, std::ios::binary);
        outputFile << retrievedFile.rdbuf();
        Logger::info("Successfully downloaded file from S3: " + objectKey);
    }
}
