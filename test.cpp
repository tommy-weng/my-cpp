#include <iostream>
#include "test.hpp"


using namespace std;

int *A::a = NULL;

int main()
{
   
    A* aa = new A();

    aa->print();   
hh
    delete aa; 
    return 0;
}

