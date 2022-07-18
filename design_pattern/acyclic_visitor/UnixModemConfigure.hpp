#pragma once

#include "ModemVisitor.hpp"
#include "HayesModemVisitor.hpp"
#include "ZoomModemVisitor.hpp"

class UnixModemConfigure : public ModemVisitor, public HayesModemVisitor, public ZoomModemVisitor
{
public:
    void visit(HayesModem& modem);
    void visit(ZoomModem& modem);
};