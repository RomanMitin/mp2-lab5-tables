#pragma once
#include <fstream>
#include <string>
#include <utility>
#include "unordered_array.h"
#include "avl_tree.h"
#include "hash_table.h"

template<template <typename T,typename V> class U>
struct template_name
{
	constexpr operator std::string_view()
	{
		return std::string_view("Unknown");
	}
};

template<typename T, typename U, template<typename H, typename G> class Container>
class table
{
	Container<T, U> data;
	inline static std::ofstream log_file{};
public:
	table() = default;
	table(const table&) = default;
	~table() = default;

	typename Container<T,U>::iterator find(const T& key)
	{
		log_file.open(log_file_name.data(), std::ios_base::app);
		/*std::pair<int, bool>*/ auto count_operation = data.find(key);

		log_file << "Container type: " << container_type << '\t';
		log_file << " Value: " << std::string(key) << " Find in table with " << count_operation.first << " operation\n";
		log_file.close();
		
		return count_operation.second;
	}

	void insert(const T& key,const U& tmpdata)
	{
		log_file.open(log_file_name.data(), std::ios_base::app);
		int count_operation = data.insert(key, tmpdata);

		log_file << "Container type: " << container_type << '\t';
		log_file << " Value: " << std::string(key) << " insert in table with " << count_operation << " operation\n";
		log_file.close();
	}

	void erase(const T& key)
	{
		log_file.open(log_file_name.data(), std::ios_base::app);
		int count_operation = data.erase(key);

		log_file << "Container type: " << container_type << '\t';
		log_file << " Value: " << std::string(key) << " erase from table with " << count_operation << " operation\n";
		log_file.close();
	}

	static constexpr std::string_view log_file_name = "Log_file1.txt";
	static constexpr std::string_view container_type = std::string_view(template_name<Container> ());
};

template<> 
constexpr template_name<unordered_array>::operator std::string_view()
{
	return std::string_view("unordered_array");
}

template<>
constexpr template_name<avl_tree>::operator std::string_view()
{
	return std::string_view("avl_tree");
}

template<>
constexpr template_name<hash_table>::operator std::string_view()
{
	return std::string_view("hash_table");
}