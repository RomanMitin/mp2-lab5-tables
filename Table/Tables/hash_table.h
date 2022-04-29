#pragma once
#include<utility>
#include<string>
#include<unordered_set>
#include"list.h"

static const size_t size = 1000;

//template<typename T,typename U>
//using list my::list<T,U>

template<typename T>
inline size_t get_hash(const T& key)
{
	std::hash<T> hasher;
	return hasher(key) % size;
}

template<>
inline size_t get_hash(const std::string& key)
{
	size_t hash = 0;
	for (size_t i = 0; i < key.size(); i++)
	{
		hash += key[i] * (i + 1);
	}
	return hash % ::size;
}

template<typename T, typename U>
class hash_table
{
	my::list<T, U> data[size];

public:
	struct iterator
	{
		typename my::list<T, U>::node* p;
		iterator(typename my::list<T, U>::node* n) :p(n) {};
	};

	std::pair<int, iterator> find(const T& key)
	{
		return std::pair<int, iterator>(data[get_hash(key)].find(key));
	}

	int insert(const T& key, const U& tmpdata)
	{
		return data[get_hash(key)].insert(key, tmpdata);
	}

	int erase(const T& key)
	{
		return data[get_hash(key)].erase(key);
	}
};

