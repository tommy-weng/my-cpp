#include "UnixModemConfigure.hpp"
#include "DosModemConfigure.hpp"
#include "HayesModem.hpp"
#include "ZoomModem.hpp"

int main()
{
    UnixModemConfigure unixModemConfigure{};
    DosModemConfigure dosModemConfigure{};
    HayesModem hayes{};
    ZoomModem zoom{};

    hayes.accept(unixModemConfigure);
    zoom.accept(unixModemConfigure);
    hayes.accept(dosModemConfigure);
    zoom.accept(dosModemConfigure);

    return 0;
}