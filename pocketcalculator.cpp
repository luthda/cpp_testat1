#include "pocketcalculator.h"
#include "calc.h"
#include "sevensegment.h"

#include <stdexcept>
#include <istream>
#include <iterator>
#include <sstream>
#include <string>

static bool isTooBig(int result) {
	return std::to_string(result).length() > 8;
}

void pocketcalculator(std::istream &in, std::ostream &out) {
	std::string inputString{};
	while (getline(in, inputString)) {
		try {
			std::istringstream input{inputString};
			int result = calc(input);
			if (isTooBig(result)) {
				throw std::overflow_error("Result more than eight digits!");
			}
			else{
				printLargeNumber(result, out);
			}
		} catch (std::invalid_argument const &e) {
			printLargeError(out);
		} catch (std::overflow_error const &e) {
			printLargeError(out);
		}
	}
}
