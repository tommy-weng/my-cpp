#include <iostream>

using namespace std;

class B
{
public:
    virtual void base()
    {
        cout << "In base: " << valB << endl;
    }
private:
    int valB{1};
};

class D : public B
{
public:
    void derived()
    {
        cout << "In derived: " << valD << endl;
    }
private:
    int valD{2};
};

void static_c(B* pb)
{
    D* pd1 = static_cast<D*>(pb); //dangerous
    if (pd1)
    {
        pd1->derived();
    }
    else
    {
        cout << "null ptr" << endl;
    }
}

void dynamic_c(B* pb)
{
    D* pd2 = dynamic_cast<D*>(pb);
    if (pd2)
    {
        pd2->derived();
    }
    else
    {
        cout << "null ptr" << endl;
    }
}

void foo(B* pb)
{
    static_c(pb);
    dynamic_c(pb);
}

int main()
{
    foo(new B{});
    foo(new D{});

    return 0;
}   

