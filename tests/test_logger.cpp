#include "logger.h"
#include "test_framework.h"
#include "test_paths.h"
#include "utils/file_utils.h"

TEST_CASE(LoggerInitializesAndWrites) {
    const std::string logPath = TestPaths::output("test_logs/logger.log");
    Logger::init(logPath);

    Logger::info("Info message");
    Logger::warn("Warning message");
    Logger::error("Error message");

    Logger::shutdown();

    REQUIRE(FileUtils::fileExists(logPath));
}
