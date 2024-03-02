#include <iostream>

using namespace std;

enum class Weekday
{
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday
};

enum class Weekend
{
    Saturday,
    Sunday
};

int main()
{
    cout << static_cast<int>(Weekend::Saturday) << endl; 
    return 0;
}   

