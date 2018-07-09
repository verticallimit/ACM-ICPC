#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

#define INF 0x3f3f3f3f
const int maxn = 105;
int mpt[maxn][maxn];
int n, m;

void floyd() {
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                mpt[i][j] = min(mpt[i][k] + mpt[k][j], mpt[i][j]);
            }
        }
    }
}

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        if (n + m == 0) break;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (i == j) mpt[i][j] = 0;
                else mpt[i][j] = INF;
            }
        }
        for (int i = 1; i <= m; i++) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            if (c < mpt[a][b]) {
                mpt[a][b] = c;
                mpt[b][a] = c;
            }
        }
        floyd();
        printf("%d\n",mpt[1][n]);
    }
    return 0;
}

//floyd求最小环
int Floyd_MinCircle() {
    int Mincircle = Mod;
    int i, j, k;
    for (k = 1; k <= n; k++) {
        for (i = 1; i <= n; i++) {
            for (j = 1; j <= n; j++) {
                if (dis[i][j] != Mod && mp[j][k] != Mod && mp[k][i] != Mod && dis[i][j] + mp[j][k] + mp[k][i] < Mincircle)
                    Mincircle = dis[i][j] + mp[j][k] + mp[k][i];
            }
        }
        //正常Floyd
        for (i = 1; i <= n; i++) {
            for (j = 1; j <= n; j++) {
                if (dis[i][k] != Mod && dis[k][j] != Mod && dis[i][k] + dis[k][j] < dis[i][j]) {
                    dis[i][j] = dis[i][k] + dis[k][j];
                    pre[i][j] = pre[k][j];
                }
            }
        }
    }
    return Mincircle;
}
