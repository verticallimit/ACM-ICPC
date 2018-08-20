//计算PI小数点后第n位数是什么
#include <cstdio>
#include<iostream>
using namespace std;
typedef long long ll;

ll remain( ll m, ll n, ll k, ll extra)
{
    ll temp1=1,temp2=1;
    if(n==0)return extra%k;
    if(n==1)return (m*extra)%k;
    while(n>1)
    {
        temp1=m;
        temp1*=temp1;
        if(temp1>=k)temp1%=k;
        if(n%2==1)temp2=m*temp2;
        temp2%=k;
        m=temp1;
        n=n/2;
    }
    temp1=(temp1*temp2)%k;
    return (temp1*extra)%k;
}

 ll remain_nex( ll m, ll n, ll k)
{
     ll temp1=1,temp2=1;
    if(n==0)return 1;
    if(n==1)return m%k;
    while(n>1)
    {
        temp1=m;
        temp1*=temp1;
        if(temp1>=k)temp1%=k;
        if(n%2==1)temp2=m*temp2;
        temp2%=k;
        m=temp1;
        n=n/2;
    }
    return (temp1*temp2)%k;
}

char compute_n(int j){
     ll m;
    long double sum=0,temp=1.0,temp1;
    int i;
    j--;
    temp1=1.0;
    for(i=0;i<=j;i++)sum=sum+remain(16,j-i,8*i+1,4)/(long double)(8.0*i+1);
    for(i=0;i<=j;i++)sum=sum-remain(16,j-i,8*i+4,2)/(long double)(8.0*i+4);
    for(i=0;i<=j;i++)sum=sum-remain_nex(16,j-i,8*i+5)/(long double)(8.0*i+5);
    for(i=0;i<=j;i++)sum=sum-remain_nex(16,j-i,8*i+6)/(long double)(8.0*i+6);
    temp=1.0;
    for(;temp>0.000001;i++)
    {
        temp=temp/16.0;sum=sum+(4.0/(8*i+1)-2.0/(8*i+4)-1.0/(8*i+5)-1.0/(8*i+6))*temp;
    }
    for(;sum<0;)sum=sum+16;
    m=sum;
    sum=sum-m;
    sum=sum*16;
    m=sum;

    return (char)(m<10 ? m+48: m+55);
}

int main()
{
    int T, ca, i, n;
    scanf("%d", &T);
    for (ca = 1;ca <= T;ca++) {
        scanf("%d", &n);
        printf("Case #%d: %d %c\n", ca, n, compute_n(n));

    }
}
