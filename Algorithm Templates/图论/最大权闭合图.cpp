描述:
给定一个点带权的有向图，求这个图的最大权闭合图？
* 闭合图含义：图中任意的出边所指的点都在图中的点集内。

解法:
建图：
一个超级源点s，超级汇点t。
s连接所有点权为正的点，容量是点权。
所有点权为负的点连接汇点t，容量的点权乘以-1。
原图中 a->b，那么连接 a b，容量无穷大。
求出最大流，那么所有正点权的和减去 最大流 就是最大权闭合图的最大权，就是公司的最大利益。
在残量网络中从原点s出发，一遍dfs，走还有容量的点，经过的点数就是要选定的节点的编号。

最大权闭合图的的权=原图中权值为正的点的和 - 最小割（最大流）
例题：POJ 2987
题意：
公司要进行裁员，裁掉一个人可以获得一定的利益或损失（用正数和负数表示）。
一些人之间有附属关系，比如b是a的下属，则裁掉a就必须裁掉b。
问要取得最大的利益，最少要裁掉几个人，取得的最大利益是多少。

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

#define T (n + 1)

const long long INF = 1e16;

using namespace std;

struct Edge{
	int from, to;
	long long cap;
	Edge() {}
	Edge(int a, int b, long long c) : from(a), to(b), cap(c) {}
};

int n, m;
vector<Edge> edges;
vector<int> G[5005];

void addEdge(int from, int to, long long cap) {
	edges.push_back(Edge(from, to, cap));
	edges.push_back(Edge(to, from, 0));
	int siz = edges.size();
	G[from].push_back(siz - 2);
	G[to].push_back(siz - 1);
}

int cur[5005];
int layer[5005];

bool build() {
	memset(layer, -1, sizeof(layer));
	queue<int> q;
	layer[0] = 0;
	q.push(0);
	while (!q.empty()) {
		int current = q.front();
		q.pop();
		for (int i = 0; i < G[current].size(); i++) {
			Edge e = edges[G[current][i]];
			if (layer[e.to] == -1 && e.cap > 0) {
				layer[e.to] = layer[current] + 1;
				q.push(e.to);
			}
		}
	}
	return layer[T] != -1;
}

long long find(int x, long long curFlow) {
	if (x == T || !curFlow) return curFlow;
	long long flow = 0, f;
	for (int &i = cur[x]; i < G[x].size(); i++) {
		Edge &e = edges[G[x][i]];
		if (layer[e.to] == layer[x] + 1
			&& (f = find(e.to, min(curFlow, e.cap)))) {
			e.cap -= f;
			edges[G[x][i] ^ 1].cap += f;
			flow += f;
			curFlow -= f;
			if (!curFlow) break;
		}
	}
	return flow;
}

long long dinic() {
	long long ans = 0;
	while (build()) {
		memset(cur, 0, sizeof(cur));
		ans += find(0, INF);
	}
	return ans;
}

int main() {
	while (~scanf("%d %d", &n, &m)) {
		for (int i = 0; i <= n; i++)
			G[i].clear();
		edges.clear();
		int a, b;
		long long x;
		long long sum = 0, num = 0;
		long long k = 6000;
		for (int i = 1; i <= n; i++) {
			cin >> x;
			if (x > 0) {
				sum += x;
				num++;
				addEdge(0, i, (long long)x * k - 1);
			} else addEdge(i, T, (long long)-x * k + 1);
		}
		for (int i = 0; i < m; i++) {
			scanf("%d %d", &a, &b);
			addEdge(a, b, INF);
		}
		long long maxFlow = dinic();
		cout << (maxFlow + num) % k << ' ' << sum - (maxFlow + num) / k << endl;
	}
	return 0;
}
