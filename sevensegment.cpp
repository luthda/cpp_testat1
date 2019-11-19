#include "sevensegment.h"

#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>

const std::vector<std::vector<std::string>> digitVector {
	{" - ", "   ", " - ", " - ", "   ", " - ", " - ", " - ", " - ", " - ", "   "},
	{"| |", "  |", "  |", "  |", "| |", "|  ", "|  ", "  |", "| |", "| |", "   "},
	{"   ", "   ", " - ", " - ", " - ", " - ", " - ", "   ", " - ", " - ", " - "},
	{"| |", "  |", "|  ", "  |", "  |", "  |", "| |", "  |", "| |", "  |", "   "},
	{" - ", "   ", " - ", " - ", "   ", " - ", " - ", "   ", " - ", " - ", "   "}
};

const std::vector<std::vector<std::string>> errorVector {
	{
	 " -             ",
	 "|              ",
	 " -  -  -  -  - ",
	 "|  |  |  | ||  ",
	 " -        -    "
	}
};

static std::vector<int> generateIntVector(int const inputNumber) {
	int number{inputNumber};
	std::vector<int> inputDigits{};
	for (int j = 0; number != 0; ++j) {
		inputDigits.push_back(number % 10);
		number /= 10;
	}
	std::reverse(std::begin(inputDigits), std::end(inputDigits));
	return inputDigits;
}

void printLargeDigit(int i, std::ostream &out) {
	if (i < 0) {
		int const posInput{i * -1};
		std::for_each(std::cbegin(digitVector), std::cend(digitVector), [&out, &posInput](auto const vectorLine) {
			out << vectorLine[10] << vectorLine[posInput] << "\n";
		});
	}
	else {
		std::for_each(std::cbegin(digitVector), std::cend(digitVector), [&out, &i](auto const vectorLine) {
			out << vectorLine[i] << "\n";
		});
	}
}

void printLargeNumber(int i, std::ostream &out) {
	if (i >= 0 && i < 10) {
		printLargeDigit(i, out);
		return;
	}
	std::vector<int> digits{};
	if (i < 0) {
		int const posInput{i * -1};
		digits = generateIntVector(posInput);
		std::for_each(std::cbegin(digitVector), std::cend(digitVector), [&out, &digits](auto const vectorLine) {
			out << vectorLine[10];
			std::for_each(std::cbegin(digits), std::cend(digits), [&out, &vectorLine](auto const index) {
				out << vectorLine[index];
			});
			out << "\n";
		});
	} else {
		digits = generateIntVector(i);
		std::for_each(std::cbegin(digitVector), std::cend(digitVector), [&out, &digits](auto const vectorLine) {
			std::for_each(std::cbegin(digits), std::cend(digits), [&out, &vectorLine](auto const index) {
				out << vectorLine[index];
			});
			out << "\n";
		});
	}
}

void printLargeError(std::ostream &out) {
	std::ostream_iterator<std::string> outIterator{out , "\n"};
	std::copy(std::cbegin(errorVector[0]), std::cend(errorVector[0]), outIterator);
}
