#include "error_handler.h"
#include "logger.h"
#include "test_framework.h"
#include "test_paths.h"

TEST_CASE(ErrorHandlerLogsMessage) {
    Logger::init(TestPaths::output("test_logs/error_handler.log"));
    REQUIRE_NOTHROW(ErrorHandler::handleError("Something went wrong"));
    Logger::shutdown();
}
