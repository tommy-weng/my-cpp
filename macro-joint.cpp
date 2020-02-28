#include <iostream>

#define FUN(x) tommy##x
#define PRINT(x) cout << "tommy"#x << endl;

using namespace std;

void tommy1()
{
    cout << "hi tommy" << endl;
}

int main()
{
    FUN(1)();
    PRINT(2);
    return 0;
}   

