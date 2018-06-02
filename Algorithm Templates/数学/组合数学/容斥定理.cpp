// 错排问题
#include<iostream>
#include<stdio.h>
#include<string.h>
using namespace std;
long long int a[25];
long long int num[25][25];
void solve()
{
    memset(num,1,sizeof(num));
    a[1]=0;
    a[2]=1;
    a[3]=2;
    num[3][0]=1,num[3][1]=3,num[3][2]=3,num[3][3]=1;
    long long int sum=6;
    for(int i=4; i<=20; i++)
    {
        sum*=i;///当前的阶乘
        a[i]=sum;
        for(int j=1; j<i; j++)///减去1~i-1个全部放错，就是说i-1~1个放对的，（这里i也可以从2开始，因为a[1]=0,不过这样好理解）
        {
            num[i][j]=num[i-1][j]+num[i-1][j-1];
            a[i]=a[i]-a[j]*num[i][j];
        }
        a[i]-=1;///减去i个全部放对的
        num[i][1]=i;
        num[i][i]=1;
    }
}
int main()
{
    int n;
    solve();
    while(~scanf("%d",&n))
    {
        printf("%lld\n",a[n]);
    }
    return 0;
}
