#pragma once
#include<iostream>
#include<exception>


template<typename T>
class list
{
	template<typename T>
	class cell
	{
	public:
		T val;
		cell* next;
		cell() :val(), next(nullptr) {}
		~cell() {};
	};

	cell<T>* top;

	void add_front(const T& val);

	void sort();

	static cell<T>* merge(cell<T>*, cell<T>*, int);

	friend class polinom;

public:

	list() { top = new cell<T>; }
	list(const list& sec)
	{
		top = new cell<T>;
		cell<T>* it1 = top;
		cell<T>* it2 = sec.top;
		while (it2->next != nullptr)
		{
			it2 = it2->next;
			cell<T>* tmp = new cell<T>;
			tmp->val = it2->val;
			it1->next = tmp;
			it1 = tmp;
		}
	}

	list(list&& sec) :top(sec.top) { sec.top = nullptr; }

	list& operator=(const list& sec)
	{
		if (this == &sec)
			return *this;

		cell<T>* tmp = top;
		while (top != nullptr)
		{
			top = top->next;
			delete tmp;
			tmp = top;
		}

		top = new cell<T>;
		cell<T>* it1 = top;
		cell<T>* it2 = sec.top;
		while (it2->next != nullptr)
		{
			it2 = it2->next;
			tmp = new cell<T>;
			tmp->val = it2->val;
			it1->next = tmp;
			it1 = tmp;
		}

		return *this;
	}

	list& operator=(list&& sec)
	{
		if (this == &sec)
			return *this;

		while (top != nullptr)
		{
			cell<T>* tmp = top;
			top = top->next;
			delete tmp;
			tmp = top;
		}

		top = sec.top;
		sec.top = nullptr;
		return *this;
	}

	//const T& front() { return top->next->val; }

	bool operator==(const list& sec) const
	{
		if (this == &sec)
			return true;

		cell<T>* it1 = top->next;
		cell<T>* it2 = sec.top->next;
		while (it1 != nullptr && it2 != nullptr)
		{
			if (it1->val != it2->val)
			{
				return false;
			}
			it1 = it1->next;
			it2 = it2->next;
		}
		return it2 == nullptr && it1 == nullptr;
	}

	bool operator!=(const list& sec) const
	{
		return !(*this == sec);
	}
	
	void add(const T& val);
	//void delete_by_val(const T& val);

	bool empty() const { return top->next == nullptr; }

	void clear();

	void erase(const T& val);

	friend std::ostream& operator<<(std::ostream& str, const list& l)
	{
		cell<T>* it = l.top->next;
		while (it != nullptr)
		{
			str << it->val << ' ';
			it = it->next;
		}
		str << '\n';
		return str;
	}

	~list()
	{
		cell<T>* tmp = top;

		while (top != nullptr)
		{
			top = top->next;
			delete tmp;
			tmp = top;
		}
	}
};

template<typename T>
void list<T>::add(const T& val)
{
	cell<T>* tmp = new cell<T>;
	tmp->val = val;
	
	cell<T>* it = top;
	while (it->next != nullptr && it->next->val < val)
		it = it->next;

	tmp->next = it->next;
	it->next = tmp;
}

template<typename T>
void list<T>::add_front(const T& val)
{
	cell<T>* tmp = new cell<T>;
	tmp->val = val;
	tmp->next = top->next;
	top->next = tmp;
}

template<typename T>
void list<T>::sort()
{
	for (int cur_size = 2; true; cur_size *= 2)
	{
		cell<T>* it1 = top->next;
		cell<T>* it2 = top->next;

		for (int i = 0; it2 != nullptr && i < cur_size / 2; i++)
		{
			it2 = it2->next;
		}
		if (it2 == nullptr)
			break;

		top->next = it1->val < it2->val ? it1 : it2;;

		while (it2 != nullptr)
		{
			cell<T>* tmpit2 = it2;
			for (int i = 0; tmpit2 != nullptr && i < cur_size / 2; i++)
			{
				tmpit2 = tmpit2->next;
			}
			cell<T>* tmp = merge(it1, it2, cur_size / 2);
			
			it1 = tmpit2;
			it2 = tmpit2;
			
			for (int i = 0; it2 != nullptr && i < cur_size / 2; i++)
			{
				it2 = it2->next;
			}

			if (it2 != nullptr)
			{
				tmp->next = it1->val < it2->val ? it1 : it2;
			}
			else
			{
				tmp->next = it1;
			}
		}
	}
}


template<typename T>
list<T>::cell<T>* list<T>::merge(cell<T>* it1, cell<T>* it2,int size)
{
	int count1 = 0;
	int count2 = 0;

	cell<T>* tmp;
	if (it1->val < it2->val)
	{
		tmp = it1;
		it1 = it1->next;
		count1++;
	}
	else
	{
		tmp = it2;
		it2 = it2->next;
		count2++;
	}

	while (count1 < size && it2 != nullptr && count2 < size)
	{
		if (it1->val < it2->val)
		{
			tmp->next = it1;
			it1 = it1->next;
			count1++;
		}
		else
		{
			tmp->next = it2;
			it2 = it2->next;
			count2++;
		}
		tmp = tmp->next;
	}

	while (count1 < size)
	{
		tmp->next = it1;
		it1 = it1->next;
		tmp = tmp->next;
		count1++;
		
	}

	while (it2 != nullptr && count2 < size)
	{
		tmp->next = it2;
		it2 = it2->next;
		tmp = tmp->next;
		count2++;
	}

	return tmp;
}


//template<typename T>
//void list<T>::delete_by_val(const T& val)
//{
//	cell* it = top;
//	cell* tmp;
//	while (it != nullptr && it->next != nullptr)
//	{
//		if (it->next->val == val)
//		{
//			tmp = it->next;
//			while (tmp->next != nullptr && tmp->next->val == val)
//			{
//				cell* tmp2 = tmp;
//				tmp = tmp->next;
//				delete tmp2;
//			}
//			it->next = tmp->next;
//			delete tmp;
//		}
//		it = it->next;
//	}
//}
