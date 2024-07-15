#include "StringCalculator.h"
#include <sstream>
#include <regex>
#include <numeric>
#include <iostream>
#include <algorithm>

std::vector<std::string> StringCalculator::split(const std::string& str, const std::string& delimiter) {
    std::vector<std::string> tokens;
    std::string::size_type lastPos = 0, pos = str.find(delimiter, lastPos);

    while (std::string::npos != pos) {
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        lastPos = pos + delimiter.length();
        pos = str.find(delimiter, lastPos);
    }

    tokens.push_back(str.substr(lastPos));
    return tokens;
}

std::vector<int> StringCalculator::toInts(const std::vector<std::string>& tokens) {
    std::vector<int> numbers;
    for (const std::string& token : tokens) {
        numbers.push_back(std::stoi(token));
    }
    return numbers;
}

int StringCalculator::add(const std::string& numbers) {
    if (numbers.empty()) {
        return 0;
    }

    std::string delimiters = ",\n";
    std::string numString = numbers;

    if (numbers.substr(0, 2) == "//") {
        size_t delimiterEndPos = numbers.find("\n");
        std::string customDelimiter = numbers.substr(2, delimiterEndPos - 2);
        
        if (customDelimiter.front() == '[' && customDelimiter.back() == ']') {
            customDelimiter = customDelimiter.substr(1, customDelimiter.length() - 2);
        }
        
        delimiters += customDelimiter;
        numString = numbers.substr(delimiterEndPos + 1);
    }

    std::regex re("[" + delimiters + "]");
    std::sregex_token_iterator it(numString.begin(), numString.end(), re, -1);
    std::sregex_token_iterator reg_end;

    std::vector<std::string> tokens(it, reg_end);
    std::vector<int> ints = toInts(tokens);

    std::vector<int> negatives;
    int sum = 0;
    for (int number : ints) {
        if (number < 0) {
            negatives.push_back(number);
        } else if (number <= 1000) {
            sum += number;
        }
    }

    if (!negatives.empty()) {
        std::string error = "negatives not allowed: ";
        for (int n : negatives) {
            error += std::to_string(n) + " ";
        }
        throw std::invalid_argument(error);
    }

    return sum;
}
