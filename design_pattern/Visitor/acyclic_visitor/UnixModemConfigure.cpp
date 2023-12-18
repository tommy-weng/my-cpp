#include <iostream>
#include "UnixModemConfigure.hpp"
#include "HayesModem.hpp"
#include "ZoomModem.hpp"

using std::cout;
using std::endl;

void UnixModemConfigure::visit(HayesModem& modem)
{
    if (modem.dial())
    {
        cout << "Configure HayesModem for Unix" << endl;
    }
}

void UnixModemConfigure::visit(ZoomModem& modem)
{
    if (modem.dial())
    {
        cout << "Configure ZoomModem for Unix" << endl;
    }
}