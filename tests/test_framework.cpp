#include "test_framework.h"
#include <iostream>
#include <stdexcept>

TestRegistry &TestRegistry::instance() {
    static TestRegistry registry;
    return registry;
}

void TestRegistry::add(const TestCase &testCase) {
    testCases.push_back(testCase);
}

const std::vector<TestCase> &TestRegistry::tests() const {
    return testCases;
}

TestRegistrar::TestRegistrar(const std::string &name, std::function<void()> func) {
    TestRegistry::instance().add({name, func});
}

int main() {
    int failures = 0;
    for (const auto &testCase : TestRegistry::instance().tests()) {
        try {
            testCase.func();
            std::cout << "[PASS] " << testCase.name << "\n";
        } catch (const std::exception &ex) {
            failures++;
            std::cerr << "[FAIL] " << testCase.name << ": " << ex.what() << "\n";
        } catch (...) {
            failures++;
            std::cerr << "[FAIL] " << testCase.name << ": unknown error\n";
        }
    }

    if (failures > 0) {
        std::cerr << failures << " test(s) failed.\n";
        return 1;
    }
    std::cout << "All tests passed.\n";
    return 0;
}
