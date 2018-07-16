#pragma once
#include "stdafx.h"

#include "Fraction.h"//very rough thought, but I'm thinking a fraction may need to be a frame too just to hold info of any type and display somehow
//what I mean is like the top and bottom can be normal types or custom types that I make, then I need to make generic operations
//like check for similarities so I could remove like 5x form the top and bottom

class term
{
	int coefficient_ = 0;
	std::vector<char> variables_;
	std::vector<int> exponents_;
public:
	term() = default;// { this->set_coefficient(0); this->set_variables({}); this->set_exponents({}); }//handles example: 0

	explicit term(char const& var, int const& exp = 1)//handles examples: r^6, j
	{
		this->set_coefficient(1);
		this->set_variables({ var });
		this->set_exponents({ exp });
	}

	explicit term(std::vector<char> const& vars, std::vector<int> const& exps = {})//handles examples: (k^45)(g^17)m^9, asd
	{
		if (vars.size() != exps.size() && !exps.empty())
			throw std::exception("Term no coefficient vector constructor: Variables must match the amount of exponents, you must send one in the propper place if it has no exponent");

		this->set_coefficient(1);
		this->set_variables(vars);
		if (exps.empty())
			for (size_t i = 0; i < vars.size(); i++)
				this->add_exponenet(1);
		else
			this->set_exponents(exps);
	}

	term(int const& coe, char const& var, int const& exp = 1)//handles examples: 5x, 4y^8
	{
		this->set_coefficient(coe);
		this->set_variables({ var });
		this->set_exponents({ exp });
	}

	explicit term(int const& coe, std::vector<char> const& vars = {}, std::vector<int> const& exps = {})//handles examples: 10, 17(x^1)y^1, 15(k^17)(q^9)p^54
	{
		if (vars.size() != exps.size() && !exps.empty())
			throw std::exception("Term coefficient vector constructor: Variables must match the amount of exponents, you must send one in the propper place if it has no exponent");

		this->set_coefficient(coe);
		this->set_variables(vars);
		if (exps.empty())
			for (size_t i = 0; i < vars.size(); i++)
				this->add_exponenet(1);
		else
			this->set_exponents(exps);
	}

	/**
	 *\brief A constructor for converting a formatted string into a term
	 *\param trm a string with a coefficent (optional), variables (optional), and exponents (optional default is 1)
	 *
	 *This checks for digits or a negative symbol as the coefficient_.
	 *Then gets the variables_ and checks for many in a row with exponent 1.
	 *It then looks for a number in parentheses and gets the full number to make the exponent.
	 *Finally sets the values off the temporary term object
	 */
	term(std::string const& trm)//I'm not looking forward to it, but I want to change the string format to something like 5x, 4y^8, 30xysdd, 7(y^4)p^3, 9xpo(f^7)cus
	{
		term temp;
		bool num = false;
		for (unsigned int i = 0, digits[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }; i < trm.size(); i++, num = false)
		{
			for (unsigned int j = 0; j < sizeof digits; j++)
				if (trm[i] - '0' == digits[j] || trm[i] == '-')//checks for the last spot that has a digit or '-' as the coefficient_ value
					num = true;
			if (!num || num && i + 1 == trm.size())//checks that it's either found a non digit or that it has reached the end with all digits or a '-'
			{
				if (!num && i == 1 && trm[0] == '-')//check for just a negative var at start and that num is not true, indicating that there is a variable next
					temp.set_coefficient(-1);
				else if (i == 0)//check for just a positive var at start
					temp.set_coefficient(1);
				else
					temp.set_coefficient(stoi(trm.substr(0, i + 1)));
				for (unsigned int j = i; j < trm.size() && !num; j++)//!num is added to block ever adding variables_ or exponenets for only coefficients
					if (j == i || trm[j - 1] == ')' || trm[j + 1] == '^')//checks if it's the first var, a var after (exp) or a var before ^ incase there's been a stream of only vars
					{
						temp.add_variable(trm[j]);
						if (trm[j + 1] != '^')//checking for variable with no exponent or to the power of 1
						{
							temp.add_exponenet(1);
							for (unsigned int k = j + 1; k < trm.size() && trm[k + 1] != '^'; k++)//checks for a continuos streak of variables_ with a power of 1
							{
								temp.add_variable(trm[k]);
								temp.add_exponenet(1);
							}
						}
					}
					else if (trm[j - 1] == '(')//checks that it is now over a digit at j
						for (unsigned int k = j; k < trm.size(); k++, num = false)
						{
							for (unsigned int l = 0; l < sizeof digits; l++)//checks again if the spot is a number or negative sign that it's over
								if (trm[k] - '0' == digits[l] || trm[k] == '-')
									num = true;
							if (!num)//this adds the exponent of any size by using the first spot a nuber appears and moving the distance to the last spot that a number was found
							{
								temp.add_exponenet(stoi(trm.substr(j, k - j)));
								break;
							}
						}
				break;
			}
		}
		*this = temp;
	}

	/*term(const term &trm2)//copy constructor - not needed
	{
		this->coefficient_ = trm2.get_coefficient();
		this->variables_ = trm2.get_variables();
		this->exponents_ = trm2.get_exponents();
	}*/

	class check//create this check and the checker in all classes that can't execute without certain conditions
	{
	public:
		bool static plus_and_minus(term const& trm1, term const& trm2)
		{
			return trm1.get_variables() == trm2.get_variables() && trm1.get_exponents() == trm2.get_exponents();
		}
	};
	static check checker;//both need to be static to be called without a term object

	int get_coefficient() const { return this->coefficient_; }
	void set_coefficient(int const& coe) { this->coefficient_ = coe; }
	std::vector<char> get_variables() const { return variables_; }
	void set_variables(std::vector<char> const& vars) { this->variables_ = vars; }
	std::vector<int> get_exponents() const { return this->exponents_; }
	void set_exponents(std::vector<int> const& exps) { this->exponents_ = exps; }

	void set_variable(int const& index, char const& var) { this->variables_[index] = var; }
	void set_exponent(int const& index, int const& exp) { this->exponents_[index] = exp; }
	void add_variable(char const& var) { this->variables_.push_back(var); }
	void add_exponenet(int const& exp) { this->exponents_.push_back(exp); }

	term friend operator+(term const& trm1, term const& trm2)//check rule first in future string interpreter
	{
		return term{ trm1.get_coefficient() + trm2.get_coefficient(), trm1.get_variables(), trm1.get_exponents() };
	}

	term friend operator-(term const& trm1, term const& trm2)
	{
		return term{ trm1.get_coefficient() - trm2.get_coefficient(), trm1.get_variables(), trm1.get_exponents() };
	}

	term friend operator*(term const& trm1, term const& trm2)
	{
		term temp = trm1;

		temp.set_coefficient(temp.get_coefficient() * trm2.get_coefficient());
		if (temp.get_variables().size() > 0 || trm2.get_variables().size() > 0)
		{
			temp.set_variables(utility_functions::add_missing(temp.get_variables(), trm2.get_variables()));

			bool found = false;
			for (unsigned int i = 0; i < trm2.get_variables().size(); i++, found = false)
			{
				for (unsigned int j = 0; j < trm1.get_variables().size(); j++)
					if (trm2.get_variables()[i] == trm1.get_variables()[j])
					{
						temp.set_exponent(j, temp.get_exponents()[j] + trm2.get_exponents()[i]);
						found = true;
					}
				if (!found)
					temp.add_exponenet(trm2.get_exponents()[i]);

			}
		}
		return temp;
	}

	term friend operator/(term const& trm1, term const& trm2)
	{
		term temp;
		//need fraction behavior simplify
		fraction test(5, 3);
	}

	term friend operator%(term const& trm1, term const& trm2)
	{
		term temp;
	}

	std::ostream friend&  operator<<(std::ostream& os, term const& trm)
	{
		if (trm.get_coefficient() != 1 || trm.get_variables().empty())
			os << trm.get_coefficient();
		if (!(trm.get_variables().empty() && trm.get_exponents().empty()))
			if (trm.get_variables().size() == trm.get_exponents().size() && trm.get_variables().size() != 0)
				for (unsigned int i = 0; i < trm.get_variables().size(); i++)
					if (trm.get_exponents()[i] != 0)
					{
						os << trm.get_variables()[i];
						if (trm.get_exponents()[i] != 1)
							os << "^(" << trm.get_exponents()[i] << ")";
					}
		return os;
	}
};