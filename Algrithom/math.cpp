// https://blog.csdn.net/qq_39534332/article/details/91042320
// https://www.cnblogs.com/ccf19881030/p/12004812.html
// https://vimsky.com/examples/usage/isnormal-in-c.html

#include <iostream>
#include <cmath>
#include <cfloat>

using namespace std;

int main()
{
    cout << exp(1) << endl;
    cout << exp2(1) << endl;
    cout << exp10(1) << endl;
    cout << pow10(1) << endl;
    cout << pow(10, 1) << endl;

    cout << log(1) << endl;
    cout << log2(1) << endl;
    cout << log10(1) << endl;

    cout << round(1.4) << endl;
    cout << round(1.5) << endl;
    cout << ceil(1.1) << endl;
    cout << floor(1.9) << endl;

    cout << "isnan " << isnan(NAN) << endl; // is not a number
    cout << "isnan " << isnan(INFINITY) << endl;
    cout << "isnan " << isnan(INFINITY - INFINITY) << endl;
    cout << "isnan " << isnan(0.0 / 0.0) << endl;
    cout << "isnan " << isnan(1.0 / 0.0) << endl;

    cout << "isfinite " << isfinite(INFINITY) << endl;
    cout << "isfinite " << isfinite(0.0 / 0.0) << endl;
    cout << "isfinite " << isfinite(1.0 / 0.0) << endl;
    cout << "isinf " << isinf(INFINITY) << endl;
    cout << "isinf " << isinf(0.0 / 0.0) << endl;
    cout << "isinf " << isinf(1.0 / 0.0) << endl;

    cout << "isnormal " << isnormal(NAN) << endl;
    cout << "isnormal " << isnormal(INFINITY) << endl;
    cout << "isnormal " << isnormal(0.0 / 0.0) << endl;
    cout << "isnormal " << isnormal(1.0 / 0.0) << endl;
    cout << "isnormal " << isnormal(0.0) << endl;
    cout << "isnormal " << isnormal(1.0) << endl;

    cout << signbit(-1.2) << endl; // is negative
    cout << isgreater(1, 2) << endl;

    return 0;
}   

