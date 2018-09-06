#include <iostream>
#include <string>
using namespace std;

string min_str(string str1,string str2)
{
    if(str1.size() == str2.size() )
    {
        return min(str1,str2);
    }
    return str1.size() > str2.size() ? str2:str1;
}

bool is_subset(bool str1[26],bool str2[26])
{
    for(int i = 0; i < 26; ++i)
    {
        if(str2[i] && !str1[i])
        {
            return false;
        }
    }
    return true;
}

string Find_str(string S, string D) // 字符串S，字符集合D
{
    string ret;
    int Sset[26], Dset[26]; // int数组模拟集合，还有引用计数
    int Ds; // 字符集合D在字符串S中出现的不同个数
    fill(Dset,Dset+26,0);
    fill(Sset,Sset+26,0);
    Ds = 0;
    for (int i = 0; i < D.length(); i ++)
        Dset[D[i]-'a'] = 1; // 字符集合D初始化
    int l = 0;
    for (int r = 0; r < S.length(); r ++)
    {
        if (Dset[S[r]-'a'] == 1 && Sset[S[r]-'a'] == 0)
            Ds ++; // S中出现新的D集合中字符
        Sset[S[r]-'a'] ++;
        for (; l <= r; l ++)
        {
            if (Dset[S[l]-'a'] == 1 && Sset[S[l]-'a'] == 1)
            {
                if (Ds == D.length())   // D集合中字符全部出现
                {
                    ret = ret.empty() ? S.substr(l, r-l+1) : min_str(ret, S.substr(l, r-l+1));
                    Sset[S[l++]-'a'] --; // left右移
                    Ds --;
                }
                break;
            }
            Sset[S[l]-'a'] --;
        }
    }
    return ret;
}

int main()
{
    string str1,str2;
    str1 = "ssssssadf";
    str2 = "af";
    cout<<Find_str(str1,str2)<<endl;
    return 0;
}
