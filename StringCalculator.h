#include "StringCalculator.h"
#include <sstream>
#include <algorithm>
#include <regex>
#include <numeric>

int StringCalculator::add(const std::string& input) {
    if (input.empty()) {
        return 0;
    }

    std::string delimiter = ",";
    size_t pos = 0;
    std::string str = input;

    if (input.substr(0, 2) == "//") {
        delimiter = getDelimiter(input, pos);
        str = input.substr(pos + 1);
    }

    std::replace(str.begin(), str.end(), '\n', ',');
    std::regex re(delimiter);
    str = std::regex_replace(str, re, ",");

    std::vector<int> numbers = splitNumbers(str, ",");
    std::vector<int> negatives;

    for (int num : numbers) {
        if (num < 0) {
            negatives.push_back(num);
        }
    }

    if (!negatives.empty()) {
        std::string message = "negatives not allowed: ";
        for (int n : negatives) {
            message += std::to_string(n) + " ";
        }
        throw std::invalid_argument(message);
    }

    numbers.erase(std::remove_if(numbers.begin(), numbers.end(), [](int num) { return num > 1000; }), numbers.end());
    return std::accumulate(numbers.begin(), numbers.end(), 0);
}

std::vector<int> StringCalculator::splitNumbers(const std::string& str, const std::string& delimiter) {
    std::vector<int> numbers;
    size_t start = 0;
    size_t end = str.find(delimiter);

    while (end != std::string::npos) {
        numbers.push_back(std::stoi(str.substr(start, end - start)));
        start = end + delimiter.length();
        end = str.find(delimiter, start);
    }

    numbers.push_back(std::stoi(str.substr(start, end - start)));
    return numbers;
}

std::string StringCalculator::getDelimiter(const std::string& str, size_t& pos) {
    pos = str.find('\n');
    std::string delimiter = str.substr(2, pos - 2);

    if (delimiter.front() == '[' && delimiter.back() == ']') {
        delimiter = delimiter.substr(1, delimiter.size() - 2);
    }

    return delimiter;
}
