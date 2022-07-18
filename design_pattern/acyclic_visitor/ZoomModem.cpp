#include "ZoomModem.hpp"
#include "ZoomModemVisitor.hpp"
#include "ModemVisitor.hpp"

void ZoomModem::accept(ModemVisitor& visitor)
{
    auto& zoomModemVisitor = dynamic_cast<ZoomModemVisitor&>(visitor);
    zoomModemVisitor.visit(*this);
}

bool ZoomModem::dial()
{
    return true;
}