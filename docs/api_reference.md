# AWSMLTrainer API Reference

## S3Manager

### Constructor

`S3Manager(const std::string &accessKey, const std::string &secretKey, const std::string &region)`

### Methods

- `void uploadFile(const std::string &filePath, const std::string &bucketName, const std::string &objectKey)`
- `void downloadFile(const std::string &bucketName, const std::string &objectKey, const std::string &downloadFilePath)`

## SageMakerManager

### Constructor

`SageMakerManager(const std::string &region)`

### Methods

- `void createTrainingJob(const std::string &jobName, const std::string &trainingImage, const std::string &roleArn, const std::string &inputBucket, const std::string &inputKey, const std::string &outputBucket, const std::string &outputKey)`
- `void waitForTrainingJob(const std::string &jobName)`

## Logger

### Methods

- `static void init()`
- `static void shutdown()`
- `static void info(const std::string &message)`
- `static void warn(const std::string &message)`
- `static void error(const std::string &message)`

## ErrorHandler

### Methods

- `static void handleError(const std::string &errorMessage)`

## FileUtils

### Methods

- `static bool fileExists(const std::string &filePath)`

## StringUtils

### Methods

- `static std::string toLower(const std::string &str)`
