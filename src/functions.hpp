#pragma once
#include <iostream>
#include <deque>
#include <string>
#include <cmath>

using std::cin;
using std::cout;
using std::deque;
using std::fmod;
using std::string;

deque<int> fillQue(int length);
deque<int> convert(int decimalNumber);
deque<int> memoryNotation(int length, deque<int> binaryNumber, bool positive);
double convertToWholeDecimal(string const &binaryNumber);
double convertToFractionDecimal(string const &binaryNumber);

inline bool between(int number, int min, int max)
{
    return (number >= min && number <= max);
}