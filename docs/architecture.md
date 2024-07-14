# AWSMLTrainer Architecture

## Overview

AWSMLTrainer is a C++ application designed to efficiently train machine learning models on AWS. The application orchestrates the training process, manages data transfer, and leverages AWS services like S3 for data storage and SageMaker for model training.

## Components

### Main
- Entry point of the application.
- Orchestrates the overall workflow.

### S3 Manager
- Handles uploading and downloading files to/from AWS S3.
- Utilizes AWS SDK for C++.

### SageMaker Manager
- Manages the creation and monitoring of SageMaker training jobs.
- Utilizes AWS SDK for C++.

### Logger
- Provides logging capabilities for the application.
- Logs messages to both console and file.

### Error Handler
- Handles and logs application errors.
- Provides a central mechanism for error management.

### Utilities
- File and string utilities used throughout the application.

## Workflow

1. Upload training data to S3.
2. Create a SageMaker training job.
3. Wait for the training job to complete.
4. Download the trained model from S3.

## Dependencies

- AWS SDK for C++
- CMake for build configuration
- Catch2 for unit testing
