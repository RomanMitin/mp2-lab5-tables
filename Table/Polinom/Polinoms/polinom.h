#pragma once
#include<string>
#include"monom.h"
#include"..\\List\list.h"

class polinom
{
	list<monom> monoms;
public:
	polinom() :monoms() {}

	polinom(const list<monom> &l) :monoms(l) {}
	polinom(list<monom> &&l) :monoms(l) {}

	polinom(const polinom& p) :monoms(p.monoms) {}
	polinom(polinom&& p) :monoms(p.monoms) {}

	polinom& operator=(const polinom& sec) { monoms = sec.monoms; return *this; }
	polinom& operator=(polinom&& sec) { monoms = sec.monoms; return *this; }

	polinom& operator=(std::string& s);

	bool operator==(const polinom& sec) const { return this->monoms == sec.monoms; }
	bool operator!=(const polinom& sec) const { return this->monoms != sec.monoms; }

	polinom operator+(const polinom& sec) const;
	polinom operator-(const polinom& sec) const { return this->operator+(sec * -1.0); }

	polinom operator*(double sec) const;
	friend polinom operator*(double sec, const polinom& p) { return p.operator*(sec); }

	polinom operator*(const polinom& sec) const;

	friend std::ostream& operator<<(std::ostream& str, const polinom& l)
	{
		if (!l.monoms.empty())
			str << l.monoms;
		else 
			str << 0;
		return str;
	}
};

