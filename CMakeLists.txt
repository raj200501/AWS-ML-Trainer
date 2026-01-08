cmake_minimum_required(VERSION 3.16)
project(AWSMLTrainer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(AWSMLTRAINER_ENABLE_TESTS "Build AWSMLTrainer tests" ON)

add_library(awsmltrainer_lib
    src/config_loader.cpp
    src/csv_reader.cpp
    src/error_handler.cpp
    src/logger.cpp
    src/linear_regression.cpp
    src/model_artifacts.cpp
    src/path_utils.cpp
    src/s3_manager.cpp
    src/sagemaker_manager.cpp
    src/training_job.cpp
    src/utils/file_utils.cpp
    src/utils/string_utils.cpp
    src/validation.cpp
)

target_include_directories(awsmltrainer_lib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_executable(AWSMLTrainer src/main.cpp)

target_link_libraries(AWSMLTrainer PRIVATE awsmltrainer_lib)

if(AWSMLTRAINER_ENABLE_TESTS)
    enable_testing()

    add_executable(awsmltrainer_tests
        tests/test_framework.cpp
        tests/test_config_loader.cpp
        tests/test_csv_reader.cpp
        tests/test_error_handler.cpp
        tests/test_integration.cpp
        tests/test_linear_regression.cpp
        tests/test_logger.cpp
        tests/test_s3_manager.cpp
        tests/test_sagemaker_manager.cpp
        tests/test_validation.cpp
    )

    target_include_directories(awsmltrainer_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests)
    target_link_libraries(awsmltrainer_tests PRIVATE awsmltrainer_lib)
    target_compile_definitions(awsmltrainer_tests PRIVATE AWSMLTRAINER_SOURCE_DIR="${CMAKE_SOURCE_DIR}")

    add_test(NAME awsmltrainer_tests COMMAND awsmltrainer_tests)
endif()
