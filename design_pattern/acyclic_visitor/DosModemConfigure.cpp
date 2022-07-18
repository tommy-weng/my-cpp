#include <iostream>
#include "DosModemConfigure.hpp"
#include "HayesModem.hpp"
#include "ZoomModem.hpp"

using std::cout;
using std::endl;
void DosModemConfigure::visit(HayesModem& modem)
{
    if (modem.dial())
    {
        cout << "Configure HayesModem for Dos" << endl;
    }
}

void DosModemConfigure::visit(ZoomModem& modem)
{
    if (modem.dial())
    {
        cout << "Configure ZoomModem for Dos" << endl;
    }
}