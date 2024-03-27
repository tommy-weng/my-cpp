#include <iostream>
#include <boost/core/demangle.hpp>

template <typename T>
struct Tommy
{};

int main()
{
auto name = typeid(Tommy<int>).name();
std::cout << name << std::endl;
std::cout << boost::core::demangle(name) << std::endl;
}