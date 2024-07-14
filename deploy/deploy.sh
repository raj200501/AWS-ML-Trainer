#!/bin/bash

# Ensure the build directory is clean
rm -rf build
mkdir build

# Build the project
./build/build.sh

# Deploy the application (this script can be extended based on the specific deployment requirements)
echo "Deploying AWSMLTrainer application..."
