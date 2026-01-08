#include "test_framework.h"
#include "validation.h"

TEST_CASE(ValidationChecksHeaderAndNumbers) {
    REQUIRE_NOTHROW(Validation::validateCsvHeader("feature,target"));
    REQUIRE_NEAR(Validation::parseDouble("2.5", "value"), 2.5, 1e-6);
}
