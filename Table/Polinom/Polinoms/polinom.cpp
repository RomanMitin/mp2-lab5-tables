#include "polinom.h"



polinom polinom::operator+(const polinom& sec) const
{
	list<monom> l;

	auto it = l.top;
	auto it1 = this->monoms.top;
	auto it2 = sec.monoms.top;
 
	while (it1 != nullptr && it2 != nullptr)
	{
		if (it1->val.power == it2->val.power)
		{
			if (it1->val.coef + it2->val.coef != 0)
			{
				auto tmp = new list<monom>::cell<monom>;
				tmp->val.power = it1->val.power;
				tmp->val.coef = it1->val.coef + it2->val.coef;
				it->next = tmp;
				it = tmp;
			}
			
			it1 = it1->next;
			it2 = it2->next;
		}
		else
		{
			if (it1->val < it2->val)
			{
				auto tmp = new list<monom>::cell<monom>;
				tmp->val = it1->val;
				it->next = tmp;
				it = tmp;
				it1 = it1->next;
			}
			else
			{
				auto tmp = new list<monom>::cell<monom>;
				tmp->val = it2->val;
				it->next = tmp;
				it = tmp;
				it2 = it2->next;
			}
		}
	}

	while (it1 != nullptr)
	{
		auto tmp = new list<monom>::cell<monom>;
		tmp->val = it1->val;
		it->next = tmp;
		it = tmp;
		it1 = it1->next;
	}

	while (it2 != nullptr)
	{
		auto tmp = new list<monom>::cell<monom>;
		tmp->val = it2->val;
		it->next = tmp;
		it = tmp;
		it2 = it2->next;
	}

	return polinom(l);
}

polinom polinom::operator*(double sec) const
{
	list<monom> l;
	if (sec == 0.0)
		return polinom(l);

	auto it = l.top;
	auto it2 = this->monoms.top->next;

	while (it2 != nullptr)
	{
		if (it2->val.coef * sec != 0)
		{
			auto tmp = new list<monom>::cell<monom>;
			tmp->val.power = it2->val.power;
			tmp->val.coef = it2->val.coef * sec;
			it->next = tmp;
			it = tmp;
		}
		it2 = it2->next;
	}

	return polinom(l);
}

polinom polinom::operator*(const polinom& sec) const
{
	list<monom> l;

	auto it1 = this->monoms.top;

	while (it1 != nullptr)
	{
		auto it2 = sec.monoms.top;
		while (it2 != nullptr)
		{
			l.add_front(it1->val * it2->val);
			it2 = it2->next;
		}
		it1 = it1->next;
	}

	l.sort();

	auto previt = l.top;
	auto it = l.top->next;
	while (it != nullptr)
	{

		auto tmp = it->next;
		double coef = it->val.coef;
		while (tmp != nullptr && tmp->val.power == it->val.power)
		{
			auto del = tmp;
			coef += del->val.coef;
			tmp = tmp->next;
			delete del;
		}

		if (coef != 0)
		{
			it->val.coef = coef;
			it->next = tmp;
			it = it->next;
			previt = previt->next;
		}
		else
		{
			previt->next = tmp;
			delete it;
			it = previt->next;
		}
		
	}

	return polinom(l);
}