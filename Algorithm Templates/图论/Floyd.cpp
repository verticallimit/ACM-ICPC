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
