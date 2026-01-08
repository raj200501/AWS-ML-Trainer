#include "path_utils.h"
#include "s3_manager.h"
#include "test_framework.h"
#include "test_paths.h"
#include "utils/file_utils.h"

TEST_CASE(S3ManagerUploadAndDownload) {
    const std::string root = TestPaths::output("test_s3");
    const std::string bucket = "unit-test-bucket";
    const std::string inputFile = PathUtils::join(root, "input.txt");
    const std::string downloadFile = PathUtils::join(root, "downloaded.txt");

    FileUtils::writeLines(inputFile, {"hello", "world"});

    S3Manager manager(root, "us-west-2");
    manager.uploadFile(inputFile, bucket, "data/input.txt");

    REQUIRE(FileUtils::fileExists(PathUtils::join(root, "unit-test-bucket/data/input.txt")));

    manager.downloadFile(bucket, "data/input.txt", downloadFile);
    REQUIRE(FileUtils::fileExists(downloadFile));
}
