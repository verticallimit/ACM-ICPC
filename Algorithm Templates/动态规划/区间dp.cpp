// 定义
// 区间DP，顾名思义就是在区间上DP，它的主要思想就是先在小区间进行DP得到最优解
// 然后再利用小区间的最优解合并求大区间的最优解

//memset(dp, 0); 初始化DP数组
for (itn i = 1; i <= n; i++) {
    dp[i][i] = 初始值
}
for (itn len = 2; len <= n; len++)  //区间长度
for (int i = 1; i <= n; i++) {      //枚举起点
    int j = i + len - 1;            //区间终点
    if (j > n) break;               //越界结束
    for (int k = i; k < j; k++) {   //枚举分割点，构造状态转移方程
        dp[i][j] = max(dp[i][j], dp[i][k] + dp[k + 1][j] + w[i][j]);
    }
}
题目大意：n堆石子围成一圈，每堆石子的块数已知，
每次可以将相邻的两堆合并到一堆，块数变为两堆之和，
代价也为两堆石子块数之和。求合并到一堆的最小代价。
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int INF=1<<30;
const int N=1005;

int n;
int dp[N<<1][N<<1];
int s[N<<1][N<<1];
int sum[N<<1];
int a[N<<1];

void init()
{
    sum[0]=0;
    for(int i=1;i<=n;++i){
        scanf("%d",a+i);
        sum[i]=a[i]+sum[i-1];
    }
    for(int i=1;i<n;++i){
        a[n+i]=a[i];
        sum[n+i]=a[n+i]+sum[n+i-1];
    }
}

void solve()
{
    for(int l=1;l<=n;++l){
        for(int i=0;i+l-1<2*n;++i){
            int j=i+l-1;
            if(l==1){
                dp[i][i]=0;
                s[i][i]=i;
            }else{
                dp[i][j]=INF;
                for(int k=s[i][j-1];k<=s[i+1][j];++k){
                    if(dp[i][j]>dp[i][k]+dp[k+1][j]+sum[j]-sum[i-1]){
                        dp[i][j]=dp[i][k]+dp[k+1][j]+sum[j]-sum[i-1];
                        s[i][j]=k;
                    }
                }
            }
        }
    }
    int ans=INF;
    for(int i=1;i<=n;++i)
        ans=min(ans,dp[i][n+i-1]);
    printf("%d\n",ans);
}

int main()
{
    while(~scanf("%d",&n))
    {
        init();
        solve();
    }
    return 0;
}
