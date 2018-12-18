#include <iostream>

typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;

using namespace std;
u32 getRsNum(u32 subframe, u32 pdcchNum, u32 portNum)
{
	u32 rsNum = 0;
	if (4 == portNum)
	{
		if (1 == subframe)
		{
			if (1 == pdcchNum)
			{
				rsNum = 48;	
			}
			else if (2 == pdcchNum)
			{
				rsNum = 36;	
			}
		}
		else
		{
			if (1 == pdcchNum)
			{
				rsNum = 60;	
			}
			else if (2 == pdcchNum)
			{
				rsNum = 48;	
			}
			else if (3 == pdcchNum)
			{
				rsNum = 48;	
			}
		}
	
	}
	else if (2 == portNum)
	{
		if (1 == subframe)
		{
			rsNum = 24;	
		}
		else
		{
			rsNum = 36;	
		}
	}
	else if (1 == portNum)
	{
		if (1 == subframe)
		{
			rsNum = 12;	
		}
		else
		{
			rsNum = 18;	
		}
	}
	return rsNum;
}

void fun(u32 subframe, u32 pdcchNum, u32 portNum)
{
	u32 carrierNum = 12 * 3;
	u32 rsNum = getRsNum(subframe, pdcchNum, portNum);
	u32 symbolNum =  10 - pdcchNum;
	if (1 != subframe)
	{
		symbolNum =  14 - pdcchNum;
	}

	cout << "{";
	for (u32 i = 0; i < 17; i++)
	{
		u32 reNumPerRbg = symbolNum  * carrierNum - rsNum;
		if (7 == i)
		{
			if (0 == subframe)
			{
				u32 compensate = 4;
				if (1 ==  portNum)
				{
					compensate = 4;	
				}
				else if (2 == portNum)
				{
					compensate = 8;	
				}
				else
				{
					compensate = 16;	
				}

				reNumPerRbg = reNumPerRbg - 24 * 5 + compensate;	
			}
			else if ((1 == subframe) || (5 == subframe))
			{
				reNumPerRbg -= 24;			
			}
		}
		else if (8 == i)
		{
			if (0 == subframe)
			{
				u32 compensate = 6;
				if (1 ==  portNum)
				{
					compensate = 6;	
				}
				else if (2 == portNum)
				{
					compensate = 12;	
				}
				else
				{
					compensate = 24;	
				}

				reNumPerRbg = reNumPerRbg - 36 * 5 + compensate;
			}
			else if ((1 == subframe) || (5 == subframe))
			{
				reNumPerRbg -= 36;	
			}
		}
		else if (9 == i)
		{
			if (0 == subframe)
			{
				u32 compensate = 2;
				if (1 ==  portNum)
				{
					compensate = 2;	
				}
				else if (2 == portNum)
				{
					compensate = 4;	
				}
				else
				{
					compensate = 8;	
				}

				reNumPerRbg = reNumPerRbg - 12 * 5 + compensate;
			}
			else if ((1 == subframe) || (5 == subframe))
			{
				reNumPerRbg -= 12;	
			}
		}
		else if (16 == i)
		{
			reNumPerRbg = reNumPerRbg * 2 / 3; 	
		}

		cout << reNumPerRbg;
		if (16 != i)
		{
			cout << ", ";
		}
	}
	cout << "}" << endl;

	return;
}

void getReNum()
{

}

int main(void)
{
	u32 subframe = 2;
	u32 pdcchNum = 3;
	u32 portNum = 1;
	fun(subframe, pdcchNum, portNum);
	portNum = 2;
	fun(subframe, pdcchNum, portNum);
	portNum = 4;
	fun(subframe, pdcchNum, portNum);
	return 0;
}
