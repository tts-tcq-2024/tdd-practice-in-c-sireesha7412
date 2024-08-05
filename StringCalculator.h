#include <cassert>
#include <iostream>
#include <string>

void runTests() {
    // Test empty input
    assert(add("") == 0);

    // Test single number
    assert(add("1") == 1);

    // Test multiple numbers with default delimiter
    assert(add("1,2,3") == 6);
    assert(add("1\n2,3") == 6);

    // Test custom delimiter
    assert(add("//;\n1;2") == 3);
    assert(add("//***\n1***2***3") == 6);

    // Test negative numbers
    try {
        add("-1,2");
    } catch (const std::runtime_error& e) {
        assert(std::string(e.what()) == "negatives not allowed: -1");
    }

    try {
        add("2,-4,3,-5");
    } catch (const std::runtime_error& e) {
        assert(std::string(e.what()) == "negatives not allowed: -4, -5");
    }

    // Test numbers greater than 1000
    assert(add("2,1001") == 2);
    assert(add("1000,1001,2") == 1002);

    // Test special cases
    assert(add("1,\n") == 1);  // single number with trailing delimiter
    assert(add("//;\n1;2;") == 3);  // trailing custom delimiter

    std::cout << "All tests passed!" << std::endl;
}

int main() {
    runTests();
    return 0;
}

