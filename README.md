# AWSMLTrainer

## Overview

**AWSMLTrainer** is a C++ application that simulates an AWS-style machine learning workflow locally. It provides a deterministic training pipeline that:

- Uploads training data to a local S3-style directory.
- Runs a local "SageMaker" training job (linear regression over CSV data).
- Exports model artifacts and metrics.
- Downloads the trained model to a predictable output directory.

This repository ships with a complete build, test, and verification workflow so a clean checkout can run the pipeline end-to-end without AWS credentials.

## Key Features

- **Local S3 emulation**: File-based bucket/object layout for deterministic uploads and downloads.
- **Local SageMaker emulation**: Linear regression training job with metrics and manifest artifacts.
- **Configurable pipeline**: `.env`-style config file + environment variable overrides.
- **Comprehensive logging**: Logs stored in `logs/` for auditing and troubleshooting.
- **Deterministic verification**: `scripts/verify.sh` builds, tests, and validates core behavior.

## Architecture

### Components

- **Main Module**: Orchestrates local S3 upload, training job creation, and artifact download.
- **S3 Manager**: Copies files into `local_s3/` buckets and retrieves artifacts.
- **SageMaker Manager**: Creates a local training job, runs the training pipeline, and writes artifacts.
- **Training Job**: Parses CSV, fits linear regression, writes `model.json` + `manifest.txt`.
- **Logger**: Writes structured logs for every step.

## Installation

1. **Clone the repository**:
    ```sh
    git clone https://github.com/your-username/AWSMLTrainer.git
    cd AWSMLTrainer
    ```

2. **Build and test the project**:
    ```sh
    ./build/build.sh
    ```

## Configuration

The pipeline reads configuration from `config/app_config.env` by default. The file format is simple `KEY=VALUE` pairs:

```ini
AWS_REGION=us-west-2
S3_ROOT=local_s3
S3_BUCKET=awsmltrainer-demo
TRAINING_DATA_KEY=training-data.csv
MODEL_OUTPUT_KEY=model-output
TRAINING_JOB_NAME=local-training-job
TRAINING_DATA_PATH=examples/example_data/training-data.csv
OUTPUT_DIR=output
LOGS_DIR=logs
```

Environment variables with the `AWSMLTRAINER_` prefix override values in the config file, for example:

```sh
export AWSMLTRAINER_OUTPUT_DIR=output/custom
```

## Usage

1. **Run the application**:
    ```sh
    ./scripts/run.sh
    ```

2. **Expected output**:
    - Model artifact: `output/model.json`
    - Training logs: `logs/awsmltrainer.log`
    - Local S3 bucket: `local_s3/awsmltrainer-demo/`

## Verified Quickstart

The following commands were executed successfully in this repository:

```sh
./scripts/run.sh
```

After running, `output/model.json` will contain a JSON payload with the trained slope/intercept and metrics.

## Verified Verification

To run the full deterministic verification (build, unit tests, integration smoke test):

```sh
./scripts/verify.sh
```

This command:
1. Builds the project with CMake.
2. Runs the unit tests.
3. Executes the full training pipeline using the default config.
4. Validates that `output/model.json` contains the expected sections.

## Troubleshooting

- **Missing model output**: Ensure `TRAINING_DATA_PATH` points to a valid CSV file with `feature,target` columns.
- **Config errors**: Confirm `config/app_config.env` exists and uses `KEY=VALUE` syntax.
- **Reproducibility**: Delete `output/` and rerun `./scripts/run.sh` to regenerate artifacts.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
