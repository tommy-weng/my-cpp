#include <iostream>
#include "total/TotalFunds.hpp"
#include "logger/Logger.hpp"

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        cout << "Argements not enough." << endl;
        return 1;
    }

    const char* inputFile = argv[1];

    total::TotalFunds totalFunds;
    totalFunds.calcTotalFunds(inputFile);
    totalFunds.show();
    return 0;
}
