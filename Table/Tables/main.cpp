#include <iostream>
#include <vector>
#include <algorithm>
#include "tables.h"
#include "avl_tree.h"
#include "unordered_array.h"
#include "hash_table.h"
#include "table_interface.h"

using namespace std;


int main()
{
	start();
	return 0;
	table < string, double, unordered_array > table1;
	table < string, double, avl_tree > table2;
	table < string, double, hash_table > table3;

	for (int i = 0; i < 100; i++)
	{
		table1.insert(std::to_string(i), exp(i));
		table2.insert(std::to_string(i), exp(i));
		table3.insert(std::to_string(i), exp(i));
	}
	auto it1 = table1.find("1");
	auto it2 = table2.find("1");
	auto it3 = table3.find("1");

	table1.erase("1");
	table2.erase("1");
	table3.erase("1");

	return 0;
}


//test1
//vector<int> v;
//
//for (int i = 0; i < 10'000'000; i++)
//{
//	int x = rand();
//	t.insert(x);
//	v.push_back(x);
//}
//
//sort(v.begin(), v.end());
//auto it = t.begin();
//
//for (int i = 0; i < v.size(); i++, ++it)
//{
//	if (v[i] != *it)
//	{
//		cout << v[i] << ' ' << *it << '\n';
//	}
//}

//test2
//avl_tree<int, std::string> t;
//
//for (int i = 0; i < 1'000; i++)
//{
//	int x = rand() % 1000;
//	string s;
//	s.push_back(char(x));
//	s.push_back(char(i));
//	s.push_back('\n');
//	//if(!t.find(x).second)
//	t.insert(x, s);
//}
//
//for (int i = 0; i < 2'000; i++)
//{
//	int x = rand() % 1000;
//	t.erase(x);
//}
//
//for (auto it = t.begin(); it != t.end(); ++it)
//cout << it->data << ' ';
//cout << '\n';