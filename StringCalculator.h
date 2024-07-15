#include "StringCalculator.h"
#include <sstream>
#include <stdexcept>
#include <algorithm>

int StringCalculator::add(const std::string& numbers) {
    if (numbers.empty()) {
        return 0;
    }

    std::string delimiter = ",|\n";
    std::string numbersStr = numbers;

    // Check for custom delimiter
    if (numbers.substr(0, 2) == "//") {
        size_t delimiterEndPos = numbers.find("\n");
        delimiter = numbers.substr(2, delimiterEndPos - 2);
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
    std::string num;
    std::string::size_type lastPos = 0, pos = 0;

    while ((pos = numbers.find_first_of(delimiter, lastPos)) != std::string::npos) {
        if (pos > lastPos) {
            result.push_back(std::stoi(numbers.substr(lastPos, pos - lastPos)));
        }
        lastPos = pos + 1;
    }
    if (lastPos < numbers.size()) {
        result.push_back(std::stoi(numbers.substr(lastPos)));
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
