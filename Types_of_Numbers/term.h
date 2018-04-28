#pragma once
#include "stdafx.h"

class term
{
	int coefficient_ = 0;
	std::vector<char> variables_;
	std::vector<int> exponents_;
public:
	term() { this->coefficient_ = 0; this->variables_ = {}; this->exponents_ = {}; }
	term(int const& coe, std::vector<char> const& vars, std::vector<int> const& exps)
	{
		this->coefficient_ = coe;
		this->variables_ = vars;
		this->exponents_ = exps;
	}

	term(int const& coe)//constant(s)
	{
		this->coefficient_ = coe;
		this->variables_ = {};
		this->exponents_ = {};
	}
	
	/*this checks for digits or a negative symbol as the coefficient_,
	 *then gets the variables_ and checks for many in a row with exponent 1,
	 *it then looks for a number in parentheses and gets the full number to make the exponent,
	 *finally sets the values off the temporary term object*/
	term(std::string trm)
	{
		term new_term;
		bool num = false;
		for (int i = 0, digits[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }; i < trm.size(); i++, num = false)
		{
			for (int j = 0; j < sizeof digits; j++)
				if (trm[i] - '0' == digits[j] || trm[i] == '-')//checks for the last spot that has a digit or '-' as the coefficient_ value
					num = true;
			if (!num || num && i + 1 == trm.size())//checks that it's either found a non digit or that it has reached the end with all digits or a '-'
			{
				if (!num && i == 1 && trm[0] == '-')//check for just a negative var at start and that num is not true, indicating that there is a variable next
					new_term.set_coefficient(-1);
				else if (i == 0)//check for just a positive var at start
					new_term.set_coefficient(1);
				else
					new_term.set_coefficient(stoi(trm.substr(0, i + 1)));
				for (int j = i; j < trm.size() && !num; j++)//!num is added to block ever adding variables_ or exponenets for only coefficients
					if (j == i || trm[j - 1] == ')' || trm[j + 1] == '^')//checks if it's the first var, a var after (exp) or a var before ^ incase there's been a stream of only vars
					{
						new_term.set_variables(utility_functions::add_item(trm[j], new_term.get_variables()));
						if (trm[j + 1] != '^')//checking for variable with no exponent or to the power of 1
						{
							new_term.set_exponents(utility_functions::add_item(1, new_term.get_exponents()));
							for (int k = j + 1; k < trm.size() && trm[k + 1] != '^'; k++)//checks for a continuos streak of variables_ with a power of 1
							{
								new_term.set_variables(utility_functions::add_item(trm[k], new_term.get_variables()));
								new_term.set_exponents(utility_functions::add_item(1, new_term.get_exponents()));
							}
						}
					}
					else if (trm[j - 1] == '(')//checks that it is now over a digit at j
						for (int k = j; k < trm.size(); k++, num = false)
						{
							for (int l = 0; l < sizeof digits; l++)//checks again if the spot is a number that it's over
								if (trm[k] - '0' == digits[l])
									num = true;
							if (!num)//this adds the exponent of any size by using the first spot a nuber appears and moving the distance to the last spot that a number was found
							{
								new_term.set_exponents(utility_functions::add_item(stoi(trm.substr(j, k - j)), new_term.get_exponents()));
								break;
							}
						}
				break;
			}
		}
		this->coefficient_ = new_term.get_coefficient();
		if (new_term.get_variables().size() > 0 && new_term.get_exponents().size() > 0)
		{
			this->variables_ = new_term.get_variables();
			this->exponents_ = new_term.get_exponents();
		}
	}

	/*term(const term &trm2)//copy constructor - not needed
	{
		this->coefficient_ = trm2.get_coefficient();
		this->variables_ = trm2.get_variables();
		this->exponents_ = trm2.get_exponents();
	}*/

	int get_coefficient() const { return this->coefficient_; }
	void set_coefficient(int const coe) { this->coefficient_ = coe; }
	std::vector<char> get_variables() const { return variables_; }
	void set_variables(std::vector<char> const vars) { this->variables_ = vars; }
	std::vector<int> get_exponents() const { return this->exponents_; }
	void set_exponents(std::vector<int> const exps) { this->exponents_ = exps; }

	class check//create this check and the checker in all classes that can't execute without certain conditions
	{
	public:
		bool static plus_and_minus(term const& trm1, term const& trm2)
		{
			return trm1.variables_ == trm2.variables_ && trm1.exponents_ == trm2.exponents_;
		}
	};
	static check checker;//both need to be static to be called without a term object

	term friend operator+(term const& trm1, term const& trm2)//check rule first in future string interpreter
	{
		return { trm1.coefficient_ + trm2.coefficient_, trm1.variables_, trm1.exponents_ };
	}

	term friend operator-(term const& trm1, term const& trm2)
	{
		return { trm1.coefficient_ - trm2.coefficient_, trm1.variables_, trm1.exponents_ };
	}

	term friend operator*(term const& trm1, term const& trm2)
	{
		term temp = trm1;

		temp.set_coefficient(temp.get_coefficient() * trm2.get_coefficient());
		if (temp.get_variables().size() > 0 || trm2.get_variables().size() > 0)
		{
			temp.set_variables(utility_functions::add_missing(temp.get_variables(), trm2.get_variables()));

			bool found = false;
			for (int i = 0; i < trm2.get_variables().size(); i++, found = false)
			{
				for (int j = 0; j < trm1.get_variables().size(); j++)
					if (trm2.get_variables()[i] == trm1.get_variables()[j])
					{
						temp.exponents_[j] += trm2.get_exponents()[i];
						found = true;
					}
				if (!found)
					temp.exponents_.push_back(trm2.get_exponents()[i]);

			}
		}
		return temp;
	}

	std::ostream friend&  operator<<(std::ostream& os, term const& trm)
	{
		if (trm.coefficient_ != 1 || trm.variables_.empty())
			os << trm.coefficient_;
		if (!(trm.variables_.empty() && trm.exponents_.empty()))
			if (trm.variables_.size() == trm.exponents_.size() && trm.variables_.size() != 0)
				for (unsigned int i = 0; i < trm.variables_.size(); i++)
					if (trm.exponents_[i] != 0)
					{
						os << trm.variables_[i];
						if (trm.exponents_[i] != 1)
							os << "^(" << trm.exponents_[i] << ")";
					}
		return os;
	}
};