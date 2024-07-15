#include "StringCalculator.h"
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <regex>

int StringCalculator::add(const std::string& numbers) {
    if (numbers.empty()) {
        return 0;
    }

    std::string delimiter = ",|\n";
    std::string numbersStr = numbers;

    // Check for custom delimiter
    if (numbers.substr(0, 2) == "//") {
        size_t delimiterEndPos = numbers.find("\n");
        std::string delimiterSection = numbers.substr(2, delimiterEndPos - 2);
        if (delimiterSection[0] == '[' && delimiterSection[delimiterSection.size() - 1] == ']') {
            delimiterSection = delimiterSection.substr(1, delimiterSection.size() - 2);
        }
        delimiter = std::regex_replace(delimiterSection, std::regex(R"([\[\]])"), "");
        numbersStr = numbers.substr(delimiterEndPos + 1);
    }

    std::vector<int> nums = splitAndConvert(numbersStr, delimiter);

    checkForNegatives(nums);

    int sum = 0;
    for (int num : nums) {
        if (num <= 1000) {
            sum += num;
        }
    }

    return sum;
}

std::vector<int> StringCalculator::splitAndConvert(const std::string& numbers, const std::string& delimiter) {
    std::vector<int> result;
    std::regex re(delimiter);
    std::sregex_token_iterator it(numbers.begin(), numbers.end(), re, -1);
    std::sregex_token_iterator reg_end;

    for (; it != reg_end; ++it) {
        if (!it->str().empty()) {
            result.push_back(std::stoi(it->str()));
        }
    }

    return result;
}

void StringCalculator::checkForNegatives(const std::vector<int>& numbers) {
    std::vector<int> negatives;
    for (int num : numbers) {
        if (num < 0) {
            negatives.push_back(num);
        }
    }
    if (!negatives.empty()) {
        std::ostringstream oss;
        oss << "negatives not allowed: ";
        for (size_t i = 0; i < negatives.size(); ++i) {
            oss << negatives[i];
            if (i < negatives.size() - 1) {
                oss << ", ";
            }
        }
        throw std::runtime_error(oss.str());
    }
}


