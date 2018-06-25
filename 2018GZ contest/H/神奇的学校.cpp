#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

const int maxn = 100100;
typedef long long int LL;

int n, m, c;

struct Edge {
	int from, to, next;
	LL weight;
}edge[3 * maxn];

int Adj[maxn], Size;
int p[maxn], cq[maxn];
LL dist[maxn];
bool inq[maxn];

void init() {
	memset(Adj, -1, sizeof(Adj));
    Size = 0;
}

void Add_Edge(int u, int v, LL w) {
	edge[Size].from = u;
	edge[Size].to = v;
	edge[Size].next = Adj[u];
	edge[Size].weight = w;
	Adj[u] = Size++;
}

bool spfa(){
	memset(dist, 63, sizeof(dist));
	memset(p, 0, sizeof(p));
	memset(cq, 0, sizeof(cq));
	memset(inq, false, sizeof(inq));
	int k = c;
	queue<int> q;
	for (int i = 0; i < k; i++) {
		int x;
		scanf("%d", &x);
		dist[x] = 0;
        p[x] = x;
		q.push(x);
        cq[x] = 1;
        inq[x] = true;
	}
	while (!q.empty()){
		int u = q.front();
        q.pop();
		for (int i = Adj[u]; ~i; i = edge[i].next) {
			int v = edge[i].to;
			if (dist[v] > dist[u] + edge[i].weight) {
				dist[v] = dist[u] + edge[i].weight;
				p[v] = p[u];
				if (!inq[v]) {
					inq[v] = true;
					cq[v]++;
					if (cq[v] >= n) return false;
					q.push(v);
				}
			}
		}
		inq[u] = false;
	}
	return true;
}

struct BA{
	int x, y;
	LL w;
}bian[3 * maxn];

bool cmp(BA a, BA b) {
	return a.w < b.w;
}

int fa[maxn];

int find(int x) {
	if(fa[x] == x) return x;
	return fa[x] = find(fa[x]);
}

int main() {
    //freopen("C:\\Users\\Administrator\\Desktop\\高校联盟题目\\1\\1.in", "r", stdin);
    //freopen("C:\\Users\\Administrator\\Desktop\\高校联盟题目\\1\\1.out", "w", stdout);
	while (scanf("%d%d", &n, &m) != EOF) {
        init();
        for (int i=0; i<m; i++) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            Add_Edge(a, b, c);
            Add_Edge(b, a, c);
        }
        scanf("%d", &c);
        spfa();
        for (int i = 0; i <= n + 10; i++) fa[i] = i;
        for (int i = 0; i < Size; i++) {
            int u = edge[i].from;
            int v = edge[i].to;
            bian[i].x = p[u];
            bian[i].y = p[v];
            bian[i].w = dist[u] + dist[v] + edge[i].weight;
        }
        sort(bian, bian+Size, cmp);
        int cnt = 1;
        LL ans = dist[1];
        for (int i = 0; i < Size && cnt < c; i++) {
            int u = bian[i].x;
            int v = bian[i].y;
            LL w = bian[i].w;
            if (u == v) continue;
            int U = find(u);
            int V = find(v);
            if (U == V) continue;
            else {
                ans += w;
                fa[U] = V;
                cnt++;
            }
            if (cnt >= c) break;
        }
        cout << ans << endl;
	}
	return 0;
}
