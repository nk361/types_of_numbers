#pragma once
#include "stdafx.h"

#include "term.h"

class polynomial
{
	std::vector<term> terms_;
public:
	polynomial() { this->terms_ = {}; }
	polynomial(std::initializer_list<term> const& trms) { this->terms_ = trms; }

	explicit polynomial(std::string poly)//interpret string
	{
		size_t pos = 0;
		bool positive = true;

		while (poly.size() > 0)
		{
			pos = poly.find(" ");
			if (pos == std::string::npos)
				pos = poly.size();

			std::string const token = poly.substr(0, pos);

			if (token == "+" || token == "-")
				positive = token == "+";
			else
				terms_.push_back({ positive ? token : '-' + token });
			poly.erase(0, pos + 1);
		}
	}

	std::vector<term> get_terms() const { return this->terms_; }
	void set_terms(std::vector<term> const& trms) { this->terms_ = trms; }

	polynomial friend operator+(polynomial const& poly1, polynomial const& poly2)
	{
		return combine_polynomials(poly1, poly2).combine_like_terms().order();
	}

	polynomial friend operator-(polynomial const& poly1, polynomial const& poly2)
	{
		polynomial temp = poly2;
		for (int i = 0; i < temp.get_terms().size(); i++)
			temp.terms_[i].set_coefficient(temp.get_terms()[i].get_coefficient() * -1);//must use terms_ instead of get_terms() to change anything at the moment
		return combine_polynomials(poly1, temp).combine_like_terms().order();
	}

	polynomial friend operator*(polynomial const& poly1, polynomial const& poly2)
	{
		polynomial temp;
		for (int i = 0; i < poly1.get_terms().size(); i++)
			for (int j = 0; j < poly2.get_terms().size(); j++)
				temp.terms_.push_back(poly1.get_terms()[i] * poly2.get_terms()[j]);
		return temp;

		/*for (int i = 0; i < poly1.get_terms().size(); i++)
		for (int j = 0; j < poly2.get_terms().size(); j++)
		std::cout << i * poly2.get_terms().size() + j << std::endl;//the index of the illusive temp terms*/
	}

	std::pair<polynomial, polynomial> friend operator/(polynomial const& poly1, polynomial const& poly2)
	{
		polynomial temp, remainder;

		//Will most likely be all long division, unless synthetic division is faster with smaller divisors

		return std::pair<polynomial, polynomial> { temp, remainder };
	}

	polynomial static combine_polynomials(polynomial const& poly1, polynomial const& poly2)
	{
		polynomial temp = poly1;
		for (int i = 0; i < poly2.get_terms().size(); i++)
			temp.terms_.push_back(poly2.get_terms()[i]);
		return temp;
	}
	
	//adds terms with the same variables_ and exponents_ to each other then removes the higher index item before the lower so the higher index remains the same
	polynomial combine_like_terms()
	{
		if (this->terms_.size() > 1)
			for (unsigned int i = 0; i < this->terms_.size(); i++)
				for (unsigned int j = i; j < this->terms_.size(); j++)
					if (i != j && term::checker.plus_and_minus(this->terms_[i], this->terms_[j]))
					{
						this->terms_.push_back(this->terms_[i] + this->terms_[j]);

						this->terms_.erase(this->terms_.begin() + j);
						this->terms_.erase(this->terms_.begin() + i);
					}
		return *this;
	}

	//sums two term's exponents_ and swaps the term if the first has a lower degree (sum) or has the same degree and less variables_/exponents_
	polynomial order()
	{
		if (this->terms_.size() > 1)
			for (unsigned int i = 0, exp_sum1 = 0, exp_sum2 = 0; i < this->terms_.size(); i++, exp_sum1 = 0, exp_sum2 = 0)
				if (i + 1 < this->terms_.size())
				{
					for (unsigned int j = 0; j < this->terms_[i].get_variables().size(); j++)
						exp_sum1 += this->terms_[i].get_exponents()[j];
					for (unsigned int j = 0; j < this->terms_[i + 1].get_variables().size(); j++)
						exp_sum2 += this->terms_[i + 1].get_exponents()[j];
					if (exp_sum1 < exp_sum2 || exp_sum1 == exp_sum2 && this->terms_[i].get_variables().size() < this->terms_[i + 1].get_variables().size())
					{
						term const temp = this->terms_[i];
						this->terms_[i] = this->terms_[i + 1];
						this->terms_[i + 1] = temp;
						if (i > 0)
							i -= 2;
					}
				}
		return *this;
	}

	std::ostream friend& operator<<(std::ostream& os, polynomial const& poly)
	{
		if (poly.terms_.size() > 0)
		{
			os << poly.get_terms()[0];
			for (unsigned int i = 1; i < poly.get_terms().size(); i++)
			{
				if (poly.get_terms()[i].get_coefficient() > 0)
					os << " + ";
				else
					os << " - ";
				os << term{ abs(poly.get_terms()[i].get_coefficient()), poly.get_terms()[i].get_variables(), poly.get_terms()[i].get_exponents() };
			}
		}
		return os;
	}
};