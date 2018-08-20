/*
POJ 1185 炮兵阵地
*/
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

int state[70];
int num[70];
int cnt;
int dp[2][70][70];
int calc(int x) { //计算x的二进制中1的个数
    int ret = 0;
    while (x) {
        if (x & 1) ret++;
        x >>= 1;
    }
    return ret;
}
void init() {
    cnt = 0;
    for (int i = 0; i < (1 << 10); i++) {
        if ((i & (i << 1)) == 0 && (i & (i << 2)) == 0 \
        && (i&(i >> 1)) == 0 && (i&(i >> 2)) == 0) {
            num[cnt] = calc(i);
            state[cnt++] = i;
        }
    }
}
int a[110];
char str[110][20];
int main() {
    init();
    int n, m;
    while (scanf("%d%d", &n, &m) == 2) {
        for (int i = 0; i < n; i++) {
            scanf("%s", &str[i]);
            a[i] = 0;
            for (int j = 0; j < m; j++) {
                a[i] <<= 1;
                if (str[i][j] == 'H') a[i] |= 1;
            }
        }
        memset(dp, -1, sizeof(dp));
        int now = 0;
        dp[now][0][0] = 0;
        int tot = (1 << m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < cnt && state[j] < tot; j++)
                for (int k = 0; k < cnt && state[k] < tot; k++) {
                    if (dp[now][j][k] != -1) {
                        for (int x = 0; x < cnt && state[x] < tot; x++)
                            if ((state[x]&a[i]) == 0 && (state[x]&state[j]) == 0 && \
                                (state[x]&state[k]) == 0)
                                dp[now^1][k][x] = max(dp[now^1][k][x], dp[now][j][k] + num[x]);
                    }
                }
            now ^= 1;
        }
        int ans = 0;
        for (int i = 0; i < cnt && state[i] < tot; i++)
            for (int j = 0; j < cnt && state[j] < tot; j++)
                ans = max(ans, dp[now][i][j]);
        printf("%d\n", ans);
    }
    return 0;
}
