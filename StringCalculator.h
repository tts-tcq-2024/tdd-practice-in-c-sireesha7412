#include "StringCalculator.h"
#include <string>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <algorithm>

int add(const char* input) {
    std::string str(input);

    if (str.empty()) {
        return 0;
    }

    std::string delimiter = ",";
    if (str.substr(0, 2) == "//") {
        size_t pos = str.find('\n');
        delimiter = str.substr(2, pos - 2);
        str = str.substr(pos + 1);
    }

    std::replace(str.begin(), str.end(), '\n', ',');

    std::vector<int> numbers;
    std::stringstream ss(str);
    std::string token;

    while (std::getline(ss, token, ',')) {
        if (!token.empty()) {
            int number = std::stoi(token);
            if (number < 0) {
                throw std::invalid_argument("Negative numbers are not allowed");
            }
            if (number <= 1000) {
                numbers.push_back(number);
            }
        }
    }

    int sum = std::accumulate(numbers.begin(), numbers.end(), 0);
    return sum;
}
