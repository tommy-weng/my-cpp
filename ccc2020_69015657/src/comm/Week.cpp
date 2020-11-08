#include "Week.hpp"

namespace comm
{

Week::Week()
:smPoolR_(0),
disPoolR_(0),
sumOfMaxR_(0),
sumOfSmIdealSharedR_(0),
sumOfDisIdealSharedR_(0),
sumOfDisSharedR_(0),
sumOfLoadFactor_(0)
{
}

Week::~Week()
{
}
}