#include <iostream>
#include <cmath>

using std::cout;
using std::endl;

struct HumanReadable
{
    uintmax_t size{};
private:
    friend std::ostream& operator<<(std::ostream& o, HumanReadable&& hr)
    {
        double mantissa = hr.size;
        uint32_t i{0};
        for (; mantissa > 1024.; mantissa/=1024., i++);
        mantissa = std::ceil(mantissa * 10) / 10;
        o << mantissa << "BKMGTPE"[i];
        
        return i == 0 ? o : o << "B (" << hr.size << "B)";
    }
};

int main()
{
    cout << HumanReadable{5000} << endl;
    return 0;
}   

