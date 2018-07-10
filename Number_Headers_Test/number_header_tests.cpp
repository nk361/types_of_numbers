#include "pch.h"
#include "../Types_of_Numbers/fraction.h"

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
{
	fraction const test = fraction{ -1, -2 } + fraction{ -1 };
	EXPECT_EQ(test.get_mixed(), 0);
	EXPECT_EQ(test.get_numerator(), 1);
	EXPECT_EQ(test.get_denominator(), -2);
}

//ASSERT breaks out of the program if failed, EXPECT does not

int main(int argc, char* argv[])/*char **argv*/
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}