#ifndef STRING_CALCULATOR_H
#define STRING_CALCULATOR_H

#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <regex>

namespace {
    void addTokenIfNotEmpty(const std::string& token, std::vector<std::string>& tokens) {
        if (!token.empty()) {
            tokens.push_back(token);
        }
    }

    std::vector<std::string> splitHelper(const std::string& str, const std::string& delimiter) {
        std::vector<std::string> tokens;
        size_t prev = 0, pos = 0;
        while ((pos = str.find(delimiter, prev)) != std::string::npos) {
            std::string token = str.substr(prev, pos - prev);
            addTokenIfNotEmpty(token, tokens);
            prev = pos + delimiter.length();
        }
        std::string token = str.substr(prev);
        addTokenIfNotEmpty(token, tokens);
        return tokens;
    }

    std::vector<std::string> split(const std::string& str, const std::string& delimiter) {
        return splitHelper(str, delimiter);
    }

    std::vector<std::string> tokenize(const std::string& str, const std::string& delimiters) {
        std::vector<std::string> tokens;
        std::string regexPattern = "[" + delimiters + "\n]";
        std::regex re(regexPattern);
        std::sregex_token_iterator it(str.begin(), str.end(), re, -1);
        std::sregex_token_iterator end;
        while (it != end) {
            tokens.push_back(*it++);
        }
        return tokens;
    }

    std::string getDelimiter(const std::string& str) {
        if (str.substr(0, 2) == "//") {
            size_t endPos = str.find('\n');
            return str.substr(2, endPos - 2);
        }
        return ",\n";
    }

    std::string getNumbersString(const std::string& str) {
        if (str.substr(0, 2) == "//") {
            size_t newlinePos = str.find('\n');
            return str.substr(newlinePos + 1);
        }
        return str;
    }

    void throwNegativesException(const std::vector<int>& negatives) {
        std::ostringstream oss;
        oss << "negatives not allowed: ";
        for (size_t i = 0; i < negatives.size(); ++i) {
            if (i > 0) oss << ", ";
            oss << negatives[i];
        }
        throw std::runtime_error(oss.str());
    }

    void collectNegatives(const std::vector<int>& numbers, std::vector<int>& negatives) {
        for (int num : numbers) {
            if (num < 0) {
                negatives.push_back(num);
            }
        }
    }

    void checkNegatives(const std::vector<int>& numbers) {
        std::vector<int> negatives;
        collectNegatives(numbers, negatives);
        if (!negatives.empty()) {
            throwNegativesException(negatives);
        }
    }

    int sumNumbers(const std::vector<int>& numbers) {
        int sum = 0;
        for (int num : numbers) {
            if (num <= 1000) {
                sum += num;
            }
        }
        return sum;
    }

    std::vector<int> parseNumbers(const std::vector<std::string>& tokens) {
        std::vector<int> numbers;
        for (const std::string& token : tokens) {
            if (!token.empty()) {
                numbers.push_back(std::stoi(token));
            }
        }
        return numbers;
    }

    std::vector<std::string> extractTokens(const std::string& numbers) {
        std::string delimiters = getDelimiter(numbers);
        std::string nums = getNumbersString(numbers);
        return tokenize(nums, delimiters);
    }

    std::vector<int> extractAndParseNumbers(const std::string& numbers) {
        std::vector<std::string> tokens = extractTokens(numbers);
        return parseNumbers(tokens);
    }
}

int add(const std::string& numbers) {
    if (numbers.empty()) {
        return 0;
    }

    std::vector<int> parsedNumbers = extractAndParseNumbers(numbers);
    checkNegatives(parsedNumbers);
    return sumNumbers(parsedNumbers);
}

