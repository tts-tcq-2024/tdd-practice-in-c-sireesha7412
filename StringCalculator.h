#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <iterator>

// Add token to the tokens vector if it's not empty
void addTokenIfNotEmpty(const std::string& token, std::vector<std::string>& tokens) {
    if (!token.empty()) {
        tokens.push_back(token);
    }
}

// Split the input string by the delimiter and return a vector of tokens
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

// Tokenize the input string by multiple delimiters
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

// Get the delimiter from the input string
std::string getDelimiter(const std::string& input) {
    if (input.substr(0, 2) == "//") {
        return std::string(1, input[2]);
    }
    return ",";
}

// Get the numbers string from the input string
std::string getNumbersString(const std::string& input) {
    if (input.substr(0, 2) == "//") {
        return input.substr(4);
    }
    return input;
}

// Collect negative numbers from the vector of numbers
void collectNegatives(const std::vector<int>& nums, std::vector<int>& negatives) {
    for (int num : nums) {
        if (num < 0) {
            negatives.push_back(num);
        }
    }
}

// Throw an exception if there are negative numbers
void throwNegativesException(const std::vector<int>& negatives) {
    if (!negatives.empty()) {
        std::ostringstream oss;
        oss << "Negatives not allowed: ";
        std::copy(negatives.begin(), negatives.end(), std::ostream_iterator<int>(oss, " "));
        throw std::runtime_error(oss.str());
    }
}

// Sum the numbers in the vector
int sumNumbers(const std::vector<int>& nums) {
    return std::accumulate(nums.begin(), nums.end(), 0);
}

// Extract and parse numbers from the input string
std::vector<int> extractAndParseNumbers(const std::string& input) {
    std::vector<int> numbers;
    std::vector<std::string> tokens = tokenize(input, ",\n");

    for (const std::string& token : tokens) {
        numbers.push_back(std::stoi(token));
    }
    return numbers;
}

// Add function to sum the numbers in the input string
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



