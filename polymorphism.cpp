#include <iostream>

using namespace std;

class Fruit
{
	public:

	virtual void color(void)
	{
		cout << "I don't know what color it is!" << endl;	
	}
	
	void effect(void)
	{
		cout << "Benefit for health." << endl;	
	}
};

class Apple: public Fruit
{
	public:
	void color(void)
	{
		cout << "Red" << endl;	
	}
};

class Banana: public Fruit
{
	public:
	void color(void)
	{
		cout << "Yellow" << endl;
	}
};

class Grape: public Fruit
{
	public:

};

int main(void)
{
	Fruit *fruit[3];

	fruit[0] = new Apple();
	fruit[1] = new Banana();
	fruit[2] = new Grape();
	
	for (int i = 0; i < 3; i++)
	{
		fruit[i]->color();
		fruit[i]->effect();
	}

	return 0;
}
