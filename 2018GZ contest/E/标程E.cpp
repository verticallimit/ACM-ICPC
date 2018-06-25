#include <stdio.h>
#include <map>
#include <queue>
#include <vector>
#include <string.h>
#include <algorithm>
using namespace std;

const int maxn = 100 + 5;
char mpt[maxn][maxn];
int vis[maxn][maxn];
int dir[4][2] = {0, 1, 1, 0, 0, -1, -1, 0};
struct node {
    int x, y;
    int step;
};

int bfs(int sx, int sy) {
    memset(vis, 0, sizeof(vis));
    queue<node> q;
    q.push(node{sx, sy, 0});
    vis[sx][sy] = 1;
    int ans = -1;
    while(!q.empty()) {
        node now = q.front();
        q.pop();
        if (mpt[now.x][now.y] == 'E') {
            ans = now.step;
            break;
        }
        for (int i = 0; i < 4; i++) {
            int nx = now.x + dir[i][0];
            int ny = now.y + dir[i][1];
            if ((mpt[nx][ny] == '*' || mpt[nx][ny] == 'E')&&vis[nx][ny] == 0) {
                q.push(node{nx, ny, now.step + 1});
                vis[nx][ny] = 1;
            }
        }
    }
    return ans;
}

int main() {
    int h, w;
    freopen("C:\\Users\\Administrator\\Desktop\\省赛题目\\E\\1.in", "r", stdin);
    freopen("C:\\Users\\Administrator\\Desktop\\省赛题目\\E\\1.out", "w", stdout);
    while (scanf("%d%d", &h, &w) != EOF) {
        if (h == 0 && w == 0) break;
        int sx = 0, sy = 0;
        memset(mpt, 0, sizeof(mpt));
        for (int i = 1; i <= h; i++) {
            scanf("%s", mpt[i] + 1);
            for (int j = 1; j <= w; j++) {
                if (mpt[i][j] == 'S') {
                    sx = i, sy = j;
                }
            }
        }
        int ans = bfs(sx, sy);
        printf("%d\n", ans);
    }
    return 0;
}
