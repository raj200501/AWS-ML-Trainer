#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "logger.h"

TEST_CASE("Logger", "[logger]") {
    Logger::init();

    SECTION("Log info message") {
        REQUIRE_NOTHROW(Logger::info("This is an info message."));
    }

    SECTION("Log warning message") {
        REQUIRE_NOTHROW(Logger::warn("This is a warning message."));
    }

    SECTION("Log error message") {
        REQUIRE_NOTHROW(Logger::error("This is an error message."));
    }

    Logger::shutdown();
}
