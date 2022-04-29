#include"monom.h"

bool check_power(int a, int b)
{
	return a / 100 + b / 100 < 10 && a / 10 % 10 + b / 10 % 10 < 10 && a % 10 + b % 10 < 10;
}
