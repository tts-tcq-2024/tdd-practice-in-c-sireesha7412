#include <gtest/gtest.h>
#include "StringCalculator.h"
 
TEST(StringCalculatorTests, AddTokenIfNotEmpty) {
    std::vector<std::string> tokens;
    addTokenIfNotEmpty("", tokens);
    ASSERT_EQ(tokens.size(), 0); // Expect no tokens added for empty string
 
    addTokenIfNotEmpty("token", tokens);
    ASSERT_EQ(tokens.size(), 1); // Expect one token added
    ASSERT_EQ(tokens[0], "token");
}
 
TEST(StringCalculatorTests, SplitHelper) {
    std::string input = "1,2,3";
    std::vector<std::string> tokens = splitHelper(input, ",");
    ASSERT_EQ(tokens.size(), 3); // Expect three tokens
    ASSERT_EQ(tokens[0], "1");
    ASSERT_EQ(tokens[1], "2");
    ASSERT_EQ(tokens[2], "3");
}
 
// Test case for tokenize function
TEST(StringCalculatorTests, Tokenize) {
    std::string input = "1\n2,3";
    std::vector<std::string> tokens = tokenize(input, ",\n");
    ASSERT_EQ(tokens.size(), 3); // Expect three tokens
    ASSERT_EQ(tokens[0], "1");
    ASSERT_EQ(tokens[1], "2");
    ASSERT_EQ(tokens[2], "3");
}
 
TEST(StringCalculatorTests, GetDelimiter) {
    std::string input = "//;\n1;2;3";
    std::string delimiter = getDelimiter(input);
    ASSERT_EQ(delimiter, ";"); // Expect ';' as delimiter
}
 
TEST(StringCalculatorTests, GetNumbersString) {
    std::string input = "//;\n1;2;3";
    std::string numbers = getNumbersString(input);
    ASSERT_EQ(numbers, "1;2;3"); // Expect "1;2;3" as numbers string
}
 
TEST(StringCalculatorTests, NegativeNumbersHandling) {
    std::vector<int> nums = {1, -2, 3, -4};
    std::vector<int> negatives;
    collectNegatives(nums, negatives);
    ASSERT_EQ(negatives.size(), 2); // Expect two negative numbers collected
 
    try {
        throwNegativesException(negatives);
        FAIL() << "Exception not thrown";
    } catch (const std::runtime_error& e) {
        std::string errorMessage = e.what();
        ASSERT_TRUE(errorMessage.find("-2") != std::string::npos);
        ASSERT_TRUE(errorMessage.find("-4") != std::string::npos);
    }
}
 
TEST(StringCalculatorTests, SumNumbers) {
    std::vector<int> nums = {1, 2, 3};
    int sum = sumNumbers(nums);
    ASSERT_EQ(sum, 6); // Expect sum to be 6
}
 
TEST(StringCalculatorTests, ParseAndExtractTokens) {
    std::string input = "1,2,3";
    std::vector<int> parsedNumbers = extractAndParseNumbers(input);
    ASSERT_EQ(parsedNumbers.size(), 3);
    ASSERT_EQ(parsedNumbers[0], 1);
    ASSERT_EQ(parsedNumbers[1], 2);
    ASSERT_EQ(parsedNumbers[2], 3);
}
 
TEST(StringCalculatorTests, AddFunction) {
    int result = add("1,2,3");
    ASSERT_EQ(result, 6); // Expect sum of 1 + 2 + 3 = 6
}
 
int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
