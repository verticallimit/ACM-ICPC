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
}edge[maxn];

int cmp(node A, node B) {
    if (A.w < B.w) return 1;
    else return 0;
}
int fa[maxn];

int find(int x) {
    if (x == fa[x]) return x;
    fa[x] = find(fa[x]);
    return fa[x];
}

int main(){
        int N , M;
        while(scanf("%d%d",&N ,&M) != EOF){
        if (N == 0) break;
        for (int i = 1; i <= M; i++)
            fa[i] = i;
                for(int i = 0;i < N;i++) {
            scanf("%d%d%d", &edge[i].u, &edge[i].v, &edge[i].w);
                }
                sort(edge, edge + N, cmp);
        long long int sum = 0;
        int total = 0;
        for (int i = 0; i < N; i++) {
            int fx = find(edge[i].u);
            int fy = find(edge[i].v);
            if (fx != fy) {
                fa[fx] = fy;
                sum += edge[i].w;
                total++;
            }
        }
        if (total == M - 1) printf("%lld\n", sum);
        else printf("?\n");
        }
        return 0;
}
