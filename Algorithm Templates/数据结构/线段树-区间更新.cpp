#include <string>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define lson (x << 1)
#define rson (x << 1) + 1
const int MAXN = 100000 + 5;
int tree[MAXN << 2];   //树是原区间四倍长
int n, m;
int a[MAXN];
int lazy[MAXN << 2];

void push_up(int x) {
    tree[x] = tree[lson] + tree[rson];
}

void push_down(int x, int l, int r) {
    if (lazy[x] != -1) {
        lazy[lson] = lazy[x];
        lazy[rson] = lazy[x];
        lazy[x] = -1;
        int mid = (l + r) / 2;
        tree[lson] = (mid - l + 1)* lazy[lson];
        tree[rson] = (r - mid)* lazy[rson];
    }
}
void creat(int x, int l, int r) {
    if(l == r) {
      tree[x] = 1;return;
    }
    int mid = (l+ r)/ 2;
    creat(lson, l, mid);
    creat(rson, mid + 1, r);
    push_up(x);
}

void Update(int x, int L, int R, int a, int b, int val) {
    if (L >= a && R <= b) {
        tree[x] = val * (R - L + 1 );
        lazy[x] = val;
        return;
    }
    push_down(x, L, R);
    int mid = (L + R) / 2;
    if (a <= mid) Update(lson, L, mid, a, b, val);
    if (b > mid)  Update(rson, mid + 1, R, a, b, val);
    push_up(x);
}

int main() {
    int repeat; cin >> repeat;
    for (int i = 1; i <= repeat; i++) {
        memset(lazy, -1, sizeof(lazy));
        memset(tree, 0, sizeof(tree));
        scanf("%d", &n);
        creat(1, 1, n);
        scanf("%d", &m);
        while (m --) {
            int A, B, V;
            scanf("%d%d%d", &A, &B, &V);
            Update(1, 1, n, A, B, V);
        }
        printf("Case %d: The total value of the hook is %d.\n", i, tree[1]);
    }
    return 0;
}
