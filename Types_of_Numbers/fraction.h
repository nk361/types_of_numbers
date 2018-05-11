#pragma once
#include "stdafx.h"

class fraction
{
	int numerator_;
	int denominator_;
public:
	fraction() { this->set_numerator(0); this->set_denominator(1); }
	fraction(int const& num, int const& den) { this->set_numerator(num); this->set_denominator(den); }
	fraction(int const& mixed, int const& num, int const& den) { this->set_numerator(num); this->set_denominator(den); this->set_mixed(mixed); }
	/**
	 * \brief This constructor converts a double to a fraction type.
	 * \param dec refrence to constant decimal number
	 * 
	 * A loop is used to look for the first number from right to left of the decimal parameter.
	 * Once found, it sets the numerator and denominator to the decimal over one (dec/1) multiplied by ten to a power relative to their position.
	 * This moves the numerator to the right of the decimal point and moves the denominator the same amount with it.
	 */
	fraction(double const& dec)
	{//TODO I've seen a way to convert decimals to fractions with repeating values, but I think I'd like to make a decimal class with more accuracy to notice repeating values
		size_t i;
		for (i = std::to_string(dec).size() - 1; i >= 0; i--)
			if (std::to_string(dec)[i] != '0')
				break;
		this->set_numerator(static_cast<int>(dec * pow(10, i - 1)));
		this->set_denominator(static_cast<int>(1 * pow(10, i - 1)));
	}
	/**
	 * \brief This constructor converts a string into a fraction object
	 * \param frac a formatted string with fraction data
	 * 
	 * A string in the format mixed coefficient whole number(numerator/denominator) or just numerator/denominator is sent in as a param.
	 * The position of the first of two parentheses is stored if it exists or otherwise std::string::npos if not found.
	 * Then the position of the division symbol is stored which should be found in all cases.
	 * The numerator is set to the position before the division symbol and after the first parenthese if it was found.
	 * The denominator is set to the position after the division symbol, but needs to know if it was a mixed number to know whether to include the final character in the string.
	 * Lastly, because the mixed number value relies on the numerator and denominator values, the mixed number is set if the first parenthese was found.
	 */
	fraction(std::string frac)
	{
		std::string::size_type const open_parenth = frac.find('(');
		std::string::size_type const slash = frac.find('/');
		
		this->set_numerator(stoi(frac.substr(open_parenth == std::string::npos ? 0 : open_parenth + 1, open_parenth == std::string::npos ? slash : slash - open_parenth - 1)));
		this->set_denominator(stoi(frac.substr(slash + 1, open_parenth == std::string::npos ? frac.size() - slash - 1 : frac.size() - slash - 2)));
		if (open_parenth != std::string::npos)
			this->set_mixed(stoi(frac.substr(0, open_parenth)));
	}

	/**
	 * \brief This function relies on integer division to return the integer mixed number value
	 */
	int get_mixed() const { return this->get_numerator() / this->get_denominator(); }
	/**
	 * \brief Changes the numerator of the fraction to give the param as the leading mixed fraction coefficient
	 * \param mix the value used to alter the numerator to set the mixed fraction coefficient
	 * 
	 * The temp integer variable is used to store the original mixed number numerator value.
	 * The if else checks are meant to change the value only if they are of opposite signs to correct the mixed number from being one too high or too low.
	 * Then the numerator is set whether changes were applied or not to the temp value.
	 */
	void set_mixed(int const& mix)
	{
		int temp = this->get_numerator() % this->get_denominator() + mix * this->get_denominator();
		if (mix > 0 && this->get_numerator() < 0)/**This accounts for the one extra needed to change from positive to negative*/
			temp += this->get_denominator();
		else if (mix < 0 && this->get_numerator() > 0)
			temp -= this->get_denominator();
		this->set_numerator(temp);
	}
	int get_numerator() const { return this->numerator_; }
	void set_numerator(int const& num) { this->numerator_ = num; }
	int get_denominator() const { return this->denominator_; }
	void set_denominator(int const& den) { if (den == 0) throw std::exception("Cannot divide by zero in fraction class"); this->denominator_ = den; }

	/**
	 * \brief Simplify will put the current fraction into its simpliest form.
	 * \return returns a fraction of the current fraction's simpliest form or itself if already in simplist form
	 *
	 * This member function first checks if the numerator or the denominator of the current fraction object is equal to one and that the numerator is not zero.
	 * This check is to ensure that the fraction is neither in its simpliest form already and that zero will not be sent to the gcd function.
	 * If the function is not already simplified, return a fraction with the current numerator and denominator divided by their gcd (greatest common divisor).
	 */
	fraction simplify() const
	{
		if (!(this->get_numerator() == 1 || this->get_denominator() == 1) && this->get_numerator() != 0)
			return { this->get_numerator() / general_math_functions::gcd(this->get_numerator(), this->get_denominator()), this->get_denominator() / general_math_functions::gcd(this->get_numerator(), this->get_denominator()) };
		return *this;
	}

	double to_decimal() const
	{
		return static_cast<double>(this->get_numerator()) / this->get_denominator();
	}

	/**
	 * \return a fraction type with the numerator and denominator swapped
	 */
	fraction get_reciprocal() const
	{
		return { this->get_denominator(), this->get_numerator() };
	}

	fraction operator+(fraction const& r_frac) const
	{
		if (this->get_denominator() != r_frac.get_denominator())
		{
			int change1 = 1, change2 = 1;
			if (this->get_denominator() != general_math_functions::lcm(this->get_denominator(), r_frac.get_denominator()))
				change1 = general_math_functions::lcm(this->get_denominator(), r_frac.get_denominator()) / this->get_denominator();
			if (r_frac.get_denominator() != general_math_functions::lcm(this->get_denominator(), r_frac.get_denominator()))
				change2 = general_math_functions::lcm(this->get_denominator(), r_frac.get_denominator()) / r_frac.get_denominator();
			return fraction{ this->get_numerator() * change1 + r_frac.get_numerator() * change2, general_math_functions::lcm(this->get_denominator(), r_frac.get_denominator()) }.simplify();
		}
		return fraction{ this->get_numerator() + r_frac.get_numerator(), this->get_denominator() }.simplify();
	}

	void operator+=(fraction const& r_frac)
	{
		*this = *this + r_frac;
	}

	void operator+=(int const& r_int)
	{
		*this = *this + fraction{ r_int, 1 };
	}

	fraction operator++()
	{
		*this += fraction{ 1, 1 };
		return *this;
	}

	fraction operator++(int)//postfix
	{
		fraction const temp = *this;
		++*this;
		return temp;
	}

	fraction operator-(fraction const& frac2) const
	{
		if(this->get_denominator() != frac2.get_denominator())
		{
			int change1 = 1, change2 = 1;
			if (this->get_denominator() != general_math_functions::lcm(this->get_denominator(), frac2.get_denominator()))
				change1 = general_math_functions::lcm(this->get_denominator(), frac2.get_denominator()) / this->get_denominator();
			if (frac2.get_denominator() != general_math_functions::lcm(this->get_denominator(), frac2.get_denominator()))
				change2 = general_math_functions::lcm(this->get_denominator(), frac2.get_denominator()) / frac2.get_denominator();
			return fraction{ this->get_numerator() * change1 - frac2.get_numerator() * change2, general_math_functions::lcm(this->get_denominator(), frac2.get_denominator()) }.simplify();
		}
		return fraction{ this->get_numerator() - frac2.get_numerator(), this->get_denominator() }.simplify();
	}

	void operator-=(fraction const& r_frac)
	{
		*this = *this - r_frac;
	}

	void operator-=(int const& r_int)
	{
		*this = *this - fraction{ r_int, 1 };
	}

	fraction operator--()
	{
		*this -= fraction{ 1, 1 };
		return *this;
	}

	fraction operator--(int)
	{
		fraction const temp = *this;
		--*this;
		return temp;
	}

	fraction operator*(fraction const& r_frac) const
	{
		return fraction{ this->get_numerator() * r_frac.get_numerator(), this->get_denominator() * r_frac.get_denominator() }.simplify();
	}

	void operator*=(fraction const& r_frac)
	{
		*this = *this * r_frac;
	}

	void operator*=(int const& r_int)
	{
		*this = *this * fraction{ r_int, 1 };
	}

	fraction operator/(fraction const& r_frac) const
	{
		return fraction{ *this * r_frac.get_reciprocal() }.simplify();
	}

	void operator/=(fraction const& r_frac)
	{
		*this = *this / r_frac;
	}

	void operator/=(int const& r_int)
	{
		*this = *this / fraction{ r_int, 1 };
	}

	std::ostream friend& operator<<(std::ostream& os, fraction r_frac)
	{
		if (r_frac.get_numerator() % r_frac.get_denominator() == 0)
			os << r_frac.get_numerator() / r_frac.get_denominator();
		else
		{
			os << r_frac.get_numerator();
			os << "/" << r_frac.get_denominator();
			if (r_frac.get_numerator() > r_frac.get_denominator() || r_frac.get_numerator() * -1 > r_frac.get_denominator())//if mixed positive or negative fraction
			{
				os << " or " << r_frac.get_numerator() / r_frac.get_denominator() << "(";
				os << (r_frac.get_numerator() > 0 ? r_frac.get_numerator() % r_frac.get_denominator() : r_frac.get_numerator() % r_frac.get_denominator() * -1);
				os << "/" << r_frac.get_denominator() << ")";
			}
		}
		return os;
	}
};