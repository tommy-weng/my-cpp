#include <iostream>

using namespace std;

struct S
{
	int a;
};

template <typename T, typename U>
class A
{
	public:
		A():m_a(99){};
		void show()
		{
			cout << m_a << endl;	
		}
	private:
		T m_a;
};

S s;

template <typename T>
class A<T, int>
{
	public:
		A():m_a(s){};
		void show()
		{
			cout << m_a.a << endl;	
		}

	private:
		S &m_a;
};

int main(void)
{
	A<int, S> aa;
	aa.show();
	return 0;
}
