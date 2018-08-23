给定一个无向图，要求它的一个子图，使得子图中边数 |E| 与点数 |V| 的比值最大，
即最大化：|E| / |V|
这里仅给出一种解法：
解法一：
假设答案为k ，则要求解的问题是：选出一个合适的点集 V 和边集 E，令(|E|−k∗|V|) 取得最大值。
所谓“合适”是指满足如下限制：若选择某条边，则必选择其两端点。
建图:以原图的边作为左侧顶点，权值为1；原图的点作为右侧顶点，权值为 −k (相当于 支出 k)。
若原图中存在边 (u,v)，则新图中添加两条边 ([uv]−>u), ([uv]−>v)，转换为最大权闭合子图。

POJ 3155
题意：给出了n个点，m条无向边，选一个集合M，要求集合中的边数/点数的值最大
#include<stdio.h>
#include<string.h>
const int N=110;
const double inf=0x3fffffff;
const double eps=1e-8;
int gap[N],dis[N],start,end,ans,sum,head[N],num,dep[N],n,m;
bool vis[N];
struct edge
{
    int st,ed,next;
    double flow;
}e[80*N];
struct node
{
    int x,y;
}P[1100];
void addedge(int x,int y,double w)
{
    e[num].st=x;e[num].ed=y;e[num].flow=w;e[num].next=head[x];head[x]=num++;
    e[num].st=y;e[num].ed=x;e[num].flow=0;e[num].next=head[y];head[y]=num++;
}
void makemap(double g)
{
    int i;
    memset(head,-1,sizeof(head));
    num=0;
    for(i=1;i<=n;i++)
    {
        addedge(start,i,m*1.0);
        addedge(i,end,m+2*g-dep[i]);
    }
    for(i=0;i<m;i++)
    {
        addedge(P[i].x,P[i].y,1.0);
        addedge(P[i].y,P[i].x,1.0);
    }
}
double dfs(int u,double minflow)
{
    if(u==end)return minflow;
    int i,v;
    double f,flow=0.0;
    for(i=head[u];i!=-1;i=e[i].next)
    {
        v=e[i].ed;
        if(e[i].flow>0)
        {
            if(dis[v]+1==dis[u])
            {
                f=dfs(v,e[i].flow>minflow-flow?minflow-flow:e[i].flow);
                flow+=f;
                e[i].flow-=f;
                e[i^1].flow+=f;
                if(minflow-flow<=1e-8)return flow;
                if(dis[start]>=ans)return flow;
            }
        }
    }
    if(--gap[dis[u]]==0)
        dis[start]=ans;
    dis[u]++;
    gap[dis[u]]++;
    return flow;
}
double isap()
{
    double maxflow=0.0;
    memset(gap,0,sizeof(gap));
    memset(dis,0,sizeof(dis));
    gap[0]=ans;
    while(dis[start]<ans)
        maxflow+=dfs(start,inf);
    return maxflow;
}
void dfs1(int u)//遍历要选的点
{
    vis[u]=true;
    sum++;
    for(int i=head[u];i!=-1;i=e[i].next)
    {
        int v=e[i].ed;
        if(vis[v]==false&&e[i].flow>0)
          dfs1(v);
    }
}
int main()
{
    int i;
    double Left,Right,mid,hg;
    while(scanf("%d%d",&n,&m)!=-1)
    {
        if(m==0){printf("1\n1\n");continue;}
        start=0,end=n+1,ans=end+1;
        memset(dep,0,sizeof(dep));
        for(i=0;i<m;i++)
        {
            scanf("%d%d",&P[i].x,&P[i].y);
            dep[P[i].x]++;dep[P[i].y]++;
        }
        Left=0;Right=m;
        while(Right-Left>=1.0/n/n)//胡伯涛的论文给出了证明,不同解之间误差的精度不超过1/(n*n）
        {
            mid=(Left+Right)/2;
            makemap(mid);
            hg=isap();
            hg=(1.0*n*m-hg)/2;
            if(hg>eps)
                Left=mid;
            else Right=mid;
        }
        makemap(Left);//用mid值建图容易wa,因为你此时的mid不一定满足h(mid)>eps,但是Left一定是满足的
        isap();
        memset(vis,false,sizeof(vis));
        sum=0;
        dfs1(0);
        printf("%d\n",sum-1);
        for(i=1;i<=n;i++)
          if(vis[i]==true)
              printf("%d\n",i);
    }
    return 0;
}

题意：给定一个1-n的排列，它的一个子序列（不一定连续）设为S，令这个子序列的逆序对为R(S)，长度为L(S)。
请找到一个S，使得R(S)/L(S)最大。
题解：两个数字如果有逆序关系则连边，跑一遍最大密度子图就是答案。
#include<iostream>
#include<cstdio>
#include<queue>
using namespace std;
#define REP(i,n) for((i)=0;(i)<(int)(n);(i)++)
#define snuke(c,itr) for(__typeof((c).begin()) itr=(c).begin();itr!=(c).end();itr++)
#define eps 1e-10
typedef double F;
#define F_INF (1e20)
#define MAXV 10000
#define MAXE 80*10000// E*2!
F cap[MAXE],flow[MAXE];
int to[MAXE],_prev[MAXE],last[MAXV],used[MAXV],level[MAXV];
struct MaxFlow{
    int V,E;
    MaxFlow(int n){
        int i;
        V=n;E=0;
        REP(i,V) last[i]=-1;
    }
    void add_edge(int x,int y,F f){
        cap[E]=f;flow[E]=0;to[E]=y;_prev[E]=last[x];last[x]=E;E++;
        cap[E]=0;flow[E]=0;to[E]=x;_prev[E]=last[y];last[y]=E;E++;
    }
    bool bfs(int s,int t){
        int i;
        REP(i,V) level[i]=-1;
        queue<int> q;
        q.push(s);level[s]=0;
        while(!q.empty()){
            int x=q.front();q.pop();
            for(i=last[x];i>=0;i=_prev[i]) if(level[to[i]]==-1&&cap[i]>flow[i]) {q.push(to[i]);level[to[i]]=level[x] + 1;}
        }
        return (level[t]!=-1);
    }
    F dfs(int v,int t,F f){
        int i;
        if(v==t) return f;
        for(i=used[v];i>=0;used[v]=i=_prev[i]) if(level[to[i]]>level[v]&&cap[i]>flow[i]){
            F tmp=dfs(to[i],t,min(f,cap[i]-flow[i]));
            if(tmp>0) {flow[i]+=tmp;flow[i^1]-=tmp;return tmp;}
        }
        return 0;
    }
    F maxflow(int s,int t){
        int i;
        while(bfs(s,t)){
            REP(i,V) used[i]=last[i];
            while(dfs(s,t,F_INF) !=0);
        }
        F ans=0;
        for(i=last[s];i>=0;i=_prev[i]) ans+=flow[i];
        return ans;
    }
};
int n,m;
template<typename __ll>
inline void read(__ll &m)
{
    __ll x=0,f=1;char ch=getchar();
    while(!(ch>='0'&&ch<='9')){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    m=x*f;
}
struct edg{
    int u,v;
}E[MAXE];
bool check(double k){
    int i;
    MaxFlow f(m+n+2);
    for(i=1;i<=n;i++) f.add_edge(i,m+n+1,k);
    for(i=1;i<=m;i++) f.add_edge(n+i,E[i].u,F_INF),f.add_edge(n+i,E[i].v,F_INF),f.add_edge(0,n+i,1);
    double ans=m-f.maxflow(0,m+n+1);
    return ans<eps;
}
int a[111];
int main()
{
    int i,j,u,v,T,cas=1;
    cin>>T;
    while(T--){
        cin>>n;
        m=0;
        for(i=1;i<=n;i++) read(a[i]);
        for(i=1;i<=n;i++)
            for(j=i+1;j<=n;j++)
                if(a[i]>a[j])
                    E[++m].u=i,E[m].v=j;
        double l=0,r=m,mid;
        while(l+eps<=r){
            mid=(l+r)/2;
            if(check(mid)) r=mid;
            else l=mid;
        }
        printf("Case #%d: %.10lf\n",cas++,l);
    }
}
