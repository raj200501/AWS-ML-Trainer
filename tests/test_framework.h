#ifndef TEST_FRAMEWORK_H
#define TEST_FRAMEWORK_H

#include <cmath>
#include <functional>
#include <stdexcept>
#include <string>
#include <vector>

struct TestCase {
    std::string name;
    std::function<void()> func;
};

class TestRegistry {
public:
    static TestRegistry &instance();
    void add(const TestCase &testCase);
    const std::vector<TestCase> &tests() const;

private:
    std::vector<TestCase> testCases;
};

struct TestRegistrar {
    TestRegistrar(const std::string &name, std::function<void()> func);
};

#define TEST_CASE(name) \
    void name(); \
    static TestRegistrar registrar_##name(#name, name); \
    void name()

#define REQUIRE(condition) \
    if (!(condition)) { \
        throw std::runtime_error("Requirement failed: " #condition); \
    }

#define REQUIRE_EQ(left, right) \
    if (!((left) == (right))) { \
        throw std::runtime_error("Requirement failed: " #left " == " #right); \
    }

#define REQUIRE_NEAR(value, expected, tolerance) \
    if (std::abs((value) - (expected)) > (tolerance)) { \
        throw std::runtime_error("Requirement failed: |" #value " - " #expected "| <= " #tolerance); \
    }

#define REQUIRE_NOTHROW(statement) \
    try { \
        statement; \
    } catch (...) { \
        throw std::runtime_error("Requirement failed: " #statement " did throw"); \
    }

#endif // TEST_FRAMEWORK_H
