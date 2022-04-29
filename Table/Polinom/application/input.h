#pragma once
#include<string>
#include"..\\List\list.h"
#include"..//Polinoms/polinom.h"

double getnumber(std::string s, int& index);
void check_monom(std::string& s, int& index);
void correct(std::string&);
list<monom> parcer(std::string);
