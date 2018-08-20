#include <algorithm>
#include <stdio.h>
#include <string.h>
using namespace std;

const int maxn = 105;
#define INF 0x3f3f3f3f

int mpt[maxn][maxn];
int dist[maxn];
//int vis[maxn];

int main(){
    int N , M;
    while(scanf("%d",&N) != EOF) {
        if (N == 0) break;
        M = N * (N - 1) / 2;
        for (int i = 1; i <= N; i++) {
            dist[i] = INF;
            //vis[i] = 0;
            for (int j = 1; j <= N; j++) {
                if (i == j) mpt[i][j] = 0;
                else mpt[i][j] = INF;
            }
        }
        for(int i = 0;i < M;i++) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            mpt[u][v] = w;
            mpt[v][u] = w;
        }
        long long int sum = 0;
        int flag = 0;
        for (int i = 1; i <= N; i++) dist[i] = mpt[1][i];
        for (int i = 1; i < N; i++) {
            int min_len = INF;
            int min_p = -1;
            for (int j = 1; j <= N; j++) {
                if (min_len > dist[j] && dist[j] != 0) {
                    min_len = dist[j];
                    min_p = j;
                }
            }
            if (min_p == -1) {
                flag = 1; break;
            }
            //vis[min_p] = 1;
            sum += min_len;
            for (int j = 1; j <= N; j++) {
                if (dist[j] > mpt[min_p][j] && dist[j] != 0)
                    dist[j] = mpt[min_p][j];
            }
        }
        printf("%lld\n", sum);
    }
    return 0;
}
