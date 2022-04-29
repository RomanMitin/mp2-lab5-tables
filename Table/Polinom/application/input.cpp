#include"input.h"

double getnumber(std::string s,int& index)
{
	double sign = 1.0;
	if (s[index] == '+')
	{
		index++;
	}
	
	if (s[index] == '-')
	{
		sign = -1.0;
		index++;
	}

	double result = 0;
	while (s[index] >= '0' && s[index] <= '9')
	{
		result *= 10.0;
		result += s[index] - '0';
		index++;
	}

	if (s[index] == '.')
	{
		index++;
		double power = 0.1;
		while (s[index] >= '0' && s[index] <= '9')
		{
			result += (s[index] - '0') * power;
			power *= 0.1;
			index++;
		}
	}
	return sign * result;
}

bool check_symbol(char c)
{
	return c >= '0' && c <= '9' || c == '.' || c == '(' || c == ')' || c == '-' || c == '+' || c == ' ';
}

void check_monom(std::string& s,int& index)
{

	if ((s[index] >= '0' && s[index] <= '9' || s[index] == '.' || s[index] == '-' || s[index] == '+') == false)
	{
		auto tmp = std::string("wrong symbol at ") + std::to_string(index);
		throw std::exception(tmp.c_str());
	}
	if(s[index] == '-' || s[index] == '+')
		index++;

	while (s[index] >= '0' && s[index] <= '9')
	{
		index++;
		if (index == s.size())
			throw std::exception("There are not enough characters in the polinom");
	}

	if (s[index] == '.')
	{
		index++;
		if (index == s.size())
			throw std::exception("There are not enough characters in the polinom");
	}

	while (s[index] >= '0' && s[index] <= '9')
	{
		index++;
		if (index == s.size())
			throw std::exception("There are not enough characters in the polinom");
	}

	if (s[index] != '(')
	{
		auto tmp = std::string("wrong symbol at ") + std::to_string(index);
		throw std::exception(tmp.c_str());
	}
	else
		index++;

	if (index == s.size())
		throw std::exception("There are not enough characters in the polinom");

	int i;
	for (i = index; i < index + 3; i++)
	{
		if (i >= s.size())
			throw std::exception("There are not enough characters in the polinom");

		if (s[i] == ')')
		{
			break;
		}
		if (s[i] < '0' || s[i]>'9')
		{
			auto tmp = std::string("wrong symbol at ") + std::to_string(index);
			throw std::exception(tmp.c_str());
		}
	}
	index = i;
	if (s[i] != ')')
	{
		auto tmp = std::string("wrong symbol at ") + std::to_string(i);
		throw std::exception(tmp.c_str());
	}
}

void correct(std::string& s)
{
	auto it = s.begin();
	while ((it = std::find(s.begin(), s.end(), ' ')) != s.end())
		s.erase(it);

	for (int i = 0; i < s.size(); i++)
		if (!check_symbol(s[i]))
			throw std::exception("Wrong synbol in input string");

	int index = 0;
	while (index < s.size())
	{
		check_monom(s, index);
		index++;
	}

}

list<monom> parcer(std::string s)
{
	int index = 0;
	list<monom> result;
	while (index != s.size())
	{
		double coef = getnumber(s, index);
		index++;
		int pow = getnumber(s, index);
		monom tmp(coef, pow);
		if (coef != 0.0)
		{
			result.add(tmp);
		}
		index++;
	}
	return result;
}

polinom& polinom::operator=(std::string& s)
{
	correct(s);
	monoms = parcer(s);
	return *this;
}