#include <iostream>

using std::cout;
using std::endl;

template<class Tp, Tp v>
struct my_integral
{
    static constexpr Tp value = v;
    using value_type = Tp;
    using type = my_integral<Tp, v>;
    constexpr operator value_type() const noexcept { return value; }
    constexpr value_type operator()() const noexcept { return value; }
};

struct true_type: my_integral<bool, true>{};
struct false_type: my_integral<bool, false>{};

template<class, class>
struct is_same: false_type{};

template<class Tp>
struct is_same<Tp, Tp> : true_type{};

template<class Tp, class Up>
constexpr bool is_same_v = is_same<Tp, Up>::value;

int main()
{
    is_same<int, double> obj;
    cout << obj() << endl; // bracket() overload
    cout << is_same<int, double>() << endl; // type force convert operator overload

    // cout << std::is_same_v<int, int> << endl;
    cout << is_same<int, int>() << endl;
    cout << is_same_v<int, int> << endl;
    

    return 0;
}   

