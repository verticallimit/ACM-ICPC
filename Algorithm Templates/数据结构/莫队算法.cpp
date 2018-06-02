// 莫队算法，一个优雅的暴力，可以解决一类静态，离线区间查询问题。
// 普通莫队，离线+区间分块，复杂度O(n*sqrt(n))
// 带修改的莫队也叫可持久化莫队，复杂度O(n^(5/3))
// 引入一个修改时间表示询问是发生在前time个修改操作后的

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

const int MAXN = 50010;
const int MAXM = 50010;
struct Query
{
    int L,R,id;
}node[MAXM];
long long gcd(long long a,long long b)
{
    if(b == 0)return a;
    return gcd(b,a%b);
}
struct Ans
{
    long long a,b;//分数a/b
    void reduce()//分数化简
    {
        long long d = gcd(a,b);
        a /= d; b /= d;
    }
}ans[MAXM];
int a[MAXN];
int num[MAXN];
int n,m,unit;
bool cmp(Query a,Query b)
{
    if(a.L/unit != b.L/unit)return a.L/unit < b.L/unit;
    else return a.R < b.R;
}
void work()
{
    long long temp = 0;
    memset(num,0,sizeof(num));
    int L = 1;
    int R = 0;
    for(int i = 0;i < m;i++)
    {
        while(R < node[i].R)
        {
            R++;
            temp -= (long long)num[a[R]]*num[a[R]];
            num[a[R]]++;
            temp += (long long)num[a[R]]*num[a[R]];
        }
        while(R > node[i].R)
        {
            temp -= (long long)num[a[R]]*num[a[R]];
            num[a[R]]--;
            temp += (long long)num[a[R]]*num[a[R]];
            R--;
        }
        while(L < node[i].L)
        {
            temp -= (long long)num[a[L]]*num[a[L]];
            num[a[L]]--;
            temp += (long long)num[a[L]]*num[a[L]];
            L++;
        }
        while(L > node[i].L)
        {
            L--;
            temp -= (long long)num[a[L]]*num[a[L]];
            num[a[L]]++;
            temp += (long long)num[a[L]]*num[a[L]];
        }
        ans[node[i].id].a = temp - (R-L+1);
        ans[node[i].id].b = (long long)(R-L+1)*(R-L);
        ans[node[i].id].reduce();
    }
}


int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(scanf("%d%d",&n,&m) == 2)
    {
        for(int i = 1;i <= n;i++)
            scanf("%d",&a[i]);
        for(int i = 0;i < m;i++)
        {
            node[i].id = i;
            scanf("%d%d",&node[i].L,&node[i].R);
        }
        unit = (int)sqrt(n);
        sort(node,node+m,cmp);
        work();
        for(int i = 0;i < m;i++)
            printf("%lld/%lld\n",ans[i].a,ans[i].b);
    }
    return 0;
}
