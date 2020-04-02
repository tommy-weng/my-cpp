#include <iostream>
#include "hello.hpp"

using namespace std;


void test(int &b)
{
	cout << "In test: " << b << endl;
}

void print_h(int &a)
{
	cout << "Hello T_T" << endl;
	cout << "parameter:a = " << a << endl;
	test(a);
}

