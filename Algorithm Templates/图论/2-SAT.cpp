2-sat问题即2判定性问题、问题描述基本上是存在多个二元组、某些组中的一个元素与另一组中的某一个元素存在矛盾、
现在要求每一个二元组中选择一个元素、并且使选出来的元素间不存在矛盾关系、
假如X1与Y1有矛盾、则我们连两条有向边X1-->Y2、Y1-->X2、然后求强连通、如果X1和Y2在同一个强连通分量中则无解、
如果要求解选择方案的话需要进行拓扑排序、不过如果是求最小字典序的解有更简单的做法、
/*
HDU 3622  二分答案+2-sat判断可行性
题意:给n对炸弹可以放置的位置(每个位置为一个二维平面上的点),
每次放置炸弹是时只能选择这一对中的其中一个点,每个炸弹爆炸
的范围半径都一样,控制爆炸的半径使得所有的爆炸范围都不相
交(可以相切),求解这个最大半径.
     首先二分最大半径值,然后2-sat构图判断其可行性,对于每
     两队位置(u,uu)和(v,vv),如果u和v之间的距离小于2*id,也就
     是说位置u和位置v处不能同时防止炸弹(两范围相交),所以连边(u,vv)
     和(v,uu),求解强连通分量判断可行性.
注意精度问题
*/
#include<stdio.h>
#include<algorithm>
#include<string.h>
#include<iostream>
#include<math.h>
using namespace std;
const int MAXN=210;
const int MAXM=40005;//边的最大数
const double eps=1e-5;

struct Edge
{
    int to,next;
}edge1[MAXM],edge2[MAXM];
int head1[MAXN];
int head2[MAXN];
int tol1,tol2;
bool vis1[MAXN],vis2[MAXN];
int Belong[MAXN];//连通分量标记
int T[MAXN];//dfs结点结束时间
int Bcnt,Tcnt;
void add(int a,int b)//原图和逆图都要添加
{
    edge1[tol1].to=b;
    edge1[tol1].next=head1[a];
    head1[a]=tol1++;
    edge2[tol2].to=a;
    edge2[tol2].next=head2[b];
    head2[b]=tol2++;
}
void init()//建图前初始化
{
    memset(head1,-1,sizeof(head1));
    memset(head2,-1,sizeof(head2));
    memset(vis1,false,sizeof(vis1));
    memset(vis2,false,sizeof(vis2));
    tol1=tol2=0;
    Bcnt=Tcnt=0;
}
void dfs1(int x)//对原图进行dfs,算出每个结点的结束时间，哪个点开始无所谓
{
    vis1[x]=true;
    int j;
    for(int j=head1[x];j!=-1;j=edge1[j].next)
      if(!vis1[edge1[j].to])
        dfs1(edge1[j].to);
    T[Tcnt++]=x;
}
void dfs2(int x)
{
    vis2[x]=true;
    Belong[x]=Bcnt;
    int j;
    for(j=head2[x];j!=-1;j=edge2[j].next)
       if(!vis2[edge2[j].to])
         dfs2(edge2[j].to);
}

struct Point
{
    int x,y;
}s[MAXN];
double dist(Point a,Point b)
{
    return sqrt((double)(a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

bool ok(int n)//判断可行性
{
    for(int i=0;i<2*n;i++)
      if(!vis1[i])
        dfs1(i);
    for(int i=Tcnt-1;i>=0;i--)
      if(!vis2[T[i]])//这个别写错，是vis2[T[i]]
      {
          dfs2(T[i]);
          Bcnt++;
      }
    for(int i=0;i<=2*n-2;i+=2)
      if(Belong[i]==Belong[i+1])
        return false;
    return true;
}
int main()
{
    int n;
    double left,right,mid;
    while(scanf("%d",&n)!=EOF)
    {
        for(int i=0;i<n;i++)
          scanf("%d%d%d%d",&s[2*i].x,&s[2*i].y,&s[2*i+1].x,&s[2*i+1].y);
        left=0;
        right=40000.0;
        while(right-left>=eps)
        {
            mid=(left+right)/2;
            init();
            for(int i=0;i<2*n-2;i++)
            {
                int t;
                if(i%2==0)t=i+2;
                else t=i+1;
                for(int j=t;j<2*n;j++)
                   if(dist(s[i],s[j])<2*mid)//冲突了
                   {
                       add(i,j^1);
                       add(j,i^1);//注意顺序不能变的
                   }
            }
            if(ok(n))left=mid;
            else right=mid;
        }
        printf("%.2lf\n",right);
    }
    return 0;
}
/*
HDU 1814
输出字典序最小的解
*/
#include <bits/stdc++.h>
using namespace std;

const int maxn = 20000 + 20;
const int maxm = 100000 + 10;
struct Edge {
    int to, next;
}edge[maxm];
int head[maxn], tot;
void init() {
    tot = 0;
    memset(head, -1, sizeof(head));
}
void addedge(int u, int v) {
    edge[tot].to = v;
    edge[tot].next = head[u];
    head[u] = tot++;
}
bool vis[maxn];//染色标记，为true表示选择
int S[maxn], top;//栈
bool dfs(int u) {
    if (vis[u^1]) return false;
    if (vis[u]) return true;
    vis[u] = true;
    S[top++] = u;
    for (int i = head[u]; i != -1; i = edge[i].next)
        if (!dfs(edge[i].to)) return false;
    return true;
}
bool Twosat(int n) {
    memset(vis, false, sizeof(vis));
    for (int i = 0; i < n; i += 2) {
        if (vis[i] || vis[i^1]) continue;
        top = 0;
        if (!dfs(i)) {
            while (top) vis[S[--top]] = false;
            if (!dfs(i^1)) return false;
        }
    }
    return true;
}

int main() {
    int n, m;
    int u, v;
    while (scanf("%d%d", &n, &m) == 2) {
        init();
        while (m--) {
            scanf("%d%d", &u, &v);
            u--;v--;
            addedge(u, v^1);
            addedge(v, u^1);
        }
        if (Twosat(2 * n)) {
            for (int i = 0; i < 2 * n; i++)
                if (vis[i]) printf("%d\n", i + 1);
        }
        else printf("NIE\n");
    }

    return 0;
}
