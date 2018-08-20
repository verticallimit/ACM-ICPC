#include <algorithm>
#include <stdio.h>
#include <string.h>
using namespace std;

const int maxn = 105;
#define INF 0x3f3f3f3f

struct node {
    int u;
    int v;
    int w;
}edge[maxn * maxn];

int cmp(node A, node B) {
    return A.w < B.w;
}
int fa[maxn];

int find(int x) {
    if (x == fa[x]) return x;
    fa[x] = find(fa[x]);
    return fa[x];
}

int main(){
    int N , M;
    while(scanf("%d",&N) != EOF){
        if (N == 0) break;
        M = N * (N - 1) / 2;
        for (int i = 0; i < M; i++) {
            scanf("%d%d%d", &edge[i].u, &edge[i].v, &edge[i].w);
        }
        for (int i = 1; i <= N; i++) fa[i] = i;
        sort(edge, edge + M, cmp);
        long long int sum = 0;
        int total = 0;
        for (int i = 0; i < M; i++) {
            int fx = find(edge[i].u);
            int fy = find(edge[i].v);
            if (fx != fy) {
                fa[fx] = fy;
                sum += (long long)edge[i].w;
                total++;
            }
        }
        printf("%lld\n", sum);
    }
    return 0;
}
