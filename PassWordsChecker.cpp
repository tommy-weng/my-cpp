#include <iostream>
#include <vector>
#include <string>
#include <bitset>

using std::cout;
using std::endl;

class Checker
{
public:
    bool verify(const std::string& passwd)
    {
        len = passwd.size();

        return checkLength(passwd) and not isDuplication(passwd) and not isContinuous(passwd);
    }

private:
    bool isDuplication(const std::string& passwd)
    {
        for (size_t i = 0; i < len - 3; i++)
        {
            std::string token{passwd, i, 3};
            for (size_t j = i + 3; j < len; j++)
            {
                if (std::string::npos != passwd.find(token, j))
                {
                    return true;
                }
            }
        }
        return false;
    }

    bool isContinuous(const std::string& passwd)
    {
        std::string token{};
        for (int i = 0; i < len - 4; i++)
        {
            if (not isdigit(passwd.at(i)))
            {
                token.clear();
                continue;
            }
            for (int j = i; j < i + 4; j++)
            {
                if (not isdigit(passwd.at(j)))
                {
                    token.clear();
                    break;
                }
                token.push_back(passwd.at(j));
            }

            if (not token.empty())
            {
                auto diff1 = abs(token.at(1) - token.at(0));
                auto diff2 = abs(token.at(2) - token.at(1));
                auto diff3 = abs(token.at(3) - token.at(2));
                if (1 == diff1 and 1 == diff2 and 1 == diff3)
                {
                    return true;
                }
                token.clear();
            }
        }
        return false;
    }

    bool checkLength(const std::string& passwd)
    {
        for (auto& i: passwd)
        {
            if (isupper(i))
            {
                bits.set(0);
            }
            else if (islower(i))
            {
                bits.set(1);
            }
            else if (isdigit(i))
            {
                bits.set(2);
            }
            else
            {
                bits.set(3);
            }
        }
        if (4 == getCount())
        {
            return len >= 6;
        }
        else if (3 == getCount())
        {
            return len >= 8;
        }
        else
        {
            return len >= 10;
        }
    }

    int getCount()
    {
        return bits.count();
    }

    int len{0};
    std::bitset<4> bits{};
};

int main()
{
    std::vector<std::string> input{
        "120XYc4000%",
        "120HWcc&9HWcc",
        "120ABCc888888",
        "74123450000",
        "120$bc80X00",
        "12304560987"
    };

    Checker checker{};
    for (auto& passwd: input)
    {
        std::string output = checker.verify(passwd) ? "OK" : "NG";
        cout << output << endl;
    }

    return 0;
}   
