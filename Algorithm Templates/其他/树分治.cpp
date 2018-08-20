/*
给一棵边带权树，问两点之间的距离小于等于K的点对有多少个。
*/
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 1e4 + 10;
struct node {
    int v, l;
    node() {}
    node(int _v, int _l):v(_v),l(_l){};
};
vector<node> G[maxn];
// s数组存子节点数量 f数组存父节点的数量 d数组存到根节点的距离
int n, sz, s[maxn], f[maxn], root, d[maxn], K, ans;
vector<int> dep;//当前子树的各个节点深度、排序加速计算
bool done[maxn];//标记是否访问过

//以now节点为根节点重新构造树
void getroot(int now, int fa) {
    s[now] = 1;
    f[now] = 0;
    for (int i = 0; i < G[now].size(); i++) {
        int u = G[now][i].v;
        if (u != fa && !done[u]) {
            getroot(u, now);
            s[now] += s[u];
            f[now] = max(f[now], s[u]);
        }
    }
    f[now] = max(f[now], sz - s[now]);
    if (f[now] < f[root]) root = now;
}

//计算子树中所有点到根节点的距离
void getdep(int now, int fa) {
    dep.push_back(d[now]);
    s[now] = 1;
    for (int i = 0; i < G[now].size(); i++) {
        int u = G[now][i].v;
        if (u != fa && !done[u]) {
            d[u] = d[now] + G[now][i].l;
            getdep(u, now);
            s[now] += s[u];
        }
    }
}

//计算所求的结果
int calc(int now, int init) {
    dep.clear();
    d[now] = init;
    getdep(now, 0);
    sort(dep.begin(), dep.end());
    int ret = 0;
    for (int l = 0, r = dep.size() - 1; l < r;) {
        if (dep[l] + dep[r] <= K) {ret += (r - l); l++;}
        else r--;
    }
    return ret;
}

void solve(int now) {
    ans += calc(now, 0);
    done[now] = true; //将每次分治的根节点标记防止重复走
    for (int  i = 0; i < G[now].size(); i++) {
        int u = G[now][i].v;
        if (!done[u]) {
            ans -= calc(u, G[now][i].l); //减去两个点位于同一个子树中的情况
            f[0] = sz = s[u];
            getroot(u, root = 0); //分治的时候每次都找树的重心、避免退化
            solve(root);
        }
    }
}

int main() {
    while (scanf("%d%d", &n, &K) == 2) {
        if (n == 0 && K == 0) break;
        for (int i = 0; i <= n; i++) G[i].clear();
        memset(done, false, sizeof(done));
        int u, v, l;
        for (int i = 1; i < n; i++) {
            scanf("%d%d%d", &u, &v, &l);
            G[u].push_back(node(v, l));
            G[v].push_back(node(u, l));
        }
        f[0] = sz = n;
        getroot(1, root = 0);
        ans = 0;
        solve(root);
        printf("%d\n", ans);
    }
    return 0;
}
