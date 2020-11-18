#include "functions.hpp"
#include <cstddef>
#include <stdexcept>

int numconv::converter() {
	int intNumber, base;
	string binaryNumber;

	// cout << "Usage: <type(f/i)> <value> <base(10/2)\n";
	cout << "Enter the base of the number you want to convert <2> or <10>: ";
	cin >> base;

	if (base == 10) {

		cout << "Enter the number you wish to convert. It must be a positive  integer: ";
		cin >> intNumber;
		if (intNumber < 0) {
			cout << "Number must be positive";
			return 1;
		}
		decimalToBinary(intNumber);
	} else if (base == 2) {
		cout << "Enter your binary number without any spaces. ";
		cin >> binaryNumber;
		if (!checkBinary(binaryNumber)) {
			cout << "The given binary number must consist of 1 and 0\n";
			return 1;
		}

		binaryToDecimal(binaryNumber);
	}

	else {
		cout << "Error: You must input 2 or l0!";
		return 1;
	}
	return 0;
}

deque<int> numconv::convert(int decimalNumber) {
	deque<int> binaryNumber;

	while (decimalNumber > 0) {
		binaryNumber.push_front(decimalNumber % 2);
		decimalNumber /= 2;
	}
	cout << "conversion complete:\n";
	return binaryNumber;
}

deque<int> numconv::memoryNotation(size_t length, deque<int> binaryNumber, bool positive) {
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
double numconv::convertToWholeDecimal(string const& binaryNumber) {

	int total = 0;
	for (auto digit : binaryNumber) {
		total = total * 2 + (digit - '0');
	}

	return total;
}
bool numconv::checkBinary(string binaryNumber) {
	for (auto digit : binaryNumber) {
		if (digit != '1' && digit != '0') {
			return false;
		}
	}
	return true;
}
deque<int> numconv::decimalToBinary(int decimalNumber) {
	deque<int> binaryNumber;
	size_t length = 0;

	if (between(decimalNumber, -128, 127)) {
		length = 8;
	} else if (between(decimalNumber, -32768, 32767)) {
		length = 16;
	} else if (between(decimalNumber, -2147483647, 2147483646)) {
		length = 32;
	} else {
		cout << "The given number is too big. Max values are < -2147483648, 2147483647> \n";
	}
	binaryNumber = memoryNotation(length, convert(decimalNumber), decimalNumber >= 0);
	cout << decimalNumber << "  --> ";
	for (auto digit : binaryNumber) {
		cout << digit;
	}
	return binaryNumber;
}

double numconv::binaryToDecimal(string binaryNumber) {
	double decimalNumber = 0;
	/*      if (binaryNumber.find('.') != string::npos) {
					string wholeNumber = binaryNumber.substr(0, binaryNumber.find('.'));
					string fraction = binaryNumber.substr(binaryNumber.find('.') + 1, binaryNumber.length() - binaryNumber.find('.'));
					decimalNumber = convertToWholeDecimal(wholeNumber) + convertToFractionDecimal(fraction);
			} else {
			}*/
	decimalNumber = convertToWholeDecimal(binaryNumber);

	cout << binaryNumber << " --> " << decimalNumber << '\n';
	return decimalNumber;
}
