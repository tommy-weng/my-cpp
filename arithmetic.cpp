#include<iostream>
#include<cstdlib>
using namespace std;

class Practice
{
    public:
        void get_number(void)
        {
            m_a = rand() % m_limit;
            m_b = rand() % m_limit;	
            return;
        }
        void get_result(void)	
        {

            while (!(cin >> m_input))
            {
                cout << "Error input! Try again please." << endl;
                cin.clear();
                char s[100];
                //cin.get();
                cin.getline(s, 100);	
            }

            if (m_input == m_result)
            {
                cout << "Congratulations! you got it." << endl;	
            }
            else
            {
                cout << "Sorry, it's not correct. The correct result is: " << m_result << endl;	
            }
            return;
        }
        void calculate(void)
        {
            m_curr_operator = m_operator[rand()%4];

            switch (m_curr_operator)
            {
                case '+':
                    {
                        m_result = m_a + m_b;
                        break;				
                    }
                case '-':
                    {
                        m_result = m_a - m_b;
                        break;	
                    }
                case '*':
                    {
                        m_result = m_a * m_b;
                        break;	
                    }
                case '/':
                    {
                        m_result = m_a / m_b;
                        break;	
                    }
                default:
                    {
                        break;
                    }
            }
            return;
        }
        void display(void)
        {
            cout << m_a << " "<< m_curr_operator << " "<< m_b << " = " << endl;	
            return;	
        }
        void do_it(void)
        {
            get_number();
            calculate();
            display();	
            get_result();
            return;
        }

    private:
        static const int m_limit = 100;
        static const char m_operator[];
        int m_a;
        int m_b;
        int m_result;
        int m_input;
        char m_curr_operator;
};

const char Practice::m_operator[] = {'+', '-', '*', '/'};

int main(void)
{
    Practice p;

    //srand(getpid());
    srand(time(0));
    for (int i = 0; i < 100; i++)
    {
        p.do_it();	
    }
    return 0;
}
