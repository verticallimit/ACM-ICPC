// 求对于区间[1，b]内的整数x和[1,d]内的y，满足gcd(x,y)=k的数对的个数。

#include<iostream>
#include<cstdio>
#include<climits>
#include<algorithm>
#include<cstring>
using namespace std;
const int maxn=100005;
int T,a,b,c,d,e,tot;
long long ans1,ans2;
bool is[maxn];
int pri[maxn],miu[maxn];
void init(){//首先把莫比乌斯函数筛出来
    miu[1]=1;
    for(int i=2;i<=100000;i++){
        if(!is[i]){pri[++tot]=i;miu[i]=-1;}
        for(int j=1;j<=tot;j++){
            int k=pri[j]*i;if(k>100000)break;
            is[k]=1;
            if(i%pri[j]==0){miu[k]=0;break;}
            else miu[k]=-miu[i];
        }
    }
}
int main()
{
    int i,j,cnt=0;
    init();
    scanf("%d",&T);
    while(T--){
        cnt++;ans1=ans2=0;
        scanf("%d%d%d%d%d",&a,&b,&c,&d,&e);
        if(!e){ printf("Case %d: 0\n",cnt);continue;}
        b/=e;d/=e;//如果gcd(x,y)=1,那么gcd(x*e,y*e)=e;
        if(b>d)swap(b,d);
        for(i=1;i<=b;i++)ans1+=(long long)miu[i]*(b/i)*(d/i);
        for(i=1;i<=b;i++)ans2+=(long long)miu[i]*(b/i)*(b/i);
        printf("Case %d: %lld\n",cnt,ans1-ans2/2);
    }
    return 0;
}
