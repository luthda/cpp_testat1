#include "calc.h"

#include <stdexcept>
#include <istream>

int calc(int lhs, int rhs, char op) {
	//TODO Implement functionality
	int result{0};
	switch (op) {
		case '+':
			result = lhs + rhs;
			break;
		case '-':
			result = lhs - rhs;
			break;
		case '*':
			result = lhs * rhs;
			break;
		case '/':
			if (rhs == 0) {
				throw std::invalid_argument("Division by zero condition!");
			}
			else {
				result = lhs / rhs;
			}
			break;
		case '%':
			if (rhs == 0) {
				throw std::invalid_argument("Modulo by zero condition!");
			}
			else {
				result = lhs % rhs;
			}
			break;
		default:
			throw std::invalid_argument("No valid operator!");
			break;
	}
	return result;
}

int calc(std::istream& in) {
	int lhs{};
	int rhs{};
	char op{};
	if (in >> lhs >> op >> rhs) {
		return calc(lhs, rhs, op);
	}
	else {
		throw std::invalid_argument("Invalid input!");
	}
}
