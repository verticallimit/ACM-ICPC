/*
POJ 3241 求曼哈顿距离生成树上第K大的边
*/
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN = 100010;
const int  INF = 0x3f3f3f3f;
struct Point{
    int x,y,id;
}p[MAXN];
bool cmp(Point a,Point b){
    if(a.x != b.x)
        return a.x < b.x;
    return a.y < b.y;
}
struct BIT{
    int min_val,pos;
    void init(){
        min_val = INF;
        pos = -1;
    }
}bit[MAXN];
struct Edge{
    int u,v,d;
}edge[MAXN << 2];
bool cmpedge(Edge a,Edge b){
    return a.d < b.d;
}
int tot;
int n;
int F[MAXN];
int find(int x){
    if(F[x] == -1) return x;
    else return F[x] = find(F[x]);
}
void addedge(int u,int v,int d){
    edge[tot].u = u;
    edge[tot].v = v;
    edge[tot].d = d;
    tot ++;
}
int lowbit(int x){
    return x & -x;
}
void update(int i,int val,int pos){
    while(i > 0){
        if(val < bit[i].min_val){
            bit[i].min_val = val;
            bit[i].pos = pos;
        }
        i -= lowbit(i);
    }
}
int ask(int i,int m){
    int min_val = INF, pos = -1;
    while(i <= m){
        if(bit[i].min_val < min_val){
            min_val = bit[i].min_val;
            pos = bit[i].pos;
        }
        i += lowbit(i);
    }
    return pos;
}
int dist(Point a,Point b){
    return abs(a.x - b.x) + abs(a.y - b.y);
}
void Manhattan_minimum_spanning_tree(int n,Point p[]){
    int a[MAXN],b[MAXN];
    tot = 0;
    for(int dir = 0;dir < 4; dir++){
        if(dir == 1 || dir == 3){
            for(int i = 0; i < n; i++)
                swap(p[i].x,p[i].y);
        }
        else if(dir == 2){
            for(int i = 0; i < n; i++)
                p[i].x = - p[i].x;
        }
        sort(p,p + n,cmp);
        for(int i = 0; i < n; i++)
            a[i] = b[i] = p[i].y - p[i].x;
        sort(b,b + n);
        int m = unique(b,b + n) - b;
        for(int i = 1; i <= m; i++)
            bit[i].init();
        for(int i = n - 1; i >= 0; i--){
            int pos = lower_bound(b,b + m,a[i]) - b + 1;
            int ans = ask(pos,m);
            if(ans != -1)
                addedge(p[i].id,p[ans].id,dist(p[i],p[ans]));
            update(pos,p[i].x + p[i].y,i);
        }
    }
}
int solve(int k){
    Manhattan_minimum_spanning_tree(n,p);
    memset(F,-1,sizeof(F));
    sort(edge,edge + tot,cmpedge);
    for(int i = 0; i < tot; i++){
        int u = edge[i].u;
        int v = edge[i].v;
        int t1 = find(u),t2 = find(v);
        if(t1 != t2){
            F[t1] = t2;
            k --;
            if(k == 0) return edge[i].d;
        }
    }
}
int main(){
    int k;
    while(scanf("%d%d",&n,&k) == 2 && n){
        for(int i = 0; i < n; i++){
            scanf("%d%d",&p[i].x,&p[i].y);
            p[i].id = i;
        }
        printf("%d\n",solve(n - k));
    }
    return 0;
}
