#pragma once
#include <utility>
#include <exception>

template<typename T,typename U>
struct node;

template<typename T, typename U>
int getheifght(node<T,U>* n);

template<typename T,typename U>
struct node
{
	T val;
	U data;
	node* lch, * rch, * parent;
	uint8_t heigt;

	node() :val(), lch(nullptr), rch(nullptr), heigt(0) {}
	node(const node&) = default;
	node(T key, U data, uint8_t h) :val(key), data(data), lch(nullptr), rch(nullptr), parent(nullptr), heigt(h) {};
	~node() = default;


	int8_t getbfactor()
	{
		return getheifght(this->rch) - getheifght(this->lch);
	}

	void fixheight()
	{
		this->heigt = std::max(getheifght(this->lch), getheifght(this->rch)) + 1;
	}

	operator T()
	{
		return val;
	}
};

template<typename T, typename U>
int getheifght(node<T,U>* n)
{
	if (n == nullptr)
		return 0;
	return n->heigt;
}

template<typename T, typename U>
class avl_tree
{
public:
	node<T,U>* top;

	void balance(node<T,U>*);

	void left_rotation(node<T,U>*);
	void right_rotation(node<T,U>*);
	/*void big_left_rotation(node<T,U>*);
	void big_right_rotation(node<T,U>*);*/

	void delete_node(node<T,U>*);


	class iterator
	{
		friend class avl_tree;

		node<T,U>* p;
	public:
		iterator(node<T,U>* pointer) :p(pointer) {}
		bool is_end() { return p == nullptr; }

		node<T,U>& operator*()
		{
			return *p;
		}

		node<T,U>* operator->()
		{
			return &**this;
		}

		iterator& operator++()
		{
			if (p == nullptr)
				throw std::exception();

			if (p->rch == nullptr)
			{
				while (p->parent != nullptr && p->parent->rch == p)
				{
					p = p->parent;
				}
				p = p->parent;
			}
			else
			{
				p = p->rch;
				while (p->lch != nullptr)
					p = p->lch;
			}
			return *this;
		}

		iterator& operator--()
		{
			if (p->lch == nullptr)
			{
				while (p->parent != nullptr && p->parent->lch == p)
				{
					p = p->parent;
				}
				p = p->parent;
			}
			else
			{
				p = p->lch;
				while (p->rch != nullptr)
				{
					p = p->rch;
				}
			}
			return *this;
		}

		bool operator==(const iterator& sec) { return p == sec.p; }
		bool operator!=(const iterator& sec) { return p != sec.p; }
	};

	avl_tree() :top(nullptr) {};
	//avl_tree(const avl_tree&);

	std::pair<int, avl_tree<T, U>::iterator> find(const T&);
	int insert(const T&, const U&);
	int erase(const T&);

	iterator begin()
	{
		iterator it = top;
		if (top != nullptr)
		{
			while (it->lch != nullptr)
				it.p = it.p->lch;
		}
		return it;
	}

	iterator end()
	{
		avl_tree::iterator it = nullptr;
		return it;
	}

	~avl_tree();

	//template<typename T>

};

template<typename T, typename U>
std::pair<int,typename avl_tree<T,U>::iterator> avl_tree<T,U>::find(const T& key)
{
	int count = 0;

	node<T,U>* it = this->top;
	while (it != nullptr && it->val != key)
	{
		it = it->val > key ? it->lch : it->rch;
		count++;
	}

	return std::make_pair(count, it);
}

template<typename T, typename U>
int avl_tree<T, U>::insert(const T& key, const U& data)
{
	int count = 0;

	if (top != nullptr)
	{
		node<T,U>* it = top;
		node<T,U>* next = it;
		bool is_right;

		while (next != nullptr)
		{
			it = next;
			if (it->val > key)
			{
				is_right = false;
				next = it->lch;
			}
			else
			{
				is_right = true;
				next = it->rch;
			}
			count++;
		}

		next = new node<T,U>(key, data, 1);
		next->parent = it;
		if (is_right)
		{
			it->rch = next;
		}
		else
			it->lch = next;

		balance(it);
	}
	else
	{
		top = new node<T,U>(key, data, 1);
	}

	return count;

}

template<typename T, typename U>
void avl_tree<T,U>::balance(node<T,U>* it)
{
	while (it != nullptr)
	{
		if (std::abs(it->getbfactor()) == 2)
		{
			if (it->getbfactor() == 2)
			{
				if (it->rch->getbfactor() != -1)
				{
					left_rotation(it);
				}
				else
				{
					right_rotation(it->rch);
					left_rotation(it);
				}
			}
			else
			{
				if (it->lch->getbfactor() != 1)
				{
					right_rotation(it);
				}
				else
				{
					left_rotation(it->lch);
					right_rotation(it);
				}
			}
		}

		it->fixheight();
		this->top = it;
		it = it->parent;
	}
}

template<typename T, typename U>
int avl_tree<T, U>::erase(const T& key)
{
	int count = 0;
	node<T,U>* it = nullptr;
	node<T,U>* next = top;
	bool is_left;
	while (next != nullptr && next->val != key)
	{
		it = next;
		if (next->val < key)
		{
			next = next->rch;
			is_left = false;
		}
		else
		{
			next = next->lch;
			is_left = true;
		}

		count++;
	}

	if (next != nullptr)
	{
		if (next->lch != nullptr && next->rch != nullptr)
		{
			avl_tree<T, U>::iterator iter = next;
			++iter;
			next->val = iter->val;
			iter->val = key;
			next = iter.p;
			it = next->parent;
			if (it->lch == next)
				is_left = true;
			else
				is_left = false;
		}

		if (it != nullptr)
		{
			if (next->lch == nullptr)
			{
				if (next->rch != nullptr)
					next->rch->parent = it;

				if (is_left)
					it->lch = next->rch;
				else
					it->rch = next->rch;
			}
			else
			{
				if (next->lch != nullptr)
					next->lch->parent = it;

				if (is_left)
					it->lch = next->lch;
				else
					it->rch = next->lch;
			}
			delete next;
			balance(it);
		}
		else
		{
			if (next->lch == nullptr && next->rch == nullptr)
				top = nullptr;
			else
			{
				if (next->lch != nullptr)
				{
					next->lch->parent = nullptr;
					top = next->lch;
				}
				else
				{
					next->rch->parent = nullptr;
					top = next->rch;
				}
			}
			delete next;
		}
		
	}

	return count;
}

template<typename T, typename U>
void avl_tree<T,U>::left_rotation(node<T,U>* it)
{
	node<T,U>* tmpp = it->parent, * tmp = it->rch->lch;

	it->rch->lch = it;
	if (it->parent != nullptr)
	{
		if (it->parent->lch == it)
		{
			it->parent->lch = it->rch;
		}
		else
		{
			it->parent->rch = it->rch;
		}
	}
	it->parent = it->rch;
	it->rch->parent = tmpp;

	it->rch = tmp;

	if (tmp != nullptr)
		tmp->parent = it;

	it->fixheight();
	it->parent->fixheight();
}

template<typename T, typename U>
void avl_tree<T,U>::right_rotation(node<T,U>* it)
{
	node<T,U>* tmpp = it->parent, * tmp = it->lch->rch;

	it->lch->rch = it;
	if (it->parent != nullptr)
	{
		if (it->parent->lch == it)
		{
			it->parent->lch = it->lch;
		}
		else
		{
			it->parent->rch = it->lch;
		}
	}
	it->parent = it->lch;

	it->lch->parent = tmpp;

	it->lch = tmp;

	if (tmp != nullptr)
		tmp->parent = it;

	it->fixheight();
	it->parent->fixheight();
}

template<typename T, typename U>
void avl_tree<T,U>::delete_node(node<T,U>* n)
{
	if (n != nullptr)
	{
		delete_node(n->lch);
		delete_node(n->rch);
		delete n;
	}
}
template<typename T, typename U>
avl_tree<T,U>::~avl_tree()
{
	delete_node(this->top);
}

