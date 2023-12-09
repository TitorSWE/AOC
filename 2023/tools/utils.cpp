// utils.cpp

#include "utils.h"
#include <iostream>
#include <vector>
#include <algorithm>

std::string Input(std::string fileName) {
    std::ifstream inputFile(fileName);
    std::stringstream buffer;
    buffer << inputFile.rdbuf();
    std::string fileContent = buffer.str();
    return fileContent;
}

std::vector<std::string> splitString(std::string s, std::string delimiter) {
    std::vector<std::string> res;
    int left = 0;
    int right = 0;
    for (int i = 0; i < s.size(); i++) {
        char ch = s[i];
        if (ch == delimiter[0]) {
            bool stringsEqual = true;
            for (int k = 0; k < delimiter.size(); k++) {
                if (s[i + k] != delimiter[k]) stringsEqual = false;
            }
            if (stringsEqual) {
                std::string stringToAdd = s.substr(left, right - left);
                if (right > left) {
                    res.push_back(stringToAdd);
                }
                left = right + delimiter.size();
            }
        }
        right++;
    }
    if (right > left) res.push_back(s.substr(left, right));
    return res;
}


// Function to calculate the greatest common divisor (GCD) using Euclidean algorithm
long gcd(long a, long b) {
    while (b != 0) {
        long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to calculate the least common multiple (LCM) of two numbers
long lcm(long a, long b) {
    return (a * b) / gcd(a, b);
}

// Function to calculate the LCM of a vector of integers
long lcmVector(const std::vector<long>& numbers) {
    if (numbers.empty()) {
        std::cerr << "Error: Empty vector. Cannot calculate LCM." << std::endl;
        return -1; // Return a sentinel value or throw an exception to indicate an error
    }

    long result = numbers.front(); // Initialize with the first number

    // Iterate through the vector and calculate LCM for each pair of numbers
    for (size_t i = 1; i < numbers.size(); ++i) {
        result = lcm(result, numbers[i]);
    }

    return result;
}
