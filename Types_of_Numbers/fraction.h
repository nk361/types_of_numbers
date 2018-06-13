#pragma once
#include "stdafx.h"
#include "functional"

class fraction
{
	int numerator_;
	int denominator_;
public:
	fraction() { this->set_numerator(0); this->set_denominator(1); }
	fraction(int const& num, int const& den, bool const& trig = false)
	{
		this->set_numerator(num);
		this->set_denominator(den);
		if (!trig)
		{
			fraction temp = this->fix_signs();
			this->set_numerator(temp.get_numerator());
			this->set_denominator(temp.get_denominator());
		}
	}
	/**
	 * \brief Sets the mixed fraction values, nested mixed fractions not supported here, call set_normalize instead
	 */
	fraction(int mixed, int num, int den, bool const& trig = false, bool const& norm = false)
	{
		//this will take the three parameters to set. If trig is true, the signs for them won't change
		//if the norm param is true, this will attempt to normalize the fraction if the numerator is greater than the denominator
		//by adding or subtracting what it needs to to the mixed number value
		//if both trig and norm are false, all that will by changed is the numerators sign to negative if the mixed sign is negative and numerator's is not
		//the trig bool is meant to decide whether the signs matter for the fraction to figure out other trig fractions for a triangle

		if (mixed < 0 && num > 0)
			num *= -1;
		else if (mixed > 0 && num < 0)
			mixed *= -1;

		if(!trig)
		{
			if(num > 0 && den < 0 || num < 0 && den < 0)
			{
				mixed *= -1;
				num *= -1;
				den *= -1;
			}
		}

		/*if(norm)
		{
			if(fraction{num, den}.get_mixed() != 0)
			{
				mixed += fraction{ num, den }.get_mixed();
				num %= den;
			}
		}*/

		this->set_numerator(num);
		this->set_denominator(den);

		if (den < 0 && mixed > 0 && trig && !norm)
			this->set_numerator(num % (den * -1) + mixed * (den * -1));//*this = fraction{ this->get_numerator(), this->get_denominator() * -1 } + mixed;//*this += -mixed;
		else if(den < 0 && mixed > 0 && trig && norm)
			this->set_numerator(num + (mixed + num % den * -1) * (den * -1));
		else if (den > 0 && mixed < 0)
			this->set_numerator(num % den + mixed * den);
		else
			*this += mixed;

		/*num = num * (mixed < 0 && num > 0 ? -1 : 1);


		std::cout << "           " << num << std::endl;
		if (trig)
		{
			fix_signs(mixed, num, den);
			//den *= -1;
			//num *= -1;
			//mixed *= -1;
		}*/

		/*if(norm)
		{
			mixed += num * (mixed < 0 && num > 0 ? -1 : 1) / den;
			num %= den;
		}
		
		if(!trig)
		{
			
			if(mixed >= 0 && num > 0 && den < 0 || mixed <= 0 && num < 0 && den < 0)//if the denominator is negative and the numerator is not or if all values are negative
			{
				mixed *= -1;
				num *= -1;
				den *= -1;
			}
		}

		std::cout << "           " << num << std::endl;

		if (norm)
		{
			num *= 1 % den;
			std::cout << "           " << num << std::endl;
			//den;
			mixed += num * 1 / den;

			std::cout << "           " << num << std::endl;

			//std::tie(mixed, num, den) = normalize_params(mixed, num, den);


			//std::tuple<mixed, num, den> temp = normalize_params(mixed, num, den);
			//mixed = std::get<0>(temp);

		}
			

		this->set_numerator(num);
		this->set_denominator(den);

		std::cout << "           " << this->get_numerator() << std::endl;

		this->set_mixed(mixed);

		std::cout << "           " << this->get_numerator() << std::endl;

		if (!trig)
			;// this->fix_signs();

		if (norm)
		{

			//*this = normalize();
			//this->set_mixed(this->get_mixed() + num * (mixed < 0 && num > 0 ? -1 : 1) / den);
		 	//this->set_numerator(this->get_numerator() % den);
		}

		//this->set_numerator(num * (mixed < 0 && num > 0 ? -1 : 1) % den);
		//this->set_denominator(den);
		//this->set_mixed(mixed + num * (mixed < 0 && num > 0 ? -1 : 1) / den);


		//this->set_numerator(num * (mixed < 0 && num > 0 ? -1 : 1));
		//this->set_denominator(den);
		//this->set_mixed(mixed);// + this->get_numerator() / this->get_denominator());*/
	}
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
	int get_mixed(bool trig = false) const
	{
		if (trig && this->get_denominator() < 0)
			return this->get_numerator() / (this->get_denominator() * -1);
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

	fraction fix_signs() const
	{
		//if the denominator is negative and the numerator is positive, denominator *= -1 and numerator *=-1

		if(this->get_denominator() < 0 && this->get_numerator() > 0 || this->get_numerator() < 0 && this->get_denominator() < 0)
		{
			return { this->get_numerator() * -1, this->get_denominator() * -1 };
			//this->set_numerator(this->get_numerator() * -1);
			//this->set_denominator(this->get_denominator() * -1);
		}
		return *this;

		/*if (this->get_denominator() < 0 && this->get_mixed() >= 0 && this->get_numerator() > 0)
		{
			this->set_numerator(this->get_numerator() * -1);
			this->set_denominator(this->get_denominator() * -1);
			this->set_mixed(this->get_mixed() * -1);
		}*/
	}
	
	/*void fix_signs(int &mixed, int &num, int &den)
	{
		if(den < 0 && mixed > 0 && num > 0)
		{
			num *= -1;
			den *= -1;
			mixed *= -1;
		}
	}*/

	bool is_positive() const
	{
		//std::cout << this->get_mixed() << "      " << this->get_numerator() << "       " << this->get_denominator() << std::endl;
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
	
	/*fraction normalize() const
	{
		fraction temp;

		temp.set_numerator(this->get_numerator() % this->get_denominator() + this->get       + this->get_numerator() / this->get_denominator())

		temp.set_mixed(this->get_mixed() + this->get_numerator() * (this->get_mixed() < 0 && this->get_numerator() > 0 ? -1 : 1) / this->get_denominator());
		temp.set_numerator(this->get_numerator() * (this->get_mixed() < 0 && this->get_numerator() > 0 ? -1 : 1) % this->get_denominator());
		temp.set_denominator(this->get_denominator());
		
		return temp;
	}*/

	fraction normalize(int const& mixed, int const& num, int const& den) const
	{
		return { num * (mixed < 0 && num > 0 ? -1 : 1) % den, den, mixed + num * (mixed < 0 && num > 0 ? -1 : 1) / den };
		/*this->set_numerator(num * (mixed < 0 && num > 0 ? -1 : 1) % den);
		this->set_denominator(den);
		this->set_mixed(mixed + num * (mixed < 0 && num > 0 ? -1 : 1) / den);
		return *this;*/
	}

	/*std::tuple<int, int, int> normalize_params(int const& mixed, int const& num, int const& den) const
	{
		return { num * (mixed < 0 && num > 0 ? -1 : 1) % den, den, mixed + num * (mixed < 0 && num > 0 ? -1 : 1) / den };
	}*/

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

	fraction operator+(int const& r_int) const
	{
		return *this + fraction{ r_int, 1 };
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
		*this += fraction{ 1, 1 };
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
			return fraction{ this->get_numerator() * change1 - r_frac.get_numerator() * change2, general_math_functions::lcm(this->get_denominator(), r_frac.get_denominator()) }.simplify();
		}
		return fraction{ this->get_numerator() - r_frac.get_numerator(), this->get_denominator() }.simplify();
	}

	fraction operator-(int const& r_int) const
	{
		return *this - fraction{ r_int, 1 };
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
		*this -= fraction{ 1, 1 };
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
		return fraction{ this->get_numerator() * r_frac.get_numerator(), this->get_denominator() * r_frac.get_denominator() }.simplify();
	}

	fraction operator*(int const& r_int) const
	{
		return *this * fraction{ r_int, 1 };
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
		return fraction{ *this * r_frac.get_reciprocal() }.simplify();
	}

	fraction operator/(int const& r_int) const
	{
		return *this / fraction{ r_int, 1 };
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



	std::ostream& operator<<(std::ostream& os) const
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
	}

	std::ostream friend& operator<<(std::ostream& os, fraction const& r_frac)
	{
		return r_frac.operator<<(os);
	}
};