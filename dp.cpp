//  c = 8 , m = 4
// 
//  i   1   2   3   4
//  w   2   3   4   5
//  v   3   4   5   6    
//
//  dp[i][j] = max(dp[i-1][j], dp[i-1][j-w[i]])

#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> dp;
vector<int> w;
vector<int> v;

void init(int capacity, int num)
{
    for (uint i = 0; i <= num; i++)
    {
        vector<int> row(capacity + 1, 0);
        dp.push_back(row);
        w.push_back(i + 1);
        v.push_back(i + 2);
    }
}

int main()
{
    int c = 8;
    int n = 4;

    init(c, n);

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= c; j++)
        {
            if (j >= w.at(i))
            {
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - w[i]] + v[i]);
                //cout << i << " " << j << " " << dp[i][j] << endl;
            }
            else
            {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    cout << dp[4][8] << endl;
    return 0;
}