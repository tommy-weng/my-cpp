#pragma once

class HayesModem;
class HayesModemVisitor
{
public:
    virtual void visit(HayesModem& modem) = 0;
};