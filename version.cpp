#include <iostream>

using std::cout;
using std::endl;

// void version()__attribute__((constructor));
// void version()
// {
//     cout << "Version <--" << __VERSION__ << "--> " << "Cplusplus <--" << __cplusplus << "-->" << endl;
// }

int main()
{
    cout << "Version <--" << __VERSION__ << "--> " << "Cplusplus <--" << __cplusplus << "-->" << endl;
    return 0;
}   

