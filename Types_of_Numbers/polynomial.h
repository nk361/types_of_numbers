#pragma once
#include "stdafx.h"

#include "term.h"

class polynomial
{
	std::vector<term> terms_;
public:
	polynomial() { this->set_terms({}); }
	polynomial(std::initializer_list<term> const& trms) { this->set_terms(trms); }

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
				this->add_term(positive ? token : '-' + token);//calls the term string constructor to interpret more
			poly.erase(0, pos + 1);
		}
	}

	std::vector<term> get_terms() const { return this->terms_; }
	void set_terms(std::vector<term> const& trms) { this->terms_ = trms; }

	void set_term(int const& index, term const& trm) { this->terms_[index] = trm; }
	void add_term(term const& trm) { this->terms_.push_back(trm); }
	void remove_term(int const& index) { this->terms_.erase(terms_.begin() + index); }

	polynomial friend operator+(polynomial const& poly1, polynomial const& poly2)
	{
		return combine_polynomials(poly1, poly2).combine_like_terms().order();
	}

	polynomial friend operator-(polynomial const& poly1, polynomial const& poly2)
	{
		polynomial temp = poly2;
		for (unsigned int i = 0; i < temp.get_terms().size(); i++)
			temp.set_term(i, { temp.get_terms()[i].get_coefficient() * -1, temp.get_terms()[i].get_variables(), temp.get_terms()[i].get_exponents() });
		return combine_polynomials(poly1, temp).combine_like_terms().order();
	}

	polynomial friend operator*(polynomial const& poly1, polynomial const& poly2)
	{
		polynomial temp;
		for (unsigned int i = 0; i < poly1.get_terms().size(); i++)
			for (unsigned int j = 0; j < poly2.get_terms().size(); j++)
				temp.add_term(poly1.get_terms()[i] * poly2.get_terms()[j]);
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
		for (unsigned int i = 0; i < poly2.get_terms().size(); i++)
			temp.add_term(poly2.get_terms()[i]);
		return temp;
	}
	
	//adds terms with the same variables_ and exponents_ to each other then removes the higher index item before the lower so the higher index remains the same
	polynomial combine_like_terms()
	{
		if (this->get_terms().size() > 1)
			for (unsigned int i = 0; i < this->get_terms().size(); i++)
				for (unsigned int j = i; j < this->get_terms().size(); j++)
					if (i != j && term::checker.plus_and_minus(this->get_terms()[i], this->get_terms()[j]))
					{
						this->add_term(this->get_terms()[i] + this->get_terms()[j]);

						this->remove_term(j);
						this->remove_term(i);
					}
		return *this;
	}

	//sums two term's exponents_ and swaps the term if the first has a lower degree (sum) or has the same degree and less variables_/exponents_
	polynomial order()
	{
		if (this->get_terms().size() > 1)
			for (unsigned int i = 0, exp_sum1 = 0, exp_sum2 = 0; i < this->get_terms().size(); i++, exp_sum1 = 0, exp_sum2 = 0)
				if (i + 1 < this->get_terms().size())
				{
					for (unsigned int j = 0; j < this->get_terms()[i].get_variables().size(); j++)
						exp_sum1 += this->get_terms()[i].get_exponents()[j];
					for (unsigned int j = 0; j < this->get_terms()[i + 1].get_variables().size(); j++)
						exp_sum2 += this->get_terms()[i + 1].get_exponents()[j];
					if (exp_sum1 < exp_sum2 || exp_sum1 == exp_sum2 && this->get_terms()[i].get_variables().size() < this->get_terms()[i + 1].get_variables().size())
					{
						term const temp{ this->get_terms()[i] };
						this->set_term(i, this->get_terms()[i + 1]);
						this->set_term(i + 1, temp);
						if (i > 0)
							i -= 2;
					}
				}
		return *this;
	}

	std::ostream friend& operator<<(std::ostream& os, polynomial const& poly)
	{
		if (poly.get_terms().size() > 0)
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