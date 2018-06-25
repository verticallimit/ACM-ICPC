#include<cstdio>
#include<cstring>
#include<map>
#include<algorithm>
using namespace std;
#define MAXN 33333

struct Query{
	int i, l, r;
	bool operator<(const Query &q) const{
		return r < q.r;
	}
}que[111111];

long long tree[MAXN << 2];
int N, x, y;
void update(int i, int j, int k){
	if (i == j){
		tree[k] += y;
		return;
	}
	int mid = i + j >> 1;
	if (x <= mid) update(i, mid, k << 1);
	else update(mid + 1, j, k << 1 | 1);
	tree[k] = tree[k << 1] + tree[k << 1 | 1];
}
long long query(int i, int j, int k){
	if (x <= i && j <= y) return tree[k];
	int mid = i + j >> 1;
	long long ret = 0;
	if (x <= mid) ret += query(i, mid, k << 1);
	if (y > mid) ret += query(mid + 1, j, k << 1 | 1);
	return ret;
}

int a[MAXN];
long long ans[111111];
int main(){

	int t, n, m;
	scanf("%d", &t);
	while (t--){
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i){
			scanf("%d", a + i);
		}
		scanf("%d", &m);
		for (int i = 0; i < m; ++i){
			scanf("%d%d", &que[i].l, &que[i].r);
			que[i].i = i;
		}
		sort(que, que + m);
		map<int, int> posi;
		memset(tree, 0, sizeof(tree));
		for (N = 1; N < n; N <<= 1);
		int p = 0;
		for (int i = 0; i < m; ++i){
			while (p < que[i].r){
				++p;
				if (posi.count(a[p])){
					x = posi[a[p]]; y = -a[p];
					update(1, N, 1);
				}
				x = p; y = a[p];
				update(1, N, 1);
				posi[a[p]] = p;
			}
			x = que[i].l; y = que[i].r;
			ans[que[i].i] = query(1, N, 1);
		}
		for (int i = 0; i < m; ++i){
			printf("%lld\n", ans[i]);
		}
	}
	return 0;
}
