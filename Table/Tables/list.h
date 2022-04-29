#pragma once
#include <utility>

namespace my
{
	template<typename T, typename U>
	class list
	{
	public:
		struct node
		{
			T val;
			U data;
			node* next;

			node() :val(), data(), next(nullptr) {}
		};

		node* top;

		list() :top(new node) {}

		~list()
		{
			auto it = top->next;
			auto to_delete = top;
			while (it != nullptr)
			{
				delete to_delete;
				to_delete = it;
				it = it->next;
			}
			delete to_delete;
		}

		std::pair<int, node*> find(const T& key)
		{
			int count = 0;
			auto it = top->next;
			while (it != nullptr)
			{
				if (it->val == key)
					break;
				count++;
				it = it->next;
			}
			return std::make_pair(count, it);
		}

		int insert(const T& key, const U& data)
		{
			node* tmp = new node;
			tmp->val = key;
			tmp->data = data;
			tmp->next = top->next;
			top->next = tmp;
			return 0;
		}

		int erase(const T& key)
		{
			int count = 0;
			auto it = top->next;
			auto prev = top;
			while (it != nullptr)
			{
				if (it->val == key)
				{
					prev->next = it->next;
					delete it;
					break;
				}
				count++;
				prev = it;
				it = it->next;
			}

			return count;
		}

	};
}