#pragma once

class ModemVisitor;
class Modem
{
public:
    virtual void accept(ModemVisitor& visitor) = 0;
    virtual bool dial() = 0;
};