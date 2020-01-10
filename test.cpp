#include <iostream>
#include <ostream>
#include <fstream>
#include "MyUtils.hpp"

using namespace std;


class OutPut: public fstream
{
    
};

int main()
{
//    iostream oo;
    OutPut op;
    op.open("test.log", ios::app);
    op.close();
    u32 a = 0xF0000000;
    u32 b = 0x2; 
    op << hex << (u32)a * (u64)b << endl; 
    return 0;
}   

