#pragma once

class ZoomModem;
class ZoomModemVisitor
{
public:
    virtual void visit(ZoomModem& modem) = 0;
};