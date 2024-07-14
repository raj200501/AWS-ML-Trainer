#include "error_handler.h"
#include "logger.h"

void ErrorHandler::handleError(const std::string &errorMessage) {
    Logger::error("Error occurred: " + errorMessage);
    // Additional error handling logic can be added here
}
