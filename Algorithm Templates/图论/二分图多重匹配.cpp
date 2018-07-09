#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

const int maxn = 100000 + 10;
const int maxm = 10 + 5;
int uN, vN;
int g[maxn][maxm];
int linker[maxm][maxn];
bool used[maxm];
int num[maxm];//右边最大的匹配数
int ans;
bool dfs(int u) {
    for (int v = 1; v <= vN; v++) {
        if (g[u][v] && !used[v]) {
            used[v] = true;
            if (linker[v][0] < num[v]) {
                linker[v][++linker[v][0]] = u;
                return true;
            }
            for (int i = 1; i <= num[v]; i++) {
                if (dfs(linker[v][i])) {
                    linker[v][i] = u;
                    return true;
                }
            }
        }
    }
    return false;
}
void hungary() {
    int res = 0;
    for (int i = 1; i <= vN; i++) {
        linker[i][0] = 0;
    }
    for (int u = 1; u <= uN; u++) {
        memset(used, false, sizeof(used));
        if (dfs(u)) res++;
        else {
            ans = 1;break;
        }
    }
    //return res;
}

int main() {
    while(scanf("%d%d", &uN, &vN) != EOF) {
        for (int i = 1; i <= uN; i++) {
            for (int j = 1; j <= vN; j++) {
                scanf("%d", &g[i][j]);
            }
        }
        for (int i = 1; i <= vN; i++) scanf("%d", &num[i]);
        ans = 0;
        hungary();
        if (ans == 0) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}
