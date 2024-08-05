#include "StringCalculator.h"
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <iterator>
#include <numeric> // Include this header for std::accumulate

void addTokenIfNotEmpty(const std::string& token, std::vector<std::string>& tokens) {
    if (!token.empty()) {
        tokens.push_back(token);
    }
}

std::vector<std::string> splitHelper(const std::string& input, const std::string& delimiter) {
    std::vector<std::string> tokens;
    size_t start = 0, end = 0;

    while ((end = input.find(delimiter, start)) != std::string::npos) {
        addTokenIfNotEmpty(input.substr(start, end - start), tokens);
        start = end + delimiter.length();
    }
    addTokenIfNotEmpty(input.substr(start), tokens);

    return tokens;
}

std::vector<std::string> tokenize(const std::string& input, const std::string& delimiters) {
    std::vector<std::string> tokens;
    std::string token;
    for (char ch : input) {
        if (delimiters.find(ch) != std::string::npos) {
            addTokenIfNotEmpty(token, tokens);
            token.clear();
        } else {
            token += ch;
        }
    }
    addTokenIfNotEmpty(token, tokens);
    return tokens;
}

std::string getDelimiter(const std::string& input) {
    if (input.substr(0, 2) == "//") {
        return std::string(1, input[2]);
    }
    return ",";
}

std::string getNumbersString(const std::string& input) {
    if (input.substr(0, 2) == "//") {
        return input.substr(4);
    }
    return input;
}

void collectNegatives(const std::vector<int>& nums, std::vector<int>& negatives) {
    for (int num : nums) {
        if (num < 0) {
            negatives.push_back(num);
        }
    }
}

void throwNegativesException(const std::vector<int>& negatives) {
    if (!negatives.empty()) {
        std::ostringstream oss;
        oss << "Negatives not allowed: ";
        std::copy(negatives.begin(), negatives.end(), std::ostream_iterator<int>(oss, " "));
        throw std::runtime_error(oss.str());
    }
}

int sumNumbers(const std::vector<int>& nums) {
    return std::accumulate(nums.begin(), nums.end(), 0);
}

std::vector<int> extractAndParseNumbers(const std::string& input) {
    std::vector<int> numbers;
    std::vector<std::string> tokens = tokenize(input, ",\n");

    for (const std::string& token : tokens) {
        numbers.push_back(std::stoi(token));
    }
    return numbers;
}

int add(const std::string& input) {
    std::string delimiter = getDelimiter(input);
    std::string numbersString = getNumbersString(input);
    std::vector<std::string> tokens = splitHelper(numbersString, delimiter);

    std::vector<int> numbers;
    for (const std::string& token : tokens) {
        numbers.push_back(std::stoi(token));
    }

    std::vector<int> negatives;
    collectNegatives(numbers, negatives);
    throwNegativesException(negatives);

    return sumNumbers(numbers);
}
