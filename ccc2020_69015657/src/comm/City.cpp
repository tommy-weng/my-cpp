#include <cstring>
#include "City.hpp"

namespace comm
{

City::City()
{
    memset(&config_, 0, sizeof(config_));
    memset(&minFundsData_, 0, sizeof(minFundsData_));
    memset(&surgMaskData_, 0, sizeof(surgMaskData_));
    memset(&disinData_, 0, sizeof(disinData_));
    memset(&otherData_, 0, sizeof(otherData_));
    memset(&sumData_, 0, sizeof(sumData_));
}

City::~City()
{
}

}