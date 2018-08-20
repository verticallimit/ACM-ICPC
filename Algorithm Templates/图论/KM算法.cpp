/*
KM算法主要用于求解最大(小)权完美匹配问题、在求非2完美匹配时需要添加边从而使其转化为完美匹配、
KM算法还可以解形似二分图的不等式组、
KM算法还可以解形似二分图的不等式组、复杂度O（V^3）
二分图最大权匹配  复杂度O(nx*nx*ny)
若求最小权匹配，可将权值取相反数，结果取相反数
点的编号从0开始
*/
#include <bits/stdc++.h>
using namespace std;
const int N = 310;
const int INF =0x3f3f3f3f;
int nx, ny;//两边的点数
int g[N][N];
int linker[N], lx[N], ly[N];//y中各点匹配状态、x/y中的点标号
int slack[N];
bool visx[N], visy[N];
bool DFS(int x) {
    visx[x] = true;
    for (int y = 0; y < ny; y++) {
        if (visy[y])continue;
        int tmp = lx[x] + ly[y] - g[x][y];
        if (tmp == 0) {
            visy[y] = true;
            if (linker[y] == -1 || DFS(linker[y])) {
                linker[y] = x;
                return true;
            }
        }
        else if(slack[y] > tmp) slack[y] = tmp;
    }
    return false;
}
int KM() {
    memset(linker, -1, sizeof(linker));
    memset(ly, 0, sizeof(ly));
    for (int i = 0; i < nx; i++) {
        lx[i] = -INF;
        for (int j = 0; j < ny; j++)
            if (g[i][j] > lx[i])
                lx[i] = g[i][j];

    }
    for (int x = 0; x < nx; x++) {
        for (int i = 0; i < ny; i++)
            slack[i] = INF;
        while (true) {
            memset(visx, false, sizeof(visx));
            memset(visy, false, sizeof(visy));
            if (DFS(x)) break;
            int d = INF;
            for (int i = 0; i < ny; i++)
                if (!visy[i] && d > slack[i])
                    d = slack[i];
            for (int i = 0; i < nx; i++)
                if (visx[i]) lx[i] -= d;
            for (int i = 0; i < ny; i++) {
                if (visy[i]) ly[i] += d;
                else slack[i] -= d;
            }
        }
    }
    int res = 0;
    for (int i = 0; i < ny; i++)
        if (linker[i] != -1)
            res += g[linker[i]][i];
    return res;
}
int main() {
    int n;
    while(scanf("%d", &n) != EOF) {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                scanf("%d", &g[i][j]);
        nx = ny =n;
        printf("%d\n", KM());
    }
    return 0;
}

//速度更快的KM算法
#include <bits/stdc++.h>
using namespace std;
typedef int LL;
const int maxn = 310;
const LL INF = 0xfffffff;
int t, n;
LL w[maxn][maxn], match[maxn], sx[maxn], sy[maxn], slack[maxn], pre[maxn];
bool vis[maxn];
void augment(int rt) {
    int cur = 0;
    match[0] = rt;
    memset(vis, 0, (n + 1) * sizeof(bool));
    memset(slack, 0x3f, (n + 1) * sizeof(LL));
    do {
        int nxt, u = match[cur];
        LL dt = INF;
        vis[cur] = 1;
        for(int v = 1; v <= n; ++v) {
            if(vis[v])
                continue;
            LL tmp = sx[u] + sy[v] - w[u][v];
            if(slack[v] > tmp) {
                slack[v] = tmp;
                pre[v] = cur;
            }
            if(slack[v] < dt) {
                dt = slack[v];
                nxt = v;
            }
        }
        for(int v = 0; v <= n; ++v)
            if(vis[v]) {
                sx[match[v]] -= dt;
                sy[v] += dt;
            } else
                slack[v] -= dt;
        cur = nxt;
    } while(match[cur]);
    for(int v = cur; v; v = pre[v])
        match[v] = match[pre[v]];
}
LL KM() {
    for(int i = 1; i <= n; ++i) {
        LL dt = 0;
        for(int j = 1; j <= n; ++j)
            dt = max(dt, w[i][j]);
        sx[i] = dt;
        sy[i] = match[i] = 0;
    }
    for(int i = 1; i <= n; ++i)
        augment(i);
    LL cost = 0;
    for(int i = 1; i <= n; ++i)
        cost += sx[i] + sy[i];
    return cost;
}
int main() {
    while (scanf("%d", &n) != EOF) {
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= n; ++j) {
                scanf("%d", &w[i][j]);
            }
        printf("%d\n", KM());
    }
    return 0;
}
