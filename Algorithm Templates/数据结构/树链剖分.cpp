#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <string>
#include <math.h>
#include <stdlib.h>
using namespace std;

#define lson (x<<1)
#define rson ((x<<1)+1)
const int MAXN = 5e4 + 10;
struct Edge {
    int to,next;
}edge[MAXN*2];
int head[MAXN],tot;
int top[MAXN];//top[v]表示v所在的重链的顶端节点
int fa[MAXN]; //父亲节点
int deep[MAXN];//深度
int num[MAXN];//num[v]表示以v为根的子树的节点数
int p[MAXN];//p[v]表示v与其父亲节点的连边在线段树中的位置
int fp[MAXN];//和p数组相反
int son[MAXN];//重儿子
int pos;
int n;

void init() {
    tot = 0;
    memset(head,-1,sizeof(head));
    pos = 0;
    memset(son,-1,sizeof(son));
}
void addedge(int u,int v) {
    edge[tot].to = v;edge[tot].next = head[u];head[u] = tot++;
}
void dfs1(int u,int pre,int d) {//第一遍dfs求出fa,deep,num,son
    deep[u] = d;
    fa[u] = pre;
    num[u] = 1;
    for(int i = head[u];i != -1; i = edge[i].next) {
        int v = edge[i].to;
        if(v != pre) {
            dfs1(v,u,d+1);
            num[u] += num[v];
            if(son[u] == -1 || num[v] > num[son[u]])
                son[u] = v;
        }
    }
}
void getpos(int u,int sp) {//第二遍dfs求出top和p
    top[u] = sp;
    if(son[u] != -1) {
        p[u] = pos++;
        fp[p[u]] = u;
        getpos(son[u],sp);
    }
    else {
        p[u] = pos++;
        fp[p[u]] = u;
        return;
    }
    for(int i = head[u] ; i != -1; i = edge[i].next) {
        int v = edge[i].to;
        if(v != son[u] && v != fa[u])
            getpos(v,v);
    }
}

//线段树
int tree[MAXN<<2];
void build(int x,int l,int r)
{
    if (l == r) {
        tree[x] = 0;
        return;
    }
    int mid = (l+r)/2;
    build(lson,l,mid);
    build(rson,mid+1,r);
}
void push_up(int x) {
    tree[x] = tree[lson] + tree[rson];
}
void Update(int x, int l, int r, int pos, int val) {
    if (l >= r) {
        tree[x] = val;
        return;
    }
    int mid = (l + r) / 2;
    if (pos <= mid) Update(lson, l, mid, pos, val);
    if (pos > mid) Update(rson, mid + 1, r, pos, val);
    tree[x] = tree[lson] + tree[rson];
}
int Query(int x, int l, int r, int L, int R) {
    if (L <= l && R >= r) {
        return tree[x];
    }
    int mid = (l + r) / 2;
    int ans = 0;
    if (L <= mid) ans += Query(lson, l, mid, L, R);
    if (R > mid) ans += Query(rson, mid + 1, r, L, R);
    return ans;
}
int find(int u,int v) {//查询u->v边的和
    int f1 = top[u], f2 = top[v];
    int tmp = 0;
    while(f1 != f2) {
        if(deep[f1] < deep[f2]) {
            swap(f1,f2);
            swap(u,v);
        }
        tmp = (tmp + Query(1,1,n,p[f1],p[u]));
        u = fa[f1]; f1 = top[u];
    }
    if(u == v)return tmp;
    if(deep[u] > deep[v]) swap(u,v);
    return (tmp + Query(1,1,n,p[son[u]],p[v]));
}
int e[MAXN][3];
int main() {
    int Q;
    while(scanf("%d%d",&n, &Q) != EOF) {
        init();
        for(int i = 0;i < n-1;i++) {
            scanf("%d%d%d",&e[i][0],&e[i][1],&e[i][2]);
            addedge(e[i][0],e[i][1]);
            addedge(e[i][1],e[i][0]);
        }
        dfs1(1,0,0);
        getpos(1,1);
        for(int i = 0;i < n-1; i++) {
            if(deep[e[i][0]] > deep[e[i][1]])
                swap(e[i][0],e[i][1]);
            Update(1,1,n,p[e[i][1]],e[i][2]);
        }
        int op;
        int u,v;
        while(Q--) {
            scanf("%d", &op);
            scanf("%d%d",&u,&v);
            if(op == 1)
                printf("%d\n",find(u,v));
            else Update(1,1,n,p[e[u-1][1]],v);
        }
    }
    return 0;
}




#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <string>
#include <math.h>
#include <stdlib.h>
using namespace std;

#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1

const int MAXN = 8e4 + 10;
struct Edge {
    int to,next;
}edge[MAXN*2];
int head[MAXN],tot;
int top[MAXN];//top[v]表示v所在的重链的顶端节点
int fa[MAXN]; //父亲节点
int deep[MAXN];//深度
int num[MAXN];//num[v]表示以v为根的子树的节点数
int p[MAXN];//p[v]表示v与其父亲节点的连边在线段树中的位置
int fp[MAXN];//和p数组相反
int son[MAXN];//重儿子
int pos;
int n;
int w[MAXN];

void init() {
    tot = 0;
    memset(head,-1,sizeof(head));
    pos = 1;
    memset(son,-1,sizeof(son));
}
void addedge(int u,int v) {
    edge[tot].to = v;edge[tot].next = head[u];head[u] = tot++;
}
void dfs1(int u,int pre,int d) {//第一遍dfs求出fa,deep,num,son
    deep[u] = d;
    fa[u] = pre;
    num[u] = 1;
    for(int i = head[u];i != -1; i = edge[i].next) {
        int v = edge[i].to;
        if(v != pre) {
            dfs1(v,u,d+1);
            num[u] += num[v];
            if(son[u] == -1 || num[v] > num[son[u]])
                son[u] = v;
        }
    }
}
void getpos(int u,int sp) {//第二遍dfs求出top和p
    top[u] = sp;
    if(son[u] != -1) {
        p[u] = pos++;
        fp[p[u]] = u;
        getpos(son[u],sp);
    }
    else {
        p[u] = pos++;
        fp[p[u]] = u;
        return;
    }
    for(int i = head[u] ; i != -1; i = edge[i].next) {
        int v = edge[i].to;
        if(v != son[u] && v != fa[u])
            getpos(v,v);
    }
}

//线段树
int sum[MAXN<<2];
int lazy[MAXN<<2];

void pushdown(int rt,int m){
    if (lazy[rt]){
        lazy[rt<<1]+=lazy[rt];
        lazy[rt<<1|1]+=lazy[rt];
        sum[rt<<1]+=lazy[rt];
        sum[rt<<1|1]+=lazy[rt];
        lazy[rt]=0;
    }
}
void build(int x,int l,int r)
{
    lazy[x] = 0;
    if (l == r) {
        sum[x] = w[fp[l]];
        return;
    }
    int mid = (l+r)/2;
    build(x<<1,l,mid);
    build(x<<1|1,mid+1,r);
}

void update(int L,int R,int val,int l,int r,int rt){
    if (L<=l && r<=R){
        sum[rt]+=val;
        lazy[rt]+=val;
        return;
    }
    pushdown(rt,r-l+1);
    int m=(l+r)>>1;
    if (L<=m) update(L,R,val,lson);
    if (m< R) update(L,R,val,rson);
}

int query(int x,int l,int r,int rt){
    pushdown(rt,r-l+1);
    if (l==r){
        return sum[rt];
    }
    int m=(l+r)>>1;
    if (x<=m) return query(x,lson);
    else return query(x,rson);
}

void updRange(int u,int v,int c) {//更新
    int f1 = top[u], f2 = top[v];
    while(f1 != f2) {
        if(deep[f1] < deep[f2]) {
            swap(f1,f2);
            swap(u,v);
        }
        update(p[f1],p[u],c,1,n,1);
        u = fa[f1]; f1 = top[u];
    }
    //if(u == v)return; 有可能单点更新
    if(deep[u] > deep[v]) swap(u,v);
    update(p[u],p[v],c,1,n,1);
}
int main() {
    int m, Q;
    while(scanf("%d%d%d",&n, &m, &Q) != EOF) {
        init();
        for (int i = 1; i <= n; i++) {
            scanf("%d", &w[i]);
        }
        for(int i = 0;i < n-1;i++) {
            int x, y;
            scanf("%d%d",&x, &y);
            addedge(x, y);
            addedge(y, x);
        }
        dfs1(1,0,0);
        getpos(1,1);
        build(1, 1, n);

        char op[10];
        int u,v,c;
        while(Q--) {
            scanf("%s", op);
            if (strcmp(op, "I") == 0) {
                scanf("%d%d%d",&u,&v,&c);
                updRange(u,v,c);
            }
            else if(strcmp(op, "D")== 0) {
                scanf("%d%d%d",&u,&v,&c);
                updRange(u,v,-c);
            }
            else {
                int pos;
                scanf("%d", &pos);
                printf("%d\n",query(p[pos],1,n,1));
            }
        }
    }
    return 0;
}
