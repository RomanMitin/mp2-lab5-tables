#pragma once
#include<exception>
#include<iostream>

bool check_power(int a, int b);

class monom
{
public:
	int power;
	double coef;

	monom(double coef = 0, int power = 0) :coef(coef), power(power) {};

	bool operator==(const monom& sec) const { return power == sec.power && coef == sec.coef; }
	bool operator!=(const monom& sec) const { return !(*this == sec); }
	bool operator<(const monom& sec) const { return power < sec.power; }

	monom operator+(const monom& sec) const 
	{
		if (power != sec.power)
			throw std::exception("Wrong powers in monom plus operator");
		return monom(coef + sec.coef, power);
	}

	monom operator*(const monom& sec) const
	{
		if (!check_power(power,sec.power))
			throw std::exception("Power overflow in monom multiply");
		return monom(coef * sec.coef, power + sec.power);
	}

	friend std::ostream& operator<<(std::ostream& str, const monom& m)
	{
		if (m.coef > 0)
			str << '+';
		str << m.coef << "x^" << m.power / 100 << "*y^" << m.power / 10 % 10 << "*z^" << m.power % 10;
		return str;
	}
};

