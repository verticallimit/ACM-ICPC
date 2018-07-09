/*
快速数论变化(NTT)是的原理其实和快速傅里叶变换是一样的原理
可以在模p域进行NTT变换
可以解决特殊情况下FFT的浮点误差
 */
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <time.h>
using namespace std;
#define Mp(x,y) make_pair(x,y)
const int inf = 0x3fffffff;


typedef long long LL;
const int mmax  = 1<<18;
const int mod = (479<<21)+1;
const int g = 3;  //原根
LL quick_mod(LL a,LL b)
{
    LL ans=1;
    for(;b;b/=2)
    {
        if(b&1)
            ans=ans*a%mod;
        a=a*a%mod;
    }
    return ans;
}
int rev(int x,int r)  //蝴蝶操作
{
    int ans=0;
    for(int i=0; i<r; i++)
    {
        if(x&(1<<i))
        {
            ans+=1<<(r-i-1);
        }
    }
    return ans;
}
void NTT(int n,LL A[],int on) // 长度为N (2的次数)
{
    int r=0;
    for(;; r++)
    {
        if((1<<r)==n)
            break;
    }
    for(int i=0; i<n; i++)
    {
        int tmp=rev(i,r);
        if(i<tmp)
            swap(A[i],A[tmp]);
    }
    for(int s=1; s<=r; s++)
    {
        int m=1<<s;
        LL wn=quick_mod(g,(mod-1)/m);
        for(int k=0; k<n; k+=m)
        {
            LL  w=1;
            for(int j=0; j<m/2; j++)
            {
                LL t,u;
                t=w*(A[k+j+m/2]%mod)%mod;
                u=A[k+j]%mod;
                A[k+j]=(u+t)%mod;
                A[k+j+m/2]=((u-t)%mod+mod)%mod;
                w=w*wn%mod;
            }
        }
    }
    if(on==-1)
    {
        for(int i=1;i<n/2;i++)
            swap(A[i],A[n-i]);
        LL inv=quick_mod(n,mod-2);
        for(int i=0;i<n;i++)
            A[i]=A[i]%mod*inv%mod;
    }

}
LL A[mmax+10],B[mmax+10];
LL ans[mmax+10];


int main()
{
    int n,m;
    string s1;
    string s2;
    while(cin>>s1>>s2)
    {
        n=s1.size();
        m=s2.size();
        memset(A,0,sizeof A);
        memset(B,0,sizeof B);
        for(int i=n-1; i>=0 ; i--)
            A[i]=s1[n-i-1]-'0';
        for(int i=m-1; i>=0; i--)
            B[i]=s2[m-i-1]-'0';
        int tmp=1;
        while(tmp<max(n,m))
            tmp*=2;
        n=tmp;

        NTT(2*n,A,1);
        NTT(2*n,B,1);
        for(int i=0; i<2*n; i++)
            A[i]=A[i]*B[i]%mod;
        NTT(2*n,A,-1);
        memset(ans,0,sizeof ans);
        for(int i=0;i<2*n;i++)
        {
            ans[i]+=A[i];
            if(ans[i]>=10)
            {
                ans[i+1]+=ans[i]/10;
                ans[i]%=10;
            }
        }
        int e=0;
        for(int i=2*n-1;i>=0;i--)
        {
            if(ans[i])
            {
                e=i;
                break;
            }
        }
        for(int i=e;i>=0;i--)
        {
            printf("%lld",ans[i]);
        }
        printf("\n");
    }
}
