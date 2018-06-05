/*
spfa + A* 求K短路
*/
#include <stdio.h>
#include <queue>
#include <vector>
#include <string.h>
#include <algorithm>
using namespace std;

#define INF 0x3f3f3f3f
const int maxn = 1005;
int n, m;
int dist[maxn]; // 存放起点到i点的最短距离
int vis[maxn]; // 标记是否访问过
int p[maxn]; // 存放路径

struct Edge{
    int u, v, w;
    Edge(int u, int v, int w):u(u),v(v),w(w) {}
};

struct node {
    int v;
    int g, f;
    node(int v, int g, int f):v(v),g(g),f(f) {}
    bool operator < (const node &t) const {
        if (t.f == f) return t.g < g;
        return t.f < f;
    }
};

vector<Edge> edges;
vector<Edge> revedges;
vector<int> G[maxn];
vector<int> RG[maxn];

queue<int> q;
void spfa(int s) {
    while (!q.empty()) q.pop();
    for (int i = 0; i <= n; i++) dist[i] = INF;
    dist[s] = 0;
    memset(vis, 0, sizeof(vis));
    q.push(s);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        vis[u] = 0;
        for (int i = 0; i < G[u].size(); i++) {
            Edge& e = edges[G[u][i]];
            if (dist[e.v] > dist[u] + e.w) {
                dist[e.v] = dist[u] + e.w;
                p[e.v] = G[u][i];
                if (!vis[e.v]) {
                    vis[e.v] = 1;
                    q.push(e.v);
                }
            }
        }
    }
}

priority_queue<node> que;
int A_Star(int s, int t, int k) {
    while (!que.empty()) que.pop();
    que.push(node(s, 0, dist[s]));
    while (!que.empty()) {
        node now = que.top();
        que.pop();
        if (now.v == t) {
            if (k > 1) k--;
            else return now.g;
        }
        int u = now.v;
        for (int i = 0; i < RG[u].size(); i++) {
            Edge& e = edges[RG[u][i]];
            que.push(node(e.u, now.g + e.w, now.g + e.w + dist[e.u]));
        }
    }
    return -1;
}

void addedge(int u, int v, int w) {
    edges.push_back(Edge(u, v, w));
    int sz = edges.size();
    G[u].push_back(sz - 1);
}

void addrevedge(int u, int v, int w) {
    revedges.push_back(Edge(u, v, w));
    int sz = revedges.size();
    RG[u].push_back(sz - 1);
}

void init() {
    for(int i = 0; i <= n; i++) {G[i].clear(); RG[i].clear();}
    edges.clear();
    revedges.clear();
}

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        init();
        for (int i = 0; i < m; i++) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            addrevedge(a, b, c);
            addedge(b, a, c);
        }
        int s, t, k;
        scanf("%d%d%d", &s, &t, &k);
        if (s == t) k++;
        spfa(t);
        int ans = A_Star(s, t, k);
        printf("%d\n", ans);

    }
    return 0;
}
