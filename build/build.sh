#!/bin/bash

# Create build directory if it doesn't exist
mkdir -p build

# Navigate to the build directory
cd build

# Run cmake to configure the project
cmake ..

# Build the project
make

# Run the tests
ctest
