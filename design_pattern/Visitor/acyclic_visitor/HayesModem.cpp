#include "HayesModem.hpp"
#include "HayesModemVisitor.hpp"
#include "ModemVisitor.hpp"

void HayesModem::accept(ModemVisitor& visitor)
{
    auto& hayesVisitor = dynamic_cast<HayesModemVisitor&>(visitor);
    hayesVisitor.visit(*this);
}

bool HayesModem::dial()
{
    return true;
}