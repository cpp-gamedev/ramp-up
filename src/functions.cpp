#include "functions.hpp"
#include <cstddef>
#include <stdexcept>

deque<int> convert(int decimalNumber) {
	deque<int> binaryNumber;

	while (decimalNumber > 0) {
		binaryNumber.push_front(decimalNumber % 2);
		decimalNumber /= 2;
	}
	cout << "conversion complete:\n";
	return binaryNumber;
}

deque<int> memoryNotation(size_t length, deque<int> binaryNumber, bool positive) {
	// takes in an empty array of the the appropriate size, converts the last digits to the binary number and depending on
	// the sign of the number <positive>, it changs the msb to 0 or 1.

	while (binaryNumber.size() < length - 1) {
		binaryNumber.push_front(0);
	}
	if (positive) {
		binaryNumber.push_front(0);
	} else {
		binaryNumber.push_front(1);
	}

	return binaryNumber;
}

/* Isn't working properly, might reimplement later if I have time
double convertToFractionDecimal(string const& binaryNumber) {
	double decimalNumber = 0;

	for (size_t i = 0; i < binaryNumber.length(); i++) {
		if (binaryNumber[i] == '1') {
			int power = 0x1 << i;
			decimalNumber += 1 / ((binaryNumber[i] - '0') * power);
		} else {
			continue;
		}
	}

	return decimalNumber;
}
*/
double convertToWholeDecimal(string const& binaryNumber) {

	int total = 0;
	for (auto digit : binaryNumber) {
		total = total * 2 + (digit - '0');
	}

	return total;
}
bool checkBinary(string binaryNumber) {
	for (auto digit : binaryNumber) {
		if (digit != '1' && digit != '0') {
			return false;
		}
	}
	return true;
}
