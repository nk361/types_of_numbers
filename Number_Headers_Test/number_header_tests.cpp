#include "pch.h"

#include "../Types_of_Numbers/fraction.h"

TEST(TestCaseName, TestName) {//default test example
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(FractionTests, Fraction_Constructors) {
	fraction const def_constructor;
	EXPECT_EQ(def_constructor.get_numerator(), 0) << "Default fraction constructor set incorrect numerator value";
	EXPECT_EQ(def_constructor.get_denominator(), 1) << "Default fraction constructor set incorrect denominator value";

	fraction const one_param_constructor(5);
	EXPECT_EQ(one_param_constructor.get_numerator(), 5) << "One parameter fraction constructor set incorrect numerator value";
	EXPECT_EQ(one_param_constructor.get_denominator(), 1) << "One parameter fraction constructor set incorrect denominator value";

	fraction const two_param_constructor(1, 2);
	EXPECT_EQ(two_param_constructor.get_numerator(), 1) << "Two parameter fraction constructor set incorrect numerator value";
	EXPECT_EQ(two_param_constructor.get_denominator(), 2) << "Two parameter fraction constructor set incorrect denominator value";

	fraction const two_param_constructor_trig_f(1, -2, false);
	EXPECT_EQ(two_param_constructor_trig_f.get_numerator(), -1) << "Two parameter fraction constructor, without preserved signs, set incorrect numerator value";
	EXPECT_EQ(two_param_constructor_trig_f.get_denominator(), 2) << "Two parameter fraction constructor, without preserved signs, set incorrect denominator value";
	
	fraction const two_param_constructor_trig_t(1, -2, true);
	EXPECT_EQ(two_param_constructor_trig_t.get_numerator(), 1) << "Two parameter fraction constructor, with preserved signs, set incorrect numerator value";
	EXPECT_EQ(two_param_constructor_trig_t.get_denominator(), -2) << "Two parameter fraction constructor, with preserved signs, set incorrect denominator value";

	fraction const three_param_constructor(1, 1, 2);
	EXPECT_EQ(three_param_constructor.get_mixed(), 1) << "Three parameter fraction constructor set incorrect mixed value";
	EXPECT_EQ(three_param_constructor.get_numerator(), 1 + 1 * 2) << "Three parameter fraction constructor set incorrect numerator value";
	EXPECT_EQ(three_param_constructor.get_denominator(), 2) << "Three parameter fraction constructor set incorrect denominator value";

	fraction const three_param_constructor_trig_t(1, 1, -2, true);
	EXPECT_EQ(three_param_constructor_trig_t.get_mixed(true), 1) << "Three parameter fraction constructor, with preserved signs, set incorrect mixed value";
	EXPECT_EQ(three_param_constructor_trig_t.get_numerator(), 1 + 1 * 2) << "Three parameter fraction constructor, with preserved signs, set incorrect numerator value";
	EXPECT_EQ(three_param_constructor_trig_t.get_denominator(), -2) << "Three parameter fraction constructor, with preserved signs, set incorrect denominator value";

	fraction const three_param_constructor_trig_f(1, 1, -2, false);
	EXPECT_EQ(three_param_constructor_trig_f.get_mixed(false), 1 * -1) << "Three parameter fraction constructor, without preserved signs, set incorrect mixed value";
	EXPECT_EQ(three_param_constructor_trig_f.get_numerator(), (1 + 1 * 2) * -1) << "Three parameter fraction constructor, without preserved signs, set incorrect numerator value";
	EXPECT_EQ(three_param_constructor_trig_f.get_denominator(), 2) << "Three parameter fraction constructor, without preserved signs, set incorrect denominator value";

	fraction const three_param_constructor_trig_t_norm_f(1, 5, -2, true, false);
	EXPECT_EQ(three_param_constructor_trig_t_norm_f.get_mixed(true), 1) << "Three parameter fraction constructor, with preserved signs and without normalizing, set incorrect mixed value";
	EXPECT_EQ(three_param_constructor_trig_t_norm_f.get_numerator(), 1 + (-1 * -1) * (-2 * -1)) << "Three parameter fraction constructor, with preserved signs and without normalizing, set incorrect numerator value";
	EXPECT_EQ(three_param_constructor_trig_t_norm_f.get_denominator(), -2) << "Three parameter fraction constructor, with preserved signs and without normalizing, set incorrect denominator value";
	
	fraction const three_param_constructor_trig_t_norm_t(1, 5, -2, true, true);
	EXPECT_EQ(three_param_constructor_trig_t_norm_t.get_mixed(true), 2) << "Three parameter fraction constructor, with preserved signs and with normalizing, set incorrect mixed value";
	EXPECT_EQ(three_param_constructor_trig_t_norm_t.get_numerator(), 5 + (1 + 5 % -2 * -1) * (-2 * -1)) << "Three parameter fraction constructor, with preserved signs and with normalizing, set incorrect numerator value";
	EXPECT_EQ(three_param_constructor_trig_t_norm_t.get_denominator(), -2) << "Three parameter fraction constructor, with preserved signs and with normalizing, set incorrect denominator value";
}

//ASSERT breaks out of the program if failed, EXPECT does not

int main(int argc, char* argv[])/*char **argv*/
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}