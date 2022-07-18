#pragma once

#include "Modem.hpp"

class ModemVisitor;
class ZoomModem: public Modem
{
public:
    void accept(ModemVisitor& visitor);
    bool dial();
};