#ifndef CONFIG_H
#define CONFIG_H

#include <string>

const std::string AWS_ACCESS_KEY = "your-access-key";
const std::string AWS_SECRET_KEY = "your-secret-key";
const std::string AWS_REGION = "your-region";
const std::string S3_BUCKET_NAME = "your-s3-bucket-name";
const std::string TRAINING_DATA_KEY = "training-data.csv";
const std::string MODEL_OUTPUT_KEY = "model-output";
const std::string TRAINING_IMAGE = "123456789012.dkr.ecr.us-west-2.amazonaws.com/my-training-image:latest";
const std::string ROLE_ARN = "arn:aws:iam::123456789012:role/SageMakerRole";

#endif // CONFIG_H
