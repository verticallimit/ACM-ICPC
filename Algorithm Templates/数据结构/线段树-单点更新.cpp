#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

#define lson x << 1
#define rson (x << 1) + 1

const int maxn = 200000 + 5;
int tree[maxn << 2];
int arr[maxn];
int ans;
int n, m;

void Create(int x, int l, int r) {
    if (l == r) {
        tree[x] = arr[l];
        return;
    }
    int mid = (l + r) / 2;
    Create(lson, l, mid);
    Create(rson, mid + 1, r);
    tree[x] = max(tree[lson], tree[rson]);
}

void Update(int x, int l, int r, int pos, int val) {
    if (l >= r) {
        tree[x] = val;
        return;
    }
    int mid = (l + r) / 2;
    if (pos <= mid) Update(lson, l, mid, pos, val);
    if (pos > mid) Update(rson, mid + 1, r, pos, val);
    tree[x] = max(tree[lson], tree[rson]);
}

void Query(int x, int l, int r, int L, int R) {
    if (L <= l && R >= r) {
        ans = max(ans, tree[x]);
        return;
    }
    int mid = (l + r) / 2;
    if (L <= mid) Query(lson, l, mid, L, R);
    if (R > mid) Query(rson, mid + 1, r, L, R);
}


int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        for (int i = 1; i <= n; i++) scanf("%d", &arr[i]);
        Create(1, 1, n);
        while (m--) {
            ans = 0;
            char ch;
            int a, b;
            scanf("%s", &ch);
            scanf("%d%d", &a, &b);
            if (ch == 'U') {
                Update(1, 1, n, a, b);
            }
            else {
                Query(1, 1, n, a, b);
                printf("%d\n", ans);
            }
        }
    }
    return 0;
}
