#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

#include <string>

class ErrorHandler {
public:
    static void handleError(const std::string &errorMessage);
};

#endif // ERROR_HANDLER_H
