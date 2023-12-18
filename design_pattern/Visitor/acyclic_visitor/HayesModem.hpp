#pragma once

#include "Modem.hpp"

class ModemVisitor;
class HayesModem: public Modem
{
public:
    void accept(ModemVisitor& visitor);
    bool dial();
};