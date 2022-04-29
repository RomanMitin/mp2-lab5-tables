#include<iostream>
#include"unordered_array.h"
#include"avl_tree.h"
#include"hash_table.h"
#include"tables.h"
#include"..\\Polinom\Polinoms\polinom.h"
#include"..\\Polinom\application\interface.h"

using namespace std;

table<string, polinom, unordered_array> table1;
table<string, polinom, avl_tree> table2;
table<string, polinom, hash_table> table3;

polinom* find(const string& name)
{
	auto tmp = table1.find(name).p;
	if (tmp != nullptr)
	{
		if (tmp->second != table2.find(name)->data)
			throw 1;
		if (tmp->second != table3.find(name).p->data)
			throw 2;
		return &tmp->second;
	}
	else
	{
		if (!table2.find(name).is_end())
			throw 3;
		if (nullptr != table3.find(name).p)
			throw 4;
		return nullptr;
	}
	
}

void insert(const polinom& p, const string& name)
{
	table1.insert(name, p);
	table2.insert(name, p);
	table3.insert(name, p);
}

void erase(const string& name)
{
	table1.erase(name);
	table2.erase(name);
	table3.erase(name);
}

void menu()
{
	cout << "Choose what do you want to do\n";
	cout << "1. Insert polinom in tables\n";
	cout << "2. Find polinom in tables by key\n";
	cout << "3. Erase polinom from table by key\n";
	cout << "4. End\n";
}

void print_and_get_polinom(polinom& p,string& name)
{
	cout << "To enter monom, first write the coefficient in front of it,\n";
	cout << "Then write a three-digit number in parentheses (it is possible without leading zeros) \ndenoting the degree of a monom\n";
	cout << "To enter polinom write sequence of monon and press enter when you are done\n";
	cout << "Enter polinom:\n";

	get_polinom(p);

	cout << "You enter: " << p << '\n';

	cout << "Enter name of polinom\n";
	cin >> name;
}

void work_with_polinoms(polinom& p, string& s)
{
	polinom first = p, second, result = p;
	

	bool flag = true;
	while (flag)
	{
		flag = false;
		cout << "\nChoose digit for operation to do\n";
		cout << "1. Add polinoms\n";
		cout << "2. Subtract polinoms\n";
		cout << "3. Multiply polinom on number\n";
		cout << "4. Multiply polinoms\n";
		cout << "5. Nofthing\n";

		int a;
		cin >> a;
		switch (a)
		{
		case 1:
			cout << "Enter second polinom:\n";
			get_polinom(second);
			cout << "You enter: " << second << '\n';
			result = first + second;
			break;
		case 2:
			cout << "Enter second polinom:\n";
			get_polinom(second);
			cout << "You enter: " << second << '\n';
			result = first - second;
			break;
		case 3:
			cout << "Enter number\n";
			double num;
			cin >> num;
			result = first * num;
			break;
		case 4:
			cout << "Enter second polinom:\n";
			get_polinom(second);
			cout << "You enter: " << second << '\n';
			result = first * second;
			break;
		case 5:
			break;
		default:
			flag = true;
			cout << "Wrong number, try again\n";
			break;
		}
	}

	cout << "Result is:\n";
	cout << result;
	string newname;
	cout << "Enter name for result\n";
	cin >> newname;

	cout << "What to do with the result\n";
	cout << "1. Store in table\n";
	cout << "2. Perform new operations with result\n";
	cout << "3. Nofthing\n";
	int a;
	cin >> a;
	switch (a)
	{
	case 1:
		insert(result, newname);
		cout << "Done!\n";
		break;
	case 2:
		work_with_polinoms(result, newname);
		break;
	default:
		break;
	}
	
}



void start()
{
	{
		ofstream tmp;
		tmp.open(table<string, polinom, avl_tree>::log_file_name.data());
		tmp.close();
	}
	cout << "Labwork5___TABLES\n";
	
	bool flag = true;
	while (flag)
	{
		menu();

		int a;
		polinom p;
		string s;
		polinom* pol_pointer;
		cin >> a;
		switch (a)
		{
		case 1:
			print_and_get_polinom(p, s);
			insert(p, s);
			cout << "Done!\n";
			break;
		case 2:
			cout << "Enter key:\n";
			cin >> s;
			pol_pointer = find(s);
			if (pol_pointer == nullptr)
			{
				cout << "Their is no such polinom\n";
				break;
			}
			p = *pol_pointer;
			cout << "Polinom is:\n";
			cout << p;
			work_with_polinoms(p, s);
			break;
		case 3:
			cout << "Enter key:\n";
			cin >> s;
			erase(s);
			cout << "Done!\n";
			break;
		default:
			flag = false;
			break;
		}
	}
}
