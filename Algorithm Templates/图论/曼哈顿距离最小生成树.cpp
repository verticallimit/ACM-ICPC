/*
POJ 3241 求曼哈顿距离生成树上第K大的边
*/
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int N = 1e5 + 5;
const int inf = 0x3f3f3f3f;

struct edge {
    int x, y, v;
    bool operator < (const edge &tmp) const {
        return v < tmp.v;
    }
}E[N<<3];

struct point {
    int x, y, id;
    bool operator < (const point &tmp) const {
        return x == tmp.x ? y < tmp.y : x < tmp.x;
    }
}P[N];

struct lsh {
    int id, a;
    bool operator < (const lsh &tmp) const {
        return a < tmp.a;
        /*     if (a == tmp.a) return id < tmp.id;
                return a < tmp.a;
        */
        }
}LSH[N];

int A[N], F[N];
int MI[N], ID[N];
int n, c, sz, tot, cnt;

int lowbit (int x) { return x&(-x); }

int query(int x) {
    int ans = -1, mi = inf;
    for (; x <= n; x += lowbit(x))
        if (MI[x] < mi) {
            mi = MI[x];
            ans = ID[x];
        }
    return ans;
}

void modify(int x, int mi, int id) {
    for (; x > 0; x -= lowbit(x))
        if (MI[x] > mi) {
            MI[x] = mi;
            ID[x] = id;
        }
}
//BIT维护的是某数字代表的区间的X+Y最小值, 若一区间的不同位置最小值不同, 该区间则没有最小值(即MI数组维护的是其表示的区间都可以取到的最小值)
int find(int x) { return F[x] == x ? x : F[x] = find(F[x]); }

void join(int x, int y) {
    int fx = find(x), fy = find(y);
    if (fx == fy) return;
    F[fx] = fy;
    cnt++;
}

void init (){
    sort(P + 1, P + n + 1);
    for (int i = 1; i <= n; ++i) {
        LSH[i].a = P[i].y - P[i].x;
        LSH[i].id = i;
        MI[i] = inf; ID[i] = -1;
    }
}

int abs(int x, int y) {
    return x > 0 ? x : -x;
}

int dts(int x, int y) {
    return abs(P[x].x - P[y].x) + abs(P[x].y  -P[y].y);
}

void add_edge (int x, int y, int d) {
    E[++sz].x = x; E[sz].y = y; E[sz].v = d;
}

int main() {
    scanf("%d%d", &n, &c);
    for (int i = 1; i <= n; ++i) {
        scanf("%d%d", &P[i].x, &P[i].y);
        P[i].id = i;
    }
    for (int cas = 1; cas <= 4; ++cas) {
        if (cas == 2 || cas == 4)
            for (int i = 1; i <= n; ++i)
                swap(P[i].x, P[i].y);
        if (cas == 3)
            for (int i = 1; i <= n; ++i)
                P[i].x = -P[i].x;
        init();
        sort(LSH + 1, LSH + n + 1);//按Y-X离散化
        for (int i = 1; i <= n; ++i)
            A[LSH[i].id] = i; //A表示某点在BIT中的位置
        for (int i = n; i >= 1; --i) {
            int tmp = query(A[i]);
            if (tmp != -1)
                add_edge(P[tmp].id, P[i].id, dts(tmp, i));
            modify(A[i], P[i].x + P[i].y, i);
        }
    }
    for (int i = 1; i <= n; ++i) F[i] = i;
    sort(E + 1, E + sz + 1);
    for (int i = 1; i <= sz; ++i) {
        join(E[i].x, E[i].y);
        if (cnt == n - c) {
            printf("%d\n", E[i].v);
            break;
        }
    }
    return 0;
}
