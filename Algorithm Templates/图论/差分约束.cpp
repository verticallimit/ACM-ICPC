// zoj 1508
// 解不等式组合
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define inf 0x7ffffff

const int maxn = 50005;
int dist[maxn];
int vis[maxn];
int cnt[maxn];
struct node{
    int x, val;
    node(int a, int b) {x = a; val = b;}
};
vector<node> v[maxn];

int SPFA(int s, int t) {
    memset(vis, 0, sizeof(vis));
    memset(dist, 0x3f, sizeof(dist));
    memset(cnt, 0, sizeof(cnt));
    queue<int> q;
    q.push(s);
    vis[s] = 1; dist[s] = 0; cnt[s]++;
    while(!q.empty()) {
        int now = q.front();
        q.pop();
        vis[now] = 0;
        if (cnt[now] > s + 1) return -1;
        for (int i = 0; i < v[now].size(); i++) {
            node next = v[now][i];
            if (dist[next.x] > dist[now] + next.val) {
                dist[next.x] = dist[now] + next.val;
                if (!vis[next.x]) {
                    vis[next.x] = 1; q.push(next.x); cnt[next.x]++;
                }
            }
        }
    }
    return -dist[t - 1];
}

int main() {
    int n;
    while(scanf("%d", &n) != EOF) {
        int maxx = 0, minx = 50005;
        for (int i = 0; i < maxn; i++) v[i].clear();
        for (int i = 1; i <= n; i++) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            if (a < minx) minx = a;
            if (b > maxx) maxx = b;
            v[b].push_back(node(a - 1, -c));
        }
        for (int i = minx; i <= maxx; i++) {
            v[i].push_back(node(i - 1, 0));
            v[i].push_back(node(i + 1, 1));
        }
        int ans = SPFA(maxx, minx);
        printf("%d\n", ans);
    }
    //system("pause");
    return 0;
}  
