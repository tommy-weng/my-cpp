#pragma once

#include <vector>
#include <array>
#include "../comm/City.hpp"
#include "../comm/Week.hpp"
#include "../comm/Pool.hpp"

using namespace std;

namespace io
{

class Io
{
public:
    using Cities = vector<array<comm::City, MAX_CITIES>>;
    using Weeks = vector<comm::Week>;
    using Pool = comm::Pool;

    Io(Cities& cities, Weeks& weeks, Pool& pool);
    ~Io();

    bool input(const char* file);
    void output();
private:
    void init();

    Cities& cities_;
    Weeks& weeks_;
    Pool& pool_;

};

}