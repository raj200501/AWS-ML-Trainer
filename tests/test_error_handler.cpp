#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "error_handler.h"

TEST_CASE("ErrorHandler", "[error]") {
    SECTION("Handle error") {
        REQUIRE_NOTHROW(ErrorHandler::handleError("This is a test error."));
    }
}
