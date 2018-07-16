#include "pch.h"
#include "../Types_of_Numbers/fraction.h"
#include "../Types_of_Numbers/term.h"
#include "../Types_of_Numbers/polynomial.h"

TEST(GeneralMathFunctioonTests, LCMTests)
{
	EXPECT_EQ(general_math_functions::lcm(-2, 1), -2);
	EXPECT_EQ(general_math_functions::lcm(1, -2), -2);
}

TEST(FractionHeaderTests, FractionConstructors) {
	{//end brackets should delete temporary objects when exiting scope
		fraction const def_constructor;
		EXPECT_EQ(def_constructor.get_mixed(), 0) << "Default fraction constructor set incorrect mixed value; value should always be zero";
		EXPECT_EQ(def_constructor.get_numerator(), 0) << "Default fraction constructor set incorrect numerator value";
		EXPECT_EQ(def_constructor.get_denominator(), 1) << "Default fraction constructor set incorrect denominator value";
	}
	{
		fraction const one_param_constructor{ 5 };
		EXPECT_EQ(one_param_constructor.get_mixed(), 5) << "One parameter fraction constructor's mixed value was not calculated correctly";
		EXPECT_EQ(one_param_constructor.get_numerator(), 5) << "One parameter fraction constructor set incorrect numerator value";
		EXPECT_EQ(one_param_constructor.get_denominator(), 1) << "One parameter fraction constructor set incorrect denominator value";
	
		fraction const one_param_constructor_n_n{ -35 };
		EXPECT_EQ(one_param_constructor_n_n.get_mixed(), one_param_constructor_n_n.get_numerator()) << "One parameter fraction constructor with a negative value had unequal calculated mixed value and/or set numerator value";
		EXPECT_EQ(one_param_constructor_n_n.get_denominator(), 1) << "One parameter fraction constructor, with negative numerator, set incorrect denominator value";
	}
	{
		fraction const two_param_constructor{ 1, 2 };
		EXPECT_EQ(two_param_constructor.get_numerator(), 1) << "Two parameter fraction constructor set incorrect numerator value";
		EXPECT_EQ(two_param_constructor.get_denominator(), 2) << "Two parameter fraction constructor set incorrect denominator value";
	
		fraction const two_param_constructor_n_d{ 2, -3 };
		EXPECT_EQ(two_param_constructor_n_d.get_numerator(), 2) << "Two parameter fraction constructor, with negative denominator, set incorrect numerator value";
		EXPECT_EQ(two_param_constructor_n_d.get_denominator(), -3) << "Two parameter fraction constructor, with negative denominator, set incorrect denominator value";
	
		fraction const two_param_constructor_n_n_n_d{ -2, -3 };
		EXPECT_EQ(two_param_constructor_n_n_n_d.get_numerator(), -2) << "Two parameter fraction constructor, with negative numerator and negative denominator, set incorrect numerator value";
		EXPECT_EQ(two_param_constructor_n_n_n_d.get_denominator(), -3) << "Two parameter fraction constructor, with negative numerator and negative denominator, set incorrect denominator value";
	}
	{
		fraction const three_param_constructor{ 1, 1, 2 };
		EXPECT_EQ(three_param_constructor.get_mixed(), 1) << "Three parameter fraction constructor calculated incorrect mixed value";
		EXPECT_EQ(three_param_constructor.get_numerator(), 1 + 1 * 2) << "Three parameter fraction constructor set incorrect numerator value";
		EXPECT_EQ(three_param_constructor.get_denominator(), 2) << "Three parameter fraction constructor set incorrect denominator value";
	
		fraction const three_param_constructor_n_m_n_n_n_d{ -1, -1, -2 };
		EXPECT_EQ(three_param_constructor_n_m_n_n_n_d.get_mixed(), 0) << "Three parameter fraction constructor, with negative mixed, negative numerator, and negative denominator, calculated incorrect mixed value";
		EXPECT_EQ(three_param_constructor_n_m_n_n_n_d.get_numerator(), -1 + -1 * -2) << "Three parameter fraction constructor, with negative mixed, negative numerator, and negative denominator, set incorrect numerator value";
		EXPECT_EQ(three_param_constructor_n_m_n_n_n_d.get_denominator(), -2) << "Three parameter fraction constructor, with negative mixed, negative numerator, and negative denominator, set incorrect denominator value";
	
		fraction const three_param_constructor_n_m{ -1, 1, 2 };
		EXPECT_EQ(three_param_constructor_n_m.get_mixed(), 0) << "Three parameter fraction constructor, with negative mixed, calculated incorrect mixed value";
		EXPECT_EQ(three_param_constructor_n_m.get_numerator(), 1 + -1 * 2) << "Three parameter fraction constructor, with negative mixed, set incorrect numerator value";
		EXPECT_EQ(three_param_constructor_n_m.get_denominator(), 2) << "Three parameter fraction constructor, with negative mixed, set incorrect denominator value";
	
		fraction const three_param_constructor_n_n{ 1, -1, 2 };
		EXPECT_EQ(three_param_constructor_n_n.get_mixed(), 0) << "Three parameter fraction constructor, with negative numerator, calculated incorrect mixed value";
		EXPECT_EQ(three_param_constructor_n_n.get_numerator(), -1 + 1 * 2) << "Three parameter fraction constructor, with negative numerator, set incorrect numerator value";
		EXPECT_EQ(three_param_constructor_n_n.get_denominator(), 2) << "Three parameter fraction constructor, with negative numerator, set incorrect denominator value";
	
		fraction const three_param_constructor_n_m_n_n{ -1, -1, 2 };
		EXPECT_EQ(three_param_constructor_n_m_n_n.get_mixed(), -1) << "Three parameter fraction constructor, with negative mixed and negative numerator, calculated incorrect mixed value";
		EXPECT_EQ(three_param_constructor_n_m_n_n.get_numerator(), -1 + -1 * 2) << "Three parameter fraction constructor, with negative mixed and negative numerator, set incorrect numerator value";
		EXPECT_EQ(three_param_constructor_n_m_n_n.get_denominator(), 2) << "Three parameter fraction constructor, with negative mixed and negative numerator, set incorrect denominator value";
	}
	{
		fraction const three_param_constructor_norm_t_norm_unneeded{ 1, 1, 2, true };
		EXPECT_EQ(three_param_constructor_norm_t_norm_unneeded.get_mixed(), 1) << "Three parameter fraction constructor, with unneeded normalizing being normalized, calculated incorrect mixed value";
		EXPECT_EQ(three_param_constructor_norm_t_norm_unneeded.get_numerator(), 1 + 1 * 2) << "Three parameter fraction constructor, with unneeded normalizing being normalized, set incorrect numerator value";
		EXPECT_EQ(three_param_constructor_norm_t_norm_unneeded.get_denominator(), 2) << "Three parameter fraction constructor, with unneeded normalizing being normalized, set incorrect denominator value";
	
		fraction const three_param_constructor_norm_f_norm_unneeded{ 1, 1, 2, false };
		EXPECT_EQ(three_param_constructor_norm_f_norm_unneeded.get_mixed(), 1) << "Three parameter fraction constructor, with unneeded normalizing not being normalized, calculated incorrect mixed value";
		EXPECT_EQ(three_param_constructor_norm_f_norm_unneeded.get_numerator(), 1 + 1 * 2) << "Three parameter fraction constructor, with unneeded normalizing not being normalized, set incorrect numerator value";
		EXPECT_EQ(three_param_constructor_norm_f_norm_unneeded.get_denominator(), 2) << "Three parameter fraction constructor, with unneeded normalizing not being normalized, set incorrect denominator value";
	
		fraction const three_param_constructor_norm_t_norm_needed{ 1, 3, 2, true };
		EXPECT_EQ(three_param_constructor_norm_t_norm_needed.get_mixed(), 2) << "Three parameter fraction constructor, with needed normalizing being normalized, calculated incorrect mixed value";
		EXPECT_EQ(three_param_constructor_norm_t_norm_needed.get_numerator(), 3 % 2 + 2 * 2) << "Three parameter fraction constructor, with needed normalizing being normalized, set incorrect numerator value";
		EXPECT_EQ(three_param_constructor_norm_t_norm_needed.get_denominator(), 2) << "Three parameter fraction constructor, with needed normalizing being normalized, set incorrect denominator value";
	
		fraction const three_param_constructor_norm_f_norm_needed{ 1, 3, 2, false };
		EXPECT_EQ(three_param_constructor_norm_f_norm_needed.get_mixed(), 1) << "Three parameter fraction constructor, with needed normalizing not being normalized, calculated incorrect mixed value";
		EXPECT_EQ(three_param_constructor_norm_f_norm_needed.get_numerator(), 3 % 2 + 1 * 2) << "Three parameter fraction constructor, with needed normalizing not being normalized, set incorrect numerator value";
		EXPECT_EQ(three_param_constructor_norm_f_norm_needed.get_denominator(), 2) << "Three parameter fraction constructor, with needed normalizing not being normalized, set incorrect denominator value";
	}
	{
		fraction const one_param_decimal_conversion_constructor{ static_cast<double>(0.15) };
		EXPECT_DOUBLE_EQ(one_param_decimal_conversion_constructor.to_decimal(), static_cast<double>(0.15)) << "One parameter fraction decimal conversion constructor did not convert back to the original double value";
		EXPECT_EQ(one_param_decimal_conversion_constructor.get_mixed(), 0) << "One parameter fraction decimal conversion constructor calculated incorrect mixed value";
		EXPECT_EQ(one_param_decimal_conversion_constructor.get_numerator(), 15) << "One parameter fraction decimal conversion constructor set incorrect numerator value";
		EXPECT_EQ(one_param_decimal_conversion_constructor.get_denominator(), 100) << "One parameter fraction decimal conversion constructor set incorrect denominator value";
	
		fraction const one_param_decimal_conversion_constructor_mixed{ static_cast<double>(5.15) };
		EXPECT_DOUBLE_EQ(one_param_decimal_conversion_constructor_mixed.to_decimal(), static_cast<double>(5.15)) << "One parameter fraction decimal conversion constructor, with mixed value, did not convert back to the original double value";
		EXPECT_EQ(one_param_decimal_conversion_constructor_mixed.get_mixed(), 5) << "One parameter fraction decimal conversion constructor, with mixed value, calculated incorrect mixed value";
		EXPECT_EQ(one_param_decimal_conversion_constructor_mixed.get_numerator(), 15 + 5 * 100) << "One parameter fraction decimal conversion constructor, with mixed value, set incorrect numerator value";
		EXPECT_EQ(one_param_decimal_conversion_constructor_mixed.get_denominator(), 100) << "One parameter fraction decimal conversion constructor, with mixed value, set incorrect denominator value";
	
		fraction const one_param_decimal_conversion_constructor_big_mixed{ static_cast<double>(750.15) };
		EXPECT_DOUBLE_EQ(one_param_decimal_conversion_constructor_big_mixed.to_decimal(), static_cast<double>(750.15)) << "One parameter fraction decimal conversion constructor, with large mixed to test increased reduction of exponent, did not convert back to the original double value";
		EXPECT_EQ(one_param_decimal_conversion_constructor_big_mixed.get_mixed(), 750) << "One parameter fraction decimal conversion constructor, with large mixed to test increased reduction of exponent, calculated incorrect mixed value";
		EXPECT_EQ(one_param_decimal_conversion_constructor_big_mixed.get_numerator(), 15 + 750 * 100) << "One parameter fraction decimal conversion constructor, with large mixed to test increased reduction of exponent, set incorrect numerator value";
		EXPECT_EQ(one_param_decimal_conversion_constructor_big_mixed.get_denominator(), 100) << "One parameter fraction decimal conversion constructor, with large mixed to test increased reduction of exponent, set incorrect denominator value";
	
		fraction const one_param_decimal_conversion_constructor_n_n{ static_cast<double>(-0.15) };
		EXPECT_DOUBLE_EQ(one_param_decimal_conversion_constructor_n_n.to_decimal(), static_cast<double>(-0.15)) << "One parameter fraction decimal conversion constructor, with negative numerator, did not convert back to the original double value";
		EXPECT_EQ(one_param_decimal_conversion_constructor_n_n.get_mixed(), 0) << "One parameter fraction decimal conversion constructor, with negative numerator, calculated incorrect mixed value";
		EXPECT_EQ(one_param_decimal_conversion_constructor_n_n.get_numerator(), -15) << "One parameter fraction decimal conversion constructor, with negative numerator, set incorrect numerator value";
		EXPECT_EQ(one_param_decimal_conversion_constructor_n_n.get_denominator(), 100) << "One parameter fraction decimal conversion constructor, with negative numerator, set incorrect denominator value";
	
		fraction const one_param_decimal_conversion_constructor_mixed_n_m{ static_cast<double>(-5.15) };
		EXPECT_DOUBLE_EQ(one_param_decimal_conversion_constructor_mixed_n_m.to_decimal(), static_cast<double>(-5.15)) << "One parameter fraction decimal conversion constructor, with negative mixed, did not convert back to the original double value";
		EXPECT_EQ(one_param_decimal_conversion_constructor_mixed_n_m.get_mixed(), -5) << "One parameter fraction decimal conversion constructor, with negative mixed, calculated incorrect mixed value";
		EXPECT_EQ(one_param_decimal_conversion_constructor_mixed_n_m.get_numerator(), -515) << "One parameter fraction decimal conversion constructor, with negative mixed, set incorrect numerator value";
		EXPECT_EQ(one_param_decimal_conversion_constructor_mixed_n_m.get_denominator(), 100) << "One parameter fraction decimal conversion constructor, with negative mixed, set incorrect denominator value";
	
		fraction const one_param_decimal_conversion_constructor_const{ static_cast<double>(42) };
		EXPECT_DOUBLE_EQ(one_param_decimal_conversion_constructor_const.to_decimal(), static_cast<double>(42)) << "One parameter fraction decimal conversion constructor, with only a constant, did not convert back to the original double value";
		EXPECT_EQ(one_param_decimal_conversion_constructor_const.get_mixed(), 42) << "One parameter fraction decimal conversion constructor, withonly a constant, calculated incorrect mixed value";
		EXPECT_EQ(one_param_decimal_conversion_constructor_const.get_numerator(), 42) << "One parameter fraction decimal conversion constructor, with only a constant, set incorrect numerator value";
		EXPECT_EQ(one_param_decimal_conversion_constructor_const.get_denominator(), 1) << "One parameter fraction decimal conversion constructor, with constant mixed, set incorrect denominator value";
	}
	{
		fraction const one_param_string_conversion_constructor_one{ "10" };
		EXPECT_STREQ(one_param_string_conversion_constructor_one.to_string().c_str(), "10") << "One parameter fraction string conversion constructor, with one value, did not convert back to the originial string value";
		EXPECT_EQ(one_param_string_conversion_constructor_one.get_mixed(), 10) << "One parameter fraction string conversion constructor, with one value, calculated incorrect mixed value";
		EXPECT_EQ(one_param_string_conversion_constructor_one.get_numerator(), 0 + 10 * 1) << "One parameter fraction string conversion constructor, with one value, set incorrect numerator value";
		EXPECT_EQ(one_param_string_conversion_constructor_one.get_denominator(), 1) << "One parameter fraction string conversion sonctructor, with one value, set incorrect denominator value";
	
		fraction const one_param_string_conversion_constructor_two{ "1/2" };
		EXPECT_STREQ(one_param_string_conversion_constructor_two.to_string().c_str(), "1/2") << "One parameter fraction string conversion constructor, with two values, did not convert back to the originial string value";
		EXPECT_EQ(one_param_string_conversion_constructor_two.get_mixed(), 0) << "One parameter fraction string conversion constructor, with two values, calculated incorrect mixed value";
		EXPECT_EQ(one_param_string_conversion_constructor_two.get_numerator(), 1) << "One parameter fraction string conversion constructor, with two values, set incorrect numerator value";
		EXPECT_EQ(one_param_string_conversion_constructor_two.get_denominator(), 2) << "One parameter fraction string conversion sonctructor, with two values, set incorrect denominator value";
	
		fraction const one_param_string_conversion_constructor_three{ "5(1/2)" };
		EXPECT_STREQ(one_param_string_conversion_constructor_three.to_string().c_str(), "5(1/2)") << "One parameter fraction string conversion constructor, with three values, did not convert back to the originial string value";
		EXPECT_EQ(one_param_string_conversion_constructor_three.get_mixed(), 5) << "One parameter fraction string conversion constructor, with three values, calculated incorrect mixed value";
		EXPECT_EQ(one_param_string_conversion_constructor_three.get_numerator(), 1 + 5 * 2) << "One parameter fraction string conversion constructor, with three values, set incorrect numerator value";
		EXPECT_EQ(one_param_string_conversion_constructor_three.get_denominator(), 2) << "One parameter fraction string conversion constructor, with three values, set incorrect denominator value";
	
		fraction const one_param_string_conversion_constructor_three_n_m_n_n{ "-5(-1/2)" };
		EXPECT_STREQ(one_param_string_conversion_constructor_three_n_m_n_n.to_string().c_str(), "-5(-1/2)") << "One parameter fraction string conversion constructor, with three values, negative mixed, and negative numerator, did not convert back to the originial string value";
		EXPECT_EQ(one_param_string_conversion_constructor_three_n_m_n_n.get_mixed(), -5) << "One parameter fraction string conversion constructor, with three values, negative mixed, and negative numerator, calculated incorrect mixed value";
		EXPECT_EQ(one_param_string_conversion_constructor_three_n_m_n_n.get_numerator(), -1 + -5 * 2) << "One parameter fraction string conversion constructor, with three values, negative mixed, and negative numerator, set incorrect numerator value";
		EXPECT_EQ(one_param_string_conversion_constructor_three_n_m_n_n.get_denominator(), 2) << "One parameter fraction string conversion constructor, with three values, negative mixed, and negative numerator, set incorrect denominator value";
	}
}

TEST(FractionHeaderTests, AdditionOperators)//this was just added to be sure the three param constructor's addition wasn't the problem
{//I could either use one test fixture that all operators use
	fraction const test = fraction{ -1, -2 } + fraction{ -1 };
	EXPECT_EQ(test.get_mixed(), 0);
	EXPECT_EQ(test.get_numerator(), 1);
	EXPECT_EQ(test.get_denominator(), -2);

	fraction test2;
	test2 += 5;
	EXPECT_EQ(test2.get_mixed(), 5);
	EXPECT_EQ(test2.get_numerator(), 5);
	EXPECT_EQ(test2.get_denominator(), 1);
}

TEST(TermHeaderTests, TermConstructors)
{
	term const def_constructor;
	EXPECT_EQ(def_constructor.get_coefficient(), 0);
	EXPECT_TRUE(def_constructor.get_variables().empty());
	EXPECT_TRUE(def_constructor.get_exponents().empty());

	term const constant_one_param{ 10 };
	EXPECT_EQ(constant_one_param.get_coefficient(), 10);
	EXPECT_TRUE(constant_one_param.get_variables().empty());
	EXPECT_TRUE(constant_one_param.get_exponents().empty());

	term const one_var{ 't' };
	EXPECT_EQ(one_var.get_coefficient(), 1);
	EXPECT_EQ(one_var.get_variables(), std::vector<char>{ 't' });
	EXPECT_EQ(one_var.get_exponents(), std::vector<int>{ 1 });

	term const one_var_one_exponenet{ 'u', 170 };
	EXPECT_EQ(one_var_one_exponenet.get_coefficient(), 1);
	EXPECT_EQ(one_var_one_exponenet.get_variables(), std::vector<char>{ 'u' });
	EXPECT_EQ(one_var_one_exponenet.get_exponents(), std::vector<int>{ 170 });

	term const many_vars_no_exponenets{ std::vector<char>{'b', 'v', 'z'} };
	EXPECT_EQ(many_vars_no_exponenets.get_coefficient(), 1);
	ASSERT_EQ(many_vars_no_exponenets.get_variables().size(), (std::vector<char>{ 'b', 'v', 'z' }).size());
	for (size_t index = 0; index < many_vars_no_exponenets.get_variables().size(); ++index)
		EXPECT_EQ(many_vars_no_exponenets.get_variables()[index], (std::vector<char>{ 'b', 'v', 'z' })[index]);
	ASSERT_EQ(many_vars_no_exponenets.get_exponents().size(), (std::vector<int>{ 1, 1, 1 }).size());
	for (size_t index = 0; index < many_vars_no_exponenets.get_exponents().size(); ++index)
		EXPECT_EQ(many_vars_no_exponenets.get_exponents()[index], 1);

	term const many_vars_many_exponenets{ { 'e', 'w', 'a' }, { 60, 700, 4 } };
	EXPECT_EQ(many_vars_many_exponenets.get_coefficient(), 1);
	ASSERT_EQ(many_vars_many_exponenets.get_variables().size(), (std::vector<char>{ 'e', 'w', 'a' }).size());
	for (size_t index = 0; index < many_vars_many_exponenets.get_variables().size(); ++index)
		EXPECT_EQ(many_vars_many_exponenets.get_variables()[index], (std::vector<char>{ 'e', 'w', 'a' })[index]);
	ASSERT_EQ(many_vars_many_exponenets.get_exponents().size(), (std::vector<int>{ 60, 700, 4 }).size());
	for (size_t index = 0; index < many_vars_many_exponenets.get_exponents().size(); ++index)
		EXPECT_EQ(many_vars_many_exponenets.get_exponents()[index], (std::vector<int>{ 60, 700, 4 })[index]);

	term const coefficient_and_one_var{ 20, 'x' };
	EXPECT_EQ(coefficient_and_one_var.get_coefficient(), 20);
	EXPECT_EQ(coefficient_and_one_var.get_variables(), std::vector<char>{ 'x' });
	EXPECT_EQ(coefficient_and_one_var.get_exponents(), std::vector<int>{ 1 });

	term const coefficient_var_with_exponent{ 19, 'y', 6 };
	EXPECT_EQ(coefficient_var_with_exponent.get_coefficient(), 19);
	EXPECT_EQ(coefficient_var_with_exponent.get_variables(), std::vector<char>{ 'y' });
	EXPECT_EQ(coefficient_var_with_exponent.get_exponents(), std::vector<int>{ 6 });

	term const coefficient_var_no_exponenet{ 18, 'p' };
	EXPECT_EQ(coefficient_var_no_exponenet.get_coefficient(), 18);
	EXPECT_EQ(coefficient_var_no_exponenet.get_variables(), std::vector<char>{ 'p' });
	EXPECT_EQ(coefficient_var_no_exponenet.get_exponents(), std::vector<int>{ 1 });

	term const coefficient_vars_no_exponents{ 15, { 'q', 'u' } };
	EXPECT_EQ(coefficient_vars_no_exponents.get_coefficient(), 15);
	ASSERT_EQ(coefficient_vars_no_exponents.get_variables().size(), (std::vector<char>{ 'q', 'u' }).size());
	for (size_t index = 0; index < coefficient_vars_no_exponents.get_variables().size(); ++index)
		EXPECT_EQ(coefficient_vars_no_exponents.get_variables()[index], (std::vector<char>{ 'q', 'u' })[index]);
	ASSERT_EQ(coefficient_vars_no_exponents.get_exponents().size(), (std::vector<char>{ 1, 1 }).size());
	for (size_t index = 0; index < coefficient_vars_no_exponents.get_exponents().size(); ++index)
		EXPECT_EQ(coefficient_vars_no_exponents.get_exponents()[index], 1);

	term const coeffiecient_vars_and_exponenets{ 105, { 'p', 't', 'w', 'f', 's' }, { 10, 7, 34, 19, 16 } };
	EXPECT_EQ(coeffiecient_vars_and_exponenets.get_coefficient(), 105);
	ASSERT_EQ(coeffiecient_vars_and_exponenets.get_variables().size(), std::vector<char>({ 'p', 't', 'w', 'f', 's' }).size());
	for (size_t index = 0; index < coeffiecient_vars_and_exponenets.get_variables().size(); ++index)
		EXPECT_EQ(coeffiecient_vars_and_exponenets.get_variables()[index], (std::vector<char>{ 'p', 't', 'w', 'f', 's' })[index]);
	ASSERT_EQ(coeffiecient_vars_and_exponenets.get_exponents().size(), (std::vector<int>{ 10, 7, 34, 19, 16 }).size());
	for (size_t index = 0; index < coeffiecient_vars_and_exponenets.get_exponents().size(); ++index)
		EXPECT_EQ(coeffiecient_vars_and_exponenets.get_exponents()[index], (std::vector<int>{ 10, 7, 34, 19, 16 })[index]);

	//term const string_constant{ "0" };//Going to approach string constructor with test driven development
	//EXPECT_EQ(string_constant.get_coefficient(), 0);
	//EXPECT_TRUE(string_constant.get_variables().empty());
	//EXPECT_TRUE(string_constant.get_exponents().empty());
}

TEST(PolynomialHeaderTests, PolynomialConstructors)
{
	
}

//ASSERT breaks out of the program if failed, EXPECT does not

int main(int argc, char* argv[])/*char **argv*/
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}