#include<bits/stdc++.h>
using namespace std;

#define N 1000
#define INF 100000000
struct Edge
{
    int from,to,cap,flow;
    Edge(int u,int v,int c,int f):from(u),to(v),cap(c),flow(f){}
};

struct ISAP
{
    int n,m,s,t;
    vector<Edge>edges;
    vector<int>G[N];
    bool vis[N];
    int d[N],cur[N];
    int p[N],num[N];//比Dinic算法多了这两个数组，p数组标记父亲结点，num数组标记距离d[i]存在几个
    void init() {
        edges.clear();
        for (int i = 0; i < N; i++) {
            G[i].clear();
        }
        memset(vis, false, sizeof(vis));
        memset(d, 0, sizeof(d));
        memset(cur, 0, sizeof(cur));
        memset(num, 0, sizeof(num));
        memset(p, 0, sizeof(p));
    }
    void addedge(int from,int to,int cap)
    {
        edges.push_back(Edge(from,to,cap,0));
        edges.push_back(Edge(to,from,0,0));
        int m=edges.size();
        G[from].push_back(m-2);
        G[to].push_back(m-1);
    }

    int Augumemt()
    {
        int x=t,a=INF;
        while(x!=s)//找最小的残量值
        {
            Edge&e=edges[p[x]];
            a=min(a,e.cap-e.flow);
            x=edges[p[x]].from;
        }
        x=t;
        while(x!=s)//增广
        {
            edges[p[x]].flow+=a;
            edges[p[x]^1].flow-=a;//更新反向边。
            x=edges[p[x]].from;
        }
        return a;
    }
    void bfs()//逆向进行bfs
    {
        memset(vis,0,sizeof(vis));
        queue<int>q;
        q.push(t);
        d[t]=0;
        vis[t]=1;
        while(!q.empty())
        {
            int x=q.front();q.pop();
            int len=G[x].size();
            for(int i=0;i<len;i++)
            {
                Edge&e=edges[G[x][i]];
                if(!vis[e.from]&&e.cap>e.flow)
                {
                    vis[e.from]=1;
                    d[e.from]=d[x]+1;
                    q.push(e.from);
                }
            }
        }
    }

    int Maxflow(int s,int t)//根据情况前进或者后退，走到汇点时增广
    {
        this->s=s;
        this->t=t;
        int flow=0;
        bfs();
        memset(num,0,sizeof(num));
        for(int i=0;i<n;i++)
            num[d[i]]++;
        int x=s;
        memset(cur,0,sizeof(cur));
        while(d[s]<n)
        {
            if(x==t)//走到了汇点，进行增广
            {
                flow+=Augumemt();
                x=s;//增广后回到源点
            }
            int ok=0;
            for(int i=cur[x];i<G[x].size();i++)
            {
                Edge&e=edges[G[x][i]];
                if(e.cap>e.flow&&d[x]==d[e.to]+1)
                {
                    ok=1;
                    p[e.to]=G[x][i];//记录来的时候走的边，即父边
                    cur[x]=i;
                    x=e.to;//前进
                    break;
                }
            }
            if(!ok)//走不动了，撤退
            {
                int m=n-1;//如果没有弧，那么m+1就是n，即d[i]=n
                for(int i=0;i<G[x].size();i++)
                {
                    Edge&e=edges[G[x][i]];
                    if(e.cap>e.flow)
                        m=min(m,d[e.to]);
                }
                if(--num[d[x]]==0)break;//如果走不动了，且这个距离值原来只有一个，那么s-t不连通，这就是所谓的“gap优化”
                num[d[x]=m+1]++;
                cur[x]=0;
                if(x!=s)
                    x=edges[p[x]].from;//退一步，沿着父边返回
            }
        }
        return flow;
    }
};



int main()
{
    int T,tcase = 1;
    cin >> T;
    while(tcase <= T)
    {
        ISAP isap;
        isap.init();
        scanf("%d%d",&isap.n,&isap.m);
        for(int i=0;i<isap.m;i++)
        {
            int from,to,cap;
            scanf("%d%d%d",&from,&to,&cap);
            isap.addedge(from,to,cap);
        }
        isap.s = 1;
        isap.t = isap.n;
        printf("Case %d: %d\n",tcase++,isap.Maxflow(isap.s,isap.t));
    }
    return 0;
}



#include<bits/stdc++.h>
using namespace std;

/*ISAP+bfs初始化+栈优化
*/
const int maxn=110;//点数的最大值
const int maxm=4010;//边数的最大值
const int inf=0x3f3f3f3f;
struct Edge {
  int to,next,cap,flow;
}edge[maxm];//注意是maxm
int tol;
int head[maxn];
int cur[maxn],d[maxn];// 当前弧下标   结点到汇点距离下界
int p[maxn],gap[maxn];//可增广路上的上一条弧   gap优化  //比dinic多的两个数组
void init(){
  tol=0;
  memset(head, -1, sizeof(head));
}

void addedge(int u,int v,int w,int rw = 0){
  edge[tol].to=v; edge[tol].cap=w; edge[tol].flow=0;
  edge[tol].next=head[u]; head[u]=tol++;
  edge[tol].to=u; edge[tol].cap=rw; edge[tol].flow=0;
  edge[tol].next=head[v]; head[v]=tol++;
}

int Q[maxn];
void bfs(int s,int t){//逆向进行bfs
  memset(d, -1, sizeof(d));
  memset(gap, 0, sizeof(gap));
  gap[0]=1;
  int front=0, rear=0;
  d[t]=0;
  Q[rear++]=t;
  while(front!=rear){
  int u=Q[front++];
    for(int i=head[u]; i!=-1; i=edge[i].next){
      int v=edge[i].to;
      if(d[v]!=-1)continue;
      Q[rear++]=v;
      d[v]=d[u]+1;
      gap[d[v]]++;
    }
  }
}

int S[maxn];
int sap(int s,int t,int N){
  bfs(s, t);
  memcpy(cur, head, sizeof(head));
  int top=0;
  int u=s;
  int ans=0;
  while(d[s]<N){
    if(u==t){
      int Min=inf;
      int inser;
      for(int i=0; i<top; i++)//找最小残量值
        if(Min>edge[S[i]].cap-edge[S[i]].flow){
          Min=edge[S[i]].cap-edge[S[i]].flow;
          inser=i;
        }
      for(int i=0; i<top; i++){//增广
        edge[S[i]].flow+=Min;
        edge[S[i]^1].flow-=Min;
      }
      ans+=Min;
      top=inser;
      u=edge[S[top]^1].to;
      continue;
    }
    bool ok=false;
    int v;
    for(int i=cur[u]; i!=-1; i=edge[i].next){
      v=edge[i].to;
      if(edge[i].cap-edge[i].flow && d[v]+1==d[u]){////Advance前进
        ok=true;
        cur[u]=i;
        break;
      }
    }
    if(ok){
      S[top++]=cur[u];
      u=v;
      continue;
    }
    //Retreat走不动了，撤退
    int Min=N;
    for(int i=head[u]; i!=-1; i=edge[i].next)
      if(edge[i].cap-edge[i].flow && d[edge[i].to]<Min){
        Min=d[edge[i].to];
        cur[u]=i;
      }
    gap[d[u]]--;
    if(!gap[d[u]])return ans;
    d[u]=Min+1;
    gap[d[u]]++;
    if(u!=s)u=edge[S[--top]^1].to;//退一步，沿父边返回
  }
  return ans;
}


int main()
{
    int T,tcase = 1;
    cin >> T;
    while(tcase <= T)
    {
        init();
        int n, m;
        scanf("%d%d",&n,&m);
        for(int i=0;i<m;i++)
        {
            int from,to,cap;
            scanf("%d%d%d",&from,&to,&cap);
            addedge(from,to,cap);
        }
        int ans = sap(1, n, n);
        printf("Case %d: %d\n",tcase++,ans);
    }
    return 0;
}
