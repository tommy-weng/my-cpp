#include <iostream>
#include <stdio.h>

#define LOG(format, arg...) fprintf(stdout, format, ##arg)
#define PAR(arg, ...) cout << arg << __VA_ARGS__ << endl;

#define FUN(x) tommy##x
#define PRINT(x) cout << "tommy"#x << endl;

using namespace std;

void tommy1()
{
    cout << "hi tommy" << endl;
}

int main()
{
    FILE* pf = NULL;

    pf = fopen("test.log", "a");

    //fputs("hello pf\n",pf);
    
    LOG("fdsafdsfsafdsf\n");
    return 0;
}   

