#include"interface.h"

using namespace std;

void get_polinom(polinom& p)
{
	bool flag = true;

	while (flag)
	{
		flag = false;
		try
		{
			string s;
			cin >> s;
			p = s;
		}
		catch (std::exception e)
		{
			flag = true;
			cout << e.what() << '\n';
			cout << "try enter polinom again\n";
		}
	}
}

void interface()
{
	
	cout << "Enter polinom:\n";

	polinom first, second, result;
	get_polinom(first);

	cout << "You enter: " << first << '\n';

	bool flag = true;
	while (flag)
	{
		flag = false;
		cout << "\nChoose digit for operation to do\n";
		cout << "1. Add polinoms\n";
		cout << "2. Subtract polinoms\n";
		cout << "3. Multiply polinom on number\n";
		cout << "4. Multiply polinoms\n";

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
			cout << "Enter second polinom:\n";
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
		default:
			flag = true;
			cout << "Wrong number, try again\n";
			break;
		}
	}

	cout << "Result is:\n";
	cout << result;
}