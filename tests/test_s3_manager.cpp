#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "s3_manager.h"
#include "config.h"

TEST_CASE("S3Manager Upload and Download", "[s3]") {
    S3Manager s3Manager(AWS_ACCESS_KEY, AWS_SECRET_KEY, AWS_REGION);

    SECTION("Upload file to S3") {
        REQUIRE_NOTHROW(s3Manager.uploadFile("examples/example_data/training-data.csv", S3_BUCKET_NAME, "test/training-data.csv"));
    }

    SECTION("Download file from S3") {
        REQUIRE_NOTHROW(s3Manager.downloadFile(S3_BUCKET_NAME, "test/training-data.csv", "output/test-training-data.csv"));
        REQUIRE(FileUtils::fileExists("output/test-training-data.csv"));
    }
}
