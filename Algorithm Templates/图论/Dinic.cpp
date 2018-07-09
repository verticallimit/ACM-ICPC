//给出n个城市，以及初始时每个城市的人数以及目标人数。初始时有些城市是相连的。
//每个城市的人只可以待在自己的城市或走到与他相邻的城市， 相邻， 相当于只能走一条路。
//如果目标状态不可达， 输出no， 否则输出每个城市的人都是怎么走的
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;
#define N 5005
#define INF 0x3fffffff
int n, m, k;
int level[N];
struct node {
    int to, next, cost;
}edge[N * 10];
int head[N];
int t_head[N];
int s, e;
void init() {
    k = 0;
    memset(head, -1, sizeof(head));
}
int bfs(int s, int t) {//对顶点进行标号、找出层次图
    memset(level, 0, sizeof(level));
    queue<int> q;
    q.push(s);
    level[s] = 1;
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        for (int i = head[now]; i != -1; i = edge[i].next) {
            int y = edge[i].to;
            if (!level[y] && edge[i].cost > 0) {
                level[y] = level[now] + 1;
                q.push(y);
            }
        }
    }
    return level[t] != 0;//汇点是否在层次图中
}
int dfs(int s, int cp) {//在层次图中寻找增广路进行增广
    int flow = 0, temp;
    int t;
    if (s == e || cp == 0)return cp;
    for (;t_head[s] + 1; t_head[s] = edge[t_head[s]].next) {
        int y = edge[t_head[s]].to;
        if (level[s] + 1 == level[y]) {
            temp = dfs(y, min(cp, edge[t_head[s]].cost));
            if (temp > 0) {
                edge[t_head[s]].cost -= temp;
                edge[t_head[s] ^ 1].cost += temp;
                flow += temp;
                cp -= temp;
                if(cp == 0) break;
            }
        }
    }
    return flow;
}

int dinic() {
    int ans = 0, flow = 0;
    while (bfs(s, e)) {//汇点不在层次图中、算法终止
        for (int i = 0; i <= e; i++)
            t_head[i] = head[i];
        ans += dfs(s, INF);
    }
    return ans;
}
void add(int x, int y, int val) {
    edge[k].to = y;
    edge[k].cost = val;
    edge[k].next = head[x];
    head[x] = k++;

    edge[k].to = x;
    edge[k].cost = 0;
    edge[k].next = head[y];
    head[y] = k++;
}
int A[105][205];
int main() {
    int t;
    scanf("%d%d", &n, &m);
    init();
    int sum1 = 0;
    int sum2 = 0;
    s = 0, e = 2 * n + 1;
    for (int i = 1; i <= n; i++) {
        int x;
        scanf("%d", &x);
        sum1 += x;
        add(s, i, x);
    }
    for (int i = 1; i <= n; i++) {
        int x;
        scanf("%d", &x);
        sum2 += x;
        add(n + i, e, x);
        //自身到自身
        add(i, n + i, INF);
    }
    for (int i = 1; i <= m; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        add(a, n + b, INF);
        add(b, n + a, INF);
    }
    int ans = dinic();
    if (sum1 != sum2) {
        printf("NO\n");
        return 0;
    }
    if(sum1 != ans) {
        printf("NO\n");
        return 0;
    }
    else {
        printf("YES\n");
        memset(A, 0, sizeof(A));
        for (int i = 1; i <= n; i++) {
            for (int j = head[i]; j != -1; j = edge[j].next) {
                A[i][edge[j].to - n] = edge[j^1].cost;
            }
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                printf("%d ", A[i][j]);
            }
            printf("\n");
        }
    }
    return 0;
}
