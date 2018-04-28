// Types_of_Numbers.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "polynomial.h"


int main()
{
	term test{ -5,{ 'x', 'y', 'z' },{ 5, 2, 1 } };
	term test2{ -6,{ 'x', 'y', 'z' },{ 5, 2, 1 } };
	term test3{ 2,{ 'x', 'y' },{ 5, 2 } };
	term test4{ 4,{ 'x', 'y' },{ 5, 7 } };
	term test5{ -12,{ 'y' },{ 13 } };
	term test6{ -12,{ 'y' },{ 13 } };
	term test7{ -1,{ 'z' },{ 8 } };
	term test8{ -1 };
	term test9{ 14,{},{} };
	term test11{ 5,{ 'v', 'w', 'x', 'y', 'z' },{ 4, 2, 1, 3, 3 } };
	term test12{ 65,{ 't' },{ 14 } };
	polynomial test10 { test, test2, test3, test4, test5, test6, test7, test8, test9, test11, test12 };
	//std::cout << test10 << std::endl;
	//test10.order();
	//std::cout << test10 << std::endl;
	//test10.combine_like_terms();
	//std::cout << test10 << std::endl;

	//term test13{ "-5x^(5)y^(100)m^(15)r^(17)" };
	//term test15{ "5" };
	//std::cout << test15 << std::endl << std::endl << std::endl;
	/*std::cout << test13.get_coefficient() << std::endl;
	std::cout << test13.get_variables().size() << std::endl;
	std::cout << test13.get_exponents().size() << std::endl;
	std::cout << test13 << std::endl;*/

	polynomial test14{ "-5 - 5x^(5)y^(2)z + 10x^(3)y^(2)z^(7) - 21x^(5) - 6x^(8)y^(7) + 200y^(12)gfdse^(3)tu - x^(2) + z^(13) - 5 + z^(13)" };
	/*std::cout << test14.get_terms()[0].get_coefficient() << std::endl;
	std::cout << test14.get_terms()[4] << std::endl;
	std::cout << test14.get_terms()[4].get_coefficient() << std::endl;
	std::cout << test14.get_terms()[5].get_variables()[5] << " to the power of " << test14.get_terms()[5].get_exponents()[5] << std::endl;
	std::cout << test14 << std::endl;
	std::cout << test14.combine_like_terms().order() << std::endl;*/

	//std::cout << std::endl << Polynomial::combine_polynomials(test10, test14) << std::endl;
	std::cout << test10 + test14 << std::endl;
	std::cout << test10 - test14 << std::endl;
	std::cout << test9 * test8 << std::endl;
	std::cout << test5 * test12 << std::endl;
	std::cout << test5 * test6 << std::endl;
	std::cout << test10 * test14 << std::endl;

	std::cout << std::endl << (test10 * test14).combine_like_terms().order() << std::endl;
	//for (int i = 0; i < utility_functions::add_missing({ 'x', 'y', 'q' }, { 'y', 'z', 'p' }).size(); i++)
	//std::cout << utility_functions::add_missing({ 'x', 'y', 'q' }, { 'y', 'z', 'p' })[i] << std::endl;
	//std::cout << test14 << std::endl;//subtraction did not change the original
	/*for (int i = 0; i < math_functions::fibonacci(50).size(); i++)
	std::cout << math_functions::fibonacci(50)[i] << std::endl;*/
	//std::cout << test14 << std::endl;


	//term test13{ "-5acsdfw^(10)" };
	//std::cout << test13 << std::endl;

	//std::cout << test << std::endl;
	//if (test.checker.plusAndMinus(test, test2))
	//std::cout << test + test2 << std::endl;
	//if (test.checker.plusAndMinus(test, test2))
	//std::cout << test - test2 << std::endl;


	//Factorial test{0}; //working test code
	//std::cout << test << " = " << test.solve(test.getNum()) << std::endl;
	//std::cout << "Operations done: " << test.expanded() << std::endl;

	//Radical test{ 2, 27*4, 3 };
	//std::cout << test.toString() << std::endl;
	//std::cout << test.simplify().toString() << std::endl;

	//std::cout << mathFunctions::lcm(140, 72) << std::endl; //working lcm, gcd, and factorize tests
	//std::cout << mathFunctions::gcd(140, 15) << std::endl;
	//std::cout << mathFunctions::gcd({ 72, 48, 54 }) << std::endl;
	//std::cout << mathFunctions::gcd({ 72, 48, 54, 18, 30, 21 }) << std::endl;
	//std::cout << mathFunctions::gcd({ 72, 48, 54, 18, 30, 42 }) << std::endl;
	//std::cout << mathFunctions::lcm({ 140, 72 }) << std::endl;
	//std::cout << mathFunctions::lcm({ 6, 8, 15 }) << std::endl;
	//for (int i = 0; i < mathFunctions::factorize(100).size(); i++)
	//std::cout << mathFunctions::factorize(100)[i];

	std::cin.get();
	std::cin.get();
	return 0;
}