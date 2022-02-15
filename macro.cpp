#include <iostream>
#include <stdio.h>

#define LOG(format, arg...) fprintf(stdout, format, ##arg)
#define TRACE(format, ...) fprintf(stdout, format, __VA_ARGS__)

// Refer to: https://www.cnblogs.com/devcjq/articles/2430700.html
// #: Replace x with string
// ##: Joint 2 tokens
#define TOKEN_9 9
#define PRINT(x) fprintf(stdout, "token_" #x " = %d\n",TOKEN_##x)

using namespace std;

int main()
{
    PRINT(9);

    LOG("log value = %d\n", 1);
    TRACE("trace value = %d\n", 2);

    return 0;
}   

