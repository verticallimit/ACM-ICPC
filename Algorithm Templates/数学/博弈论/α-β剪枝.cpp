题意：
Alice和Bob玩游戏，在一个4x4 的方格上
每个人每次选择2x2的区域将里面的四个值求和加到最后的分数当中(两个人共用一个分数)，
然后逆时针翻转它们，
Alice想要分数尽量大Bob想要分数尽量小
两个人每次的选择都是最优的，求最后的分数

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll mod = 1000000007;
const int inf = unsigned(-1) >> 2;
const int maxn = 1e5 + 5;

using namespace std;

int sum, winx, winy;
int k;
int Map[5][5];

int rote(int x, int y) {
    swap(Map[x][y], Map[x + 1][y]);
    swap(Map[x][y + 1], Map[x + 1][y + 1]);
    swap(Map[x][y], Map[x + 1][y + 1]);
    return Map[x][y] + Map[x + 1][y] + Map[x][y + 1] + Map[x + 1][y + 1];
}

void rerote(int x, int y) {
    swap(Map[x][y], Map[x + 1][y + 1]);
    swap(Map[x][y + 1], Map[x + 1][y + 1]);
    swap(Map[x][y], Map[x + 1][y]);
}

int DFS(int sum, int dep, int alpha, int beta) {
    if(dep == 2 * k) return sum;
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            int tmp = DFS(sum + rote(i, j), dep + 1, alpha, beta);
            rerote(i, j);
            if(dep & 1)
                beta = min(beta, tmp);
            else
                alpha = max(alpha, tmp);
            if(beta <= alpha)
                return dep & 1 ? beta : alpha;
        }
    }
    return dep & 1 ? beta : alpha;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int t;
    cin >> t;
    while(t--) {
        cin >> k;
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                cin >> Map[i][j];
            }
        }
        cout << DFS(sum, 0, -inf, inf) << endl;
    }
    return 0;
}
