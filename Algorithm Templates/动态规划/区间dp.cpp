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
