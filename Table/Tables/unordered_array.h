#pragma once
#include <vector>
#include <utility>

template<typename T,typename U>
class unordered_array
{
	std::vector<std::pair<T, U>> data;

public:

	struct iterator
	{
		iterator() = default;
		iterator(std::pair<T, U>* tmp) :p(tmp) {}
		iterator(const iterator&) = default;
		~iterator() = default;
	
		operator std::pair<T, U>* () { return p; }

		std::pair<T, U>* p;
	};

	std::pair<int,typename unordered_array<T,U>::iterator> find(const T& key)
	{
		int count = 0;
		for (auto it = data.begin(); it != data.end(); ++it)
		{
			if (it->first == key)
				return std::make_pair(count, unordered_array::iterator(&*it));
				count++;
		}
		return std::make_pair(count, unordered_array::iterator(nullptr));
	}

	int insert(const T& key, const U& tmpdata)
	{
		data.push_back(std::make_pair(key, tmpdata));
		return 1;
	}

	int erase(const T& key)
	{
		auto p = find(key);
		int count = p.first;
		if (p.second != nullptr)
		{
			auto tmp = std::move(*p.second);
			*p.second = data.back();
			data.back() = tmp;
			data.pop_back();
		}

		return count;
	}

	unordered_array() = default;
	unordered_array(const unordered_array&) = default;
	~unordered_array() = default;

};
