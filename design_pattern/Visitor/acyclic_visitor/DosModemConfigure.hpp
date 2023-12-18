#pragma once

#include "HayesModemVisitor.hpp"
#include "ZoomModemVisitor.hpp"
#include "ModemVisitor.hpp"

class DosModemConfigure: public ModemVisitor,public HayesModemVisitor, public ZoomModemVisitor
{
public:
    void visit(HayesModem& modem);
    void visit(ZoomModem& modem);
};