#pragma once
#include "stdafx.h"

class general_math_functions
{
public:
	//checks if any number less than the param divides with no remainder. if not, returns true
	bool static is_prime(int const& num)
	{
		for (int i = num - 1; i > 1; i--)
			if (num % i == 0)
				return false;
		return true;
	}

	//divides the number by primes less than it and adding them to a vector if they divide equally into a changing copy
	std::vector<int> static factorize(int const& num)
	{
		std::vector<int> factors;
		for (int i = num - 1, n = num; i > 1; i--)
			if (is_prime(i) && n % i == 0)
			{
				factors.push_back(i);
				n /= i;
				i++;
			}
		return factors;
	}

	//divides number's remainders down until an even division is made between the last remainder and the current remainder is made
	int static gcd(int num1, int num2)
	{
		if (num1 < 1)
			num1 *= -1;
		if (num2 < 1)
			num2 *= -1;
		if (num2 > num1)
			std::swap(num1, num2);
		if (num1 % num2 == 0)
			return num2;
		return gcd(num2, num1 % num2);
	}
	
	//takes many numbers and adds them to a list, then the gcd of each pair of two is added to the list and the originals removed, returning the final gcd result
	int static gcd(std::vector<int> nums)
	{
		std::vector<int> divisors;
		for (unsigned int i = 0; i < nums.size(); i++)
			if (i + 1 < nums.size())
				divisors.push_back(gcd(nums[i], nums[i + 1]));
		while (divisors.size() != 1)
			for (unsigned int i = 0; i < divisors.size(); i++)
				if (i + 1 < divisors.size())
				{
					divisors.push_back(gcd(divisors[i], divisors[i + 1]));
					if (divisors.size() > 2)
					{
						divisors.erase(divisors.begin() + i);
						divisors.erase(divisors.begin() + i + 1);
					}
				}
		return divisors[0];
	}

	//gets the result of division between the param's product divided by the highest number in common to find what both numbers can become as equal denominators
	int static lcm(int const& num1, int const& num2) { return num1 * num2 / gcd(num1, num2); }

	//same custom algorithm as gcd, but calls lcm with two params
	int static lcm(std::vector<int> nums)
	{
		std::vector<int> multiples;
		for (unsigned int i = 0; i < nums.size(); i++)
			if (i + 1 < nums.size())
				multiples.push_back(lcm(nums[i], nums[i + 1]));
		while (multiples.size() != 1)
			for (unsigned int i = 0; i < multiples.size(); i++)
				if (i + 1 < multiples.size())
				{
					multiples.push_back(lcm(multiples[i], multiples[i + 1]));
					if (multiples.size() > 2)
					{
						multiples.erase(multiples.begin() + i);
						multiples.erase(multiples.begin() + i + 1);
					}
				}
		return multiples[0];
	}

	//takes the amount of fibonacci numbers requested as param, makes a vector to store values, adds 1 twice, adds the last two values summed, and returns them
	std::vector<int> static fibonacci(unsigned int const& amount)//wonder if negetive, if the spiral reverses?
	{
		std::vector<int> fib_values;
		for (unsigned int i = 0; i < amount; i++)
			if (i == 0 || i == 1)
				fib_values.push_back(1);
			else
				fib_values.push_back(fib_values[i - 2] + fib_values[i - 1]);
		return fib_values;
	}
};