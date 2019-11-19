#include "pocketcalculator.h"

#include <iostream>

int main() {
	while (std::cin) {
		std::cout << "Calculate: \n";
		pocketcalculator(std::cin, std::cout);
	}
}
