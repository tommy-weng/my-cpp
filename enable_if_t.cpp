#include <iostream>

using std::cout;
using std::endl;
//using std::enable_if_t;

template< bool B, class T = void >
using enable_if_t = typename std::enable_if<B,T>::type;

template <size_t n = 0>
enable_if_t<n == 1, void> fun()
{
    cout << "Is tommy" << endl;
}

template <size_t n = 0>
enable_if_t<n == 0, void> fun()
{
    cout << "Not tommy" << endl;
}


template <typename Tp, typename Up>
constexpr typename std::enable_if<std::__is_integer<Tp>::__value == std::__is_integer<Up>::__value, typename __gnu_cxx::__promote_2<Tp, Up>::__type>::type add(Tp a, Up b)
{
    return a + b;
}

int main()
{
    fun();
    fun<1>();
    cout << add(1, 2) << endl;

    return 0;
}   

