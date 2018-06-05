#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

const int maxn = 25;
char mpt[maxn][maxn];
int vis[maxn][maxn][1 << 10];
int dir[4][2] = {1, 0, 0, 1, 0, -1, -1, 0};
int n, m, t;
struct node {
    int x, y;
    int step;
    int state;
};

int bfs(int sx, int sy) {
    queue<node> q;
    q.push(node{sx, sy, 0, 0});
    memset(vis, 0, sizeof(vis));
    vis[sx][sy][0] = 1;
    int ans = -1;
    while (!q.empty()) {
        node now = q.front();
        q.pop();
        if (now.step % t == 0 && (now.x != sx || now.y != sy)) continue;
        if (mpt[now.x][now.y] == '^') {
            ans = now.step; break;
        }
        for (int i = 0; i < 4; i++) {
            int nx = now.x + dir[i][0];
            int ny = now.y + dir[i][1];
            if (vis[nx][ny][now.state] == 1) continue;
            if (mpt[nx][ny] == '*') continue;
            if (mpt[nx][ny] == '.' || mpt[nx][ny] == '^' \
                     || mpt[nx][ny] == '@') {
                q.push(node{nx, ny, now.step + 1, now.state});
                vis[nx][ny][now.state] = 1;
            }
            else if (mpt[nx][ny] >= 'A' && mpt[nx][ny] <= 'J') {
                if (((1 << mpt[nx][ny] - 'A') & now.state) > 0) {
                    q.push(node{nx, ny, now.step + 1, now.state});
                    vis[nx][ny][now.state] = 1;
                }
            }
            else if (mpt[nx][ny] >= 'a' && mpt[nx][ny] <= 'j') {
                q.push(node{nx, ny, now.step + 1, now.state | (1 << mpt[nx][ny] - 'a')});
                vis[nx][ny][now.state | (1 << mpt[nx][ny] - 'a')] = 1;
            }
        }
    }
    return ans;
}

int main() {
    while (scanf("%d%d%d", &n, &m, &t) != EOF) {
        int sx = 1, sy = 1;
        memset(mpt, 0, sizeof(mpt));
        for (int i = 1; i <= n; i++) {
            scanf("%s", mpt[i] + 1);
            for (int j = 1; j <= m; j++) {
                if (mpt[i][j] == '@') {
                    sx = i;
                    sy = j;
                }
            }
        }
        int ans = bfs(sx, sy);
        printf("%d\n", ans);
    }
    return 0;
}
