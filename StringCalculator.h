#include "StringCalculator.h"
#include <gtest/gtest.h>

// Define your test cases here

// Test cases
TEST(StringCalculatorTest, TestEmptyString) {
    EXPECT_EQ(add(""), 0);
}

TEST(StringCalculatorTest, TestSingleNumber) {
    EXPECT_EQ(add("1"), 1);
}

TEST(StringCalculatorTest, TestMultipleNumbers) {
    EXPECT_EQ(add("1,2,3"), 6);
}

TEST(StringCalculatorTest, TestNewlineDelimiter) {
    EXPECT_EQ(add("1\n2,3"), 6);
}

TEST(StringCalculatorTest, TestCustomDelimiter) {
    EXPECT_EQ(add("//;\n1;2"), 3);
}

TEST(StringCalculatorTest, TestNegativeNumbers) {
    try {
        add("-1,2");
        FAIL() << "Expected std::runtime_error";
    } catch (std::runtime_error const& err) {
        EXPECT_EQ(err.what(), std::string("negatives not allowed: -1"));
    } catch (...) {
        FAIL() << "Expected std::runtime_error";
    }

    try {
        add("2,-4,3,-5");
        FAIL() << "Expected std::runtime_error";
    } catch (std::runtime_error const& err) {
        EXPECT_EQ(err.what(), std::string("negatives not allowed: -4, -5"));
    } catch (...) {
        FAIL() << "Expected std::runtime_error";
    }
}

TEST(StringCalculatorTest, TestNumbersGreaterThan1000) {
    EXPECT_EQ(add("2,1001"), 2);
    EXPECT_EQ(add("1000,1001,2"), 1002);
}

TEST(StringCalculatorTest, TestMultiCharacterDelimiter) {
    EXPECT_EQ(add("//[***]\n1***2***3"), 6);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

