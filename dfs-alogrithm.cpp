#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>

using namespace std;

vector<string> split(const string s, const string &pattern)
{
    vector<string> scVec;

    if ("" == s)
    {
        return scVec;
    }

    string str = s + pattern;
    size_t strSize = str.size();
    size_t pattSize = pattern.size();
    for (size_t pos = str.find(pattern); pos != string::npos; pos = str.find(pattern))
    {
        string sub = str.substr(0, pos);
        scVec.push_back(sub);
        str = str.substr(pos + pattSize,strSize);
    }

    return scVec;
}

bool isEqual(map<char,int> record, string& sa, string& sb, string& sc)
{
    int a = 0;
    int b = 0;
    int c = 0;
    stringstream ssa;
    stringstream ssb;
    stringstream ssc;

    for (string::iterator it = sa.begin(); it != sa.end(); it++)
    {
        ssa << record[*it];
    }
    for (string::iterator it = sb.begin(); it != sb.end(); it++)
    {
        ssb << record[*it];
    }
    for (string::iterator it = sc.begin(); it != sc.end(); it++)
    {
        ssc << record[*it];
    }

    ssa >> a;
    ssb >> b;
    ssc >> c;

    if (a + b == c)
    {
        cout << a << " + " << b << " = " << c << endl;
        return true;
    }
    else
    {
        cout << a << " + " << b << " != " << c << endl;
        return false;
    }
}

void findEqual(string& sa, string& sb, string& sc)
{
    map<char, int> record;
    int count = 0;
    for (string::iterator it = sa.begin(); it != sa.end(); it++)
    {
        cout << *it << endl;
        record.insert(pair<char,int>(*it, count));
        count++;
    }
    for (string::iterator it = sb.begin(); it != sb.end(); it++)
    {
        cout << *it << endl;
        pair<map<char, int>::iterator, bool> ret;
        ret = record.insert(pair<char,int>(*it, count));
        if (false != ret.second)
        {
            count++;
        }
    }
    for (string::iterator it = sc.begin(); it != sc.end(); it++)
    {
        cout << *it << endl;
        pair<map<char, int>::iterator, bool> ret;
        ret = record.insert(pair<char,int>(*it, count));
        cout << ret.second << endl; 
        if (false != ret.second)
        {
            count++;
        }
    }

    for (map<char, int>::iterator it = record.begin(); it != record.end(); it++)
    {
        cout << it->first << " " <<  it->second << endl;
    }

    isEqual(record, sa,sb,sc);
}


int main()
{
    string input = "ACD * BA = CDBE";

    vector<string> v = split(input, " ");//{"abcd", "efeg"};

    string a = v[0];
    string b = v[2];
    string c = v[4];

    findEqual(a, b, c);
    
    return 0;
}
