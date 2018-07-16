#pragma once
#include "stdafx.h"

class fraction
{
	int numerator_;
	int denominator_;
public:
	fraction() { this->set_numerator(0); this->set_denominator(1); }
	explicit fraction(int const& num) { this->set_numerator(num); this->set_denominator(1); }
	fraction(int const& num, int const& den)
	{
			this->set_numerator(num);
			this->set_denominator(den);
	}
	/**
	 * \brief Creates a mixed fraction.
	 * \param mixed Leading whole number that's added to the fraction
	 * \param num Fraction numerator before mixed addition
	 * \param den Fraction denominator
	 * \param norm Optional normalization of num/den being mixed, affecting the mixed param
	 * 
	 * This constructor checks if the numerator and denominator make a mixed fraction, then decides whether to
	 * normalize (add their calculated mixed value to the other) and fixes the numerator either way.
	 * It then sets the values to the result of addition between the mixed number and fraction.
	 */
	fraction(int mixed, int num, int const& den, bool const& norm = false)
	{
		if ((num < 0 ? num * -1 : num) > (den < 0 ? den * -1 : den))
		{
			if(norm)
				mixed += num / den;
			num = (num < 0 ? num * -1 : num) % (den < 0 ? den * -1 : den);
		}

		*this = fraction{ num, den } + mixed;
	}
	/**
	 * \brief This constructor converts a double to a fraction type.
	 * \param dec Refrence to constant double decimal value
	 * 
	 * This constructor starts by locating the decimal point's location. Then, it starts a loop that searches for a character that isn't
	 * a zero from right to left. It uses the position that the first non-zero character is found to calculate
	 */
	explicit fraction(double const& dec)
	{//TODO I've seen a way to convert decimals to fractions with repeating values, but I think I'd like to make a decimal class with more accuracy to notice repeating values
		std::string::size_type const point = std::to_string(dec).find('.');

		size_t i;
		for (i = std::to_string(dec).size() - 1; i >= 0; i--)
			if (std::to_string(dec)[i] != '0')
				break;

		this->set_numerator(static_cast<int>(dec * pow(10, i - 1 - std::to_string(dec).substr(0, point - 1).size())));
		this->set_denominator(static_cast<int>(1 * pow(10, i - 1 - std::to_string(dec).substr(0, point - 1).size())));
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
	explicit fraction(std::string frac)
	{
		std::string::size_type const open_parenth = frac.find('(');
		std::string::size_type const slash = frac.find('/');
		
		if (open_parenth == std::string::npos && slash == std::string::npos)
		{
			this->set_numerator(stoi(frac));
			this->set_denominator(1);
		}
		else
		{
			this->set_numerator(stoi(frac.substr(open_parenth == std::string::npos ? 0 : open_parenth + 1, open_parenth == std::string::npos ? slash : slash - open_parenth - 1)));
			this->set_denominator(stoi(frac.substr(slash + 1, open_parenth == std::string::npos ? frac.size() - slash - 1 : frac.size() - slash - 2)));
			if (open_parenth != std::string::npos)
				this->set_mixed(stoi(frac.substr(0, open_parenth)));
		}
	}

	/**
	 * \brief This function relies on integer division to return the integer mixed number value
	 */
	int get_mixed() const
	{
		return this->get_numerator() / this->get_denominator();
	}
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
		if(this->get_mixed() != mix)
			if (this->get_mixed() == 0)
				*this += mix;
			else
				*this += this->get_mixed() > mix ? this->get_mixed() - mix : mix - this->get_mixed();

		//subtract what the fraction currently is or something to get what to add or subtract to it to make it set
		//use abs instead of ternary if
		//this->set_numerator(5);//temporary
		//if (*this > mix)
			//*this += *this - mix;
		//else if (*this < mix)
			//*this += fraction{ mix, 1 } - *this;

		//*this - mix;

		/*//TODO I think the denominator needs to change signs if negitive here
		int temp = this->get_numerator() % (this->get_denominator() > 0 ? this->get_denominator() : this->get_denominator() * -1) + mix * (this->get_denominator() > 0 ? this->get_denominator() : this->get_denominator() * -1);
		std::cout << temp << std::endl;
		if (mix > 0 && this->get_numerator() < 0)/**This accounts for the one extra needed to change from positive to negative
			temp += this->get_denominator();
		else if (mix < 0 && this->get_numerator() > 0)
			temp -= this->get_denominator();
		temp = 20;
		std::cout << temp << std::endl;
		this->set_numerator(temp);*/
	}
	int get_numerator() const { return this->numerator_; }
	void set_numerator(int const& num) { this->numerator_ = num; }
	int get_denominator() const { return this->denominator_; }
	void set_denominator(int const& den) { if (den == 0) throw std::exception("Cannot divide by zero in fraction class"); this->denominator_ = den; }

	bool is_positive() const
	{
		return 0 <= this->get_numerator() * this->get_denominator();
	}
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

	std::string to_string() const
	{
		if (this->get_numerator() % this->get_denominator() == 0)
			return std::to_string(this->get_mixed());
		if (this->get_mixed() != 0)
			return std::to_string(this->get_mixed()) + '(' + std::to_string(this->get_numerator() % this->get_denominator()) + '/' + std::to_string(this->get_denominator()) + ')';
		return std::to_string(this->get_numerator()) + '/' + std::to_string(this->get_denominator());
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
			return fraction{ this->get_numerator() * change1 + r_frac.get_numerator() * change2, general_math_functions::lcm(this->get_denominator(), r_frac.get_denominator()) };
		}
		return fraction{ this->get_numerator() + r_frac.get_numerator(), this->get_denominator() };
	}

	fraction operator+(int const& r_int) const
	{
		return *this + fraction{ r_int };
	}

	void operator+=(fraction const& r_frac)
	{
		*this = *this + r_frac;
	}

	void operator+=(int const& r_int)
	{
		*this = *this + r_int;
	}

	fraction operator++()
	{
		*this += 1;
		return *this;
	}

	fraction operator++(int)//postfix
	{
		fraction const temp = *this;
		++*this;
		return temp;
	}

	fraction operator-(fraction const& r_frac) const
	{
		if(this->get_denominator() != r_frac.get_denominator())
		{
			int change1 = 1, change2 = 1;
			if (this->get_denominator() != general_math_functions::lcm(this->get_denominator(), r_frac.get_denominator()))
				change1 = general_math_functions::lcm(this->get_denominator(), r_frac.get_denominator()) / this->get_denominator();
			if (r_frac.get_denominator() != general_math_functions::lcm(this->get_denominator(), r_frac.get_denominator()))
				change2 = general_math_functions::lcm(this->get_denominator(), r_frac.get_denominator()) / r_frac.get_denominator();
			return fraction{ this->get_numerator() * change1 - r_frac.get_numerator() * change2, general_math_functions::lcm(this->get_denominator(), r_frac.get_denominator()) };
		}
		return fraction{ this->get_numerator() - r_frac.get_numerator(), this->get_denominator() };
	}

	fraction operator-(int const& r_int) const
	{
		return *this - fraction{ r_int };
	}

	void operator-=(fraction const& r_frac)
	{
		*this = *this - r_frac;
	}

	void operator-=(int const& r_int)
	{
		*this = *this - r_int;
	}

	fraction operator--()
	{
		*this -= 1;
		return *this;
	}

	fraction operator--(int)//postfix
	{
		fraction const temp = *this;
		--*this;
		return temp;
	}

	fraction operator*(fraction const& r_frac) const
	{
		return fraction{ this->get_numerator() * r_frac.get_numerator(), this->get_denominator() * r_frac.get_denominator() };
	}

	fraction operator*(int const& r_int) const
	{
		return *this * fraction{ r_int };
	}

	void operator*=(fraction const& r_frac)
	{
		*this = *this * r_frac;
	}

	void operator*=(int const& r_int)
	{
		*this = *this * r_int;
	}

	fraction operator/(fraction const& r_frac) const
	{
		return *this * r_frac.get_reciprocal();//is this deconstructing the fraction type to create a fraction with an initializer list?
	}//wait, I guess this didn't need to be within fraction{  }

	fraction operator/(int const& r_int) const
	{
		return *this / fraction{ r_int };
	}

	void operator/=(fraction const& r_frac)
	{
		*this = *this / r_frac;
	}

	void operator/=(int const& r_int)
	{
		*this = *this / r_int;
	}

	bool operator==(fraction const& r_frac) const
	{
		return this->simplify().get_numerator() == r_frac.simplify().get_numerator() && this->simplify().get_denominator() == r_frac.simplify().get_denominator();
	}

	bool operator==(int const& r_int) const
	{
		return this->simplify().get_numerator() == r_int && this->simplify().get_denominator() == 1;
	}

	bool operator!=(fraction const& r_frac) const
	{
		return this->simplify().get_numerator() != r_frac.simplify().get_numerator() || this->simplify().get_denominator() != r_frac.simplify().get_denominator();
	}

	bool operator!=(int const& r_int) const
	{
		return this->simplify().get_numerator() != r_int || this->simplify().get_denominator() != 1;
	}
	
	//bool operator>(int const& r_int) const
	//{
		//this is a fraction being compared to a full int
		//return this->get_mixed() > r_int || (this->get_mixed() == r_int && (this - this->get_mixed())->get_numerator() > 0);
		//wait, how do I deal with negatives?
		//wait until tests are made for test driven development
	//}

	//make fraction ones first then use them for ints
	bool operator>(int const& r_int) const
	{
		if (this->is_positive() && r_int < 0)
			return true;

		if (this->get_mixed() > r_int)
			return true;
		if (this->get_mixed() == r_int && this->is_positive())
			return true;
		return false;

		/*if (this->is_positive() && !fraction{ r_int, 1 }.is_positive())
			return true;
		if (!this->is_positive() && fraction{ r_int, 1 }.is_positive())
			return false;

		if (this->simplify().get_numerator() > r_int && this->simplify().get_denominator() == 1)
			return true;

		if (this->simplify().get_denominator() < fraction{ r_int, 1 }.get_denominator())
			return false;*/
	}

	bool operator>(fraction const& r_frac) const
	{
		return true;
	}

	/*bool operator>(int const& r_int)
	{
		if(this->simplify().get_mixed() >= r_int && this->simplify().get_numerator() > )
	}

	bool operator<(fraction const& r_frac) const
	{
		if(this->simplify().get_numerator() > 0 && this->simplify().get_denominator() > 0 && r_frac.simplify().get_numerator() > 0 && r_frac.simplify().get_denominator() > 0)
			if ((r_frac.simplify() - this->simplify()).simplify().get_numerator() > 0)
				return true;

		if ((this->simplify().get_numerator() > 0 || this->simplify().get_denominator() > 0) && (r_frac.simplify().get_numerator() > 0 || r_frac.simplify().get_denominator() > 0))
			if ((this->simplify() - r_frac.simplify()).simplify().get_numerator() > 0)
				return true;
		if(this->simplify().get_numerator() > )




		if (this->simplify().get_denominator() < r_frac.simplify().get_denominator())
			return true;
		return this->simplify().get_denominator() == r_frac.simplify().get_denominator() && this->simplify().get_numerator() < r_frac.simplify().get_numerator();
	}*/



	/*std::ostream& operator<<(std::ostream& os) const
	{
		if (this->get_numerator() % this->get_denominator() == 0)
			os << this->get_mixed();
		else
		{
			os << this->get_numerator();
			os << "/" << this->get_denominator();
			if (this->get_mixed() != 0)//if mixed positive or negative fraction and not a negative nonmixed fraction
			{
				os << " or " << this->get_mixed() << "(";
				os << (this->get_numerator() > 0 ? this->get_numerator() % this->get_denominator() : this->get_numerator() % this->get_denominator() * -1);
				os << "/" << this->get_denominator() << ")";
			}
		}
		return os;
	}*/

	std::ostream& operator<<(std::ostream& os) const
	{
		return os << this->get_numerator() << "/" << this->get_denominator();
	}

	std::ostream friend& operator<<(std::ostream& os, fraction const& r_frac)
	{
		return r_frac.operator<<(os);
	}

	void output_simplified() const
	{
		std::cout << this->simplify();
		if (this->get_numerator() % this->get_denominator() != 0)
			std::cout << " or " << this->get_mixed() << "(" << this->simplify() - this->get_mixed() << ")";
		std::cout << std::endl;
	}
	
	void output_pretty_signs() const
	{
		if(!this->is_positive())
			std::cout << "-";
		if (this->get_mixed() != 0)
			std::cout << abs(this->get_mixed());
		std::cout << "(" << abs(this->get_numerator() % this->get_denominator()) << "/" << abs(this->get_denominator()) << ")";
		std::cout << std::endl;
	}

	void output_details() const
	{
		std::cout << *this;
		if (this->get_mixed() != 0)
		{
			std::cout << " or ";
			std::cout << this->get_mixed();
			if (this->get_numerator() % this->get_denominator() != 0)
				std::cout << "(" << this->get_numerator() % this->get_denominator() << "/" << this->get_denominator() << ")";
		}
		std::cout << std::endl;
		
		std::cout << "Simplified: ";
		output_simplified();
		
		std::cout << "With corrected signs: ";
		output_pretty_signs();
	}
};