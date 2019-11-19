#include "calc.h"
#include "sevensegment.h"
#include "pocketcalculator.h"

#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include <stdexcept>



void test_one_plus_one() {
	auto result = calc(1, 1, '+');
	ASSERT_EQUAL(2, result);
}

void test_ten_minus_one() {
	auto result = calc(10, 1, '-');
	ASSERT_EQUAL(9, result);
}

void test_ten_times_ten() {
	auto result = calc(10, 10, '*');
	ASSERT_EQUAL(100, result);
}

void test_ten_divided_by_five() {
	auto result = calc(10, 5, '/');
	ASSERT_EQUAL(2, result);
}

void test_division_by_zero() {
	ASSERT_THROWS(calc(10, 0, '/'), std::invalid_argument);
}

void test_invalid_operator() {
	ASSERT_THROWS(calc(10, 10, 'x'), std::invalid_argument);
}

void testCalcWithStream() {
	std::istringstream input{"95/5"};
	auto result = calc(input);
	ASSERT_EQUAL(19, result);
}

void testCalcWithStreamZeroDivision() {
	std::istringstream input{"95/0"};
	ASSERT_THROWS(calc(input), std::invalid_argument);
}

void test_ten_mod_two() {
	auto result = calc(10, 2, '%');
	ASSERT_EQUAL(0, result);
}

void testCalcWithStreamModulo() {
	std::istringstream input{"10%2"};
	auto result = calc(input);
	ASSERT_EQUAL(0, result);
}

void test_Print_Zero() {
	std::ostringstream output{};
	printLargeDigit(0, output);
	ASSERT_EQUAL(" - \n"
	               "| |\n"
	               "   \n"
	               "| |\n"
	               " - \n", output.str());
}

void test_Print_Eight() {
	std::ostringstream output{};
	printLargeDigit(8, output);
	ASSERT_EQUAL(" - \n"
	               "| |\n"
	               " - \n"
	               "| |\n"
	               " - \n", output.str());
}

void test_Print_Eighty() {
	std::ostringstream output{};
	printLargeNumber(80, output);
	ASSERT_EQUAL(
			" -  - \n"
			"| || |\n"
			" -    \n"
			"| || |\n"
			" -  - \n", output.str());
}


void test_Print_Negation() {
	std::ostringstream output{};
	printLargeDigit(-8, output);
	ASSERT_EQUAL(
			"    - \n"
			"   | |\n"
			" -  - \n"
			"   | |\n"
			"    - \n", output.str());
}

void test_Print_MinusEighty() {
	std::ostringstream output{};
	printLargeNumber(-80, output);
	ASSERT_EQUAL(
			"    -  - \n"
			"   | || |\n"
			" -  -    \n"
			"   | || |\n"
			"    -  - \n", output.str());
}


void test_Error() {
	std::ostringstream output{};
	printLargeError(output);
	ASSERT_EQUAL(
			" -             \n"
			"|              \n"
			" -  -  -  -  - \n"
			"|  |  |  | ||  \n"
			" -        -    \n", output.str());
}

void test_Print_Eighty_PocketCalc() {
	std::ostringstream output{};
	std::istringstream input{"5*16"};
	pocketcalculator(input, output);
	ASSERT_EQUAL(
			" -  - \n"
			"| || |\n"
			" -    \n"
			"| || |\n"
			" -  - \n", output.str());
}

void test_Print_MinusEighty_PocketCalc() {
	std::ostringstream output{};
	std::istringstream input{"-5*16"};
	pocketcalculator(input, output);
	ASSERT_EQUAL(
			"    -  - \n"
			"   | || |\n"
			" -  -    \n"
			"   | || |\n"
			"    -  - \n", output.str());
}

void test_Print_OverflowError() {
	std::ostringstream output{};
	std::istringstream input{"123456789*2"};
	pocketcalculator(input, output);
	ASSERT_EQUAL(
			" -             \n"
			"|              \n"
			" -  -  -  -  - \n"
			"|  |  |  | ||  \n"
			" -        -    \n", output.str());
}

void test_Print_ZeroDivison() {
	std::ostringstream output{};
	std::istringstream input{"584/0"};
	pocketcalculator(input, output);
	ASSERT_EQUAL(
			" -             \n"
			"|              \n"
			" -  -  -  -  - \n"
			"|  |  |  | ||  \n"
			" -        -    \n", output.str());
}

void test_Print_LargeNrZero() {
	std::ostringstream output{};
	printLargeNumber(0, output);
	ASSERT_EQUAL(" - \n"
	               "| |\n"
	               "   \n"
	               "| |\n"
	               " - \n", output.str());
}

void test_Print_LargeNrEight() {
	std::ostringstream output{};
	printLargeNumber(8, output);
	ASSERT_EQUAL(" - \n"
	               "| |\n"
	               " - \n"
	               "| |\n"
	               " - \n", output.str());
}

void test_Print_NotEnoughArguments() {
	std::ostringstream output{};
	std::istringstream input{"111/"};
	pocketcalculator(input, output);
	ASSERT_EQUAL(
			" -             \n"
			"|              \n"
			" -  -  -  -  - \n"
			"|  |  |  | ||  \n"
			" -        -    \n", output.str());
}

void test_Print_DoubleLine_PocketCalc() {
	std::ostringstream output{};
	std::istringstream input{"-5*16\n10*8"};
	pocketcalculator(input, output);
	ASSERT_EQUAL(
			"    -  - \n"
			"   | || |\n"
			" -  -    \n"
			"   | || |\n"
			"    -  - \n"
			" -  - \n"
			"| || |\n"
			" -    \n"
			"| || |\n"
			" -  - \n", output.str());
}

void test_Print_DoubleLineWithSpaces_PocketCalc() {
	std::ostringstream output{};
	std::istringstream input{"1 * 0\n0 + 1"};
	pocketcalculator(input, output);
	ASSERT_EQUAL(
				 " - \n"
	             "| |\n"
	             "   \n"
	             "| |\n"
	             " - \n"
			 	 "   \n"
            	 "  |\n"
            	 "   \n"
            	 "  |\n"
            	 "   \n", output.str());
}

void thisIsATest() {
	ASSERTM("start writing tests", true);
}


bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	//TODO add your test here
	s.push_back(CUTE(thisIsATest));
	s.push_back(CUTE(test_one_plus_one));
	s.push_back(CUTE(test_invalid_operator));
	s.push_back(CUTE(test_division_by_zero));
	s.push_back(CUTE(test_ten_divided_by_five));
	s.push_back(CUTE(test_ten_times_ten));
	s.push_back(CUTE(test_ten_minus_one));
	s.push_back(CUTE(testCalcWithStream));
	s.push_back(CUTE(testCalcWithStreamZeroDivision));
	s.push_back(CUTE(test_Print_Zero));
	s.push_back(CUTE(test_Print_Eight));
	s.push_back(CUTE(test_Print_Eighty));
	s.push_back(CUTE(test_Print_Negation));
	s.push_back(CUTE(test_Print_MinusEighty));
	s.push_back(CUTE(test_Error));
	s.push_back(CUTE(test_Print_Eighty_PocketCalc));
	s.push_back(CUTE(test_Print_OverflowError));
	s.push_back(CUTE(test_Print_ZeroDivison));
	s.push_back(CUTE(test_Print_MinusEighty_PocketCalc));
	s.push_back(CUTE(test_Print_LargeNrZero));
	s.push_back(CUTE(test_Print_LargeNrEight));
	s.push_back(CUTE(test_Print_NotEnoughArguments));
	s.push_back(CUTE(test_Print_DoubleLine_PocketCalc));
	s.push_back(CUTE(testCalcWithStreamModulo));
	s.push_back(CUTE(test_ten_mod_two));
	s.push_back(CUTE(test_Print_DoubleLineWithSpaces_PocketCalc));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner = cute::makeRunner(lis, argc, argv);
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
