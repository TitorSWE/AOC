// utils.h

#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>

std::string Input(std::string fileName);
std::vector<std::string> splitString(std::string s, std::string delimiter);
long gcd(long a, long b);
long lcm(long a, long b);
long lcmVector(const std::vector<long>& numbers);

#endif // UTILS_H
