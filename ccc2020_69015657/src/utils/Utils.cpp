#include "Utils.hpp"

std::vector<std::string> splitWithStl(const std::string &str,const std::string &pattern)
{
    std::vector<std::string> resVec;

	if (str.empty())
    {
        return resVec;
    }

    std::string strs = str + pattern;
    
    size_t pos = strs.find(pattern);
    size_t size = strs.size();

    while (pos != std::string::npos)
    {
        std::string x = strs.substr(0,pos);
        resVec.push_back(x);
        strs = strs.substr(pos+1,size);
        pos = strs.find(pattern);
    }
    
    return resVec;
}