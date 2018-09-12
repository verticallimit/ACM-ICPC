//下面给出最小费用最大流模板、求最大费用只需要取相反数、结果取相反数即可、
const int MAXN = 1010;
const int MAXM = 10010;
const int INF = 0x3f3f3f3f;
struct Edge {
    int to, next, cap, flow, cost;
}edge[MAXM];
int head[MAXN], tol;
int pre[MAXN], dis[MAXN];
bool vis[MAXN];
int N;//节点总个数，节点编号从0 ~ N-1
void init(int n) {
    N = n;
    tol = 0;
    memset(head, -1, sizeof(head));
}
void addedge(int u, int v, int cap, int cost){
    edge[tol].to = v;
    edge[tol].cap = cap;
    edge[tol].cost = cost;
    edge[tol].flow = 0;
    edge[tol].next = head[u];
    head[u] = tol++;
    edge[tol].to = u;
    edge[tol].cap = 0;
    edge[tol].cost = -cost;
    edge[tol].flow = 0;
    edge[tol].next = head[v];
    head[v] = tol++;
}
bool spfa(int s,int t){
    queue<int> q;
    for (int i = 0; i < N; i++) {
        dis[i] = INF;
        vis[i] = false;
        pre[i] = -1;
    }
    dis[s] = 0;
    vis[s] = true;
    q.push(s);
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        vis[u] = false;
        for (int i = head[u];i != -1;i = edge[i].next) {
            int v = edge[i].to;
            if (edge[i].cap > edge[i].flow && dis[v] > dis[u] +edge[i].cost) {
                dis[v] = dis[u] + edge[i].cost;
                pre[v] = i;
                if (!vis[v]) {
                    vis[v] = true;
                    q.push(v);
                }
            }
        }
    }
    if (pre[t] == -1) return false;
    else return true;
}
//返回的是最大流，cost存的是最小费用
int minCostMaxflow(int s, int t, int &cost) {
    int flow = 0;
    cost = 0;
    while(spfa(s,t)) {
        int Min = INF;
        for (int i = pre[t]; i != -1 ; i = pre[edge[i^1].to]) {
            if (Min > edge[i].cap - edge[i].flow)
                Min = edge[i].cap - edge[i].flow;
        }
        for (int i = pre[t];i != -1;i = pre[edge[i^1].to]) {
            edge[i].flow += Min;
            edge[i^1].flow -= Min;
            cost += edge[i].cost*Min;
        }
        flow += Min;
    }
    return flow;
}


//zkw费用流
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
#include <ctime>
#include <map>
#include <queue>
#include <cstdlib>
#include <string>
#include <climits>
#include <set>
#include <vector>
using namespace std;
bool vis[200001];int dist[200001];
//解释一下各数组的含义：vis两个用处：spfa里的访问标记，増广时候的访问标记，dist是每个点的距离标号
int n,m,s,t,ans=0;
//s是起点，t是终点，ans是费用答案
int nedge=-1,p[200001],c[200001],cc[200001],nex[200001],head[200001];
//这里是边表，解释一下各数组的含义：p[i]表示以某一点出发的编号为i的边对应点，c表示编号为i的边的流量，cc表示编号为i的边的费用，nex和head不说了吧。。。
inline void addedge(int x,int y,int z,int zz){
    p[++nedge]=y;c[nedge]=z;cc[nedge]=zz;nex[nedge]=head[x];head[x]=nedge;
}
//建边（数组模拟边表倒挂）
inline bool spfa(int s,int t){
    memset(vis,0,sizeof vis);
    for(int i=0;i<=n;i++)dist[i]=1e9;dist[t]=0;vis[t]=1;
//首先SPFA我们维护距离标号的时候要倒着跑，这样可以维护出到终点的最短路径
    deque<int>q;q.push_back(t);
//使用了SPFA的SLF优化（SLF可以自行百度或Google）
    while(!q.empty()){
        int now=q.front();q.pop_front();
        for(int k=head[now];k>-1;k=nex[k])if(c[k^1]&&dist[p[k]]>dist[now]-cc[k]){
//首先c[k^1]是为什么呢，因为我们要保证正流，但是SPFA是倒着跑的，所以说我们要求c[k]的对应反向边是正的，这样保证走的方向是正确的
            dist[p[k]]=dist[now]-cc[k];
//因为已经是倒着的了，我们也可以很清楚明白地知道建边的时候反向边的边权是负的，所以减一下就对了（负负得正）
            if(!vis[p[k]]){
                vis[p[k]]=1;
                if(!q.empty()&&dist[p[k]]<dist[q.front()])q.push_front(p[k]);else q.push_back(p[k]);
//SLF优化
            }
        }
        vis[now]=0;
    }
    return dist[s]<1e9;
//判断起点终点是否连通
}
inline int dfs(int x,int low){
//这里就是进行増广了
    if(x==t){vis[t]=1;return low;}
    int used=0,a;vis[x]=1;
//这边是不是和dinic很像啊
    for(int k=head[x];k>-1;k=nex[k])if(!vis[p[k]]&&c[k]&&dist[x]-cc[k]==dist[p[k]]){
//这个条件就表示这条边可以进行増广
        a=dfs(p[k],min(c[k],low-used));
        if(a)ans+=a*cc[k],c[k]-=a,c[k^1]+=a,used+=a;
//累加答案，加流等操作都在这了
        if(used==low)break;
    }
    return used;
}
inline int costflow(){
    int flow=0;
    while(spfa(s,t)){
//判断起点终点是否连通，不连通说明满流，做完了退出
        vis[t]=1;
        while(vis[t]){
            memset(vis,0,sizeof vis);
            flow+=dfs(s,1e9);
//一直増广直到走不到为止（这样也可以省时间哦）
        }
    }
    return flow;//这里返回的是最大流，费用的答案在ans里
}
int main()
{
    memset(nex,-1,sizeof nex);memset(head,-1,sizeof head);
    scanf("%d%d%d%d",&n,&m,&s,&t);
    for(int i=1;i<=m;i++){
        int x,y,z,zz;scanf("%d%d%d%d",&x,&y,&z,&zz);
        addedge(x,y,z,zz);addedge(y,x,0,-zz);
    }
    printf("%d ",costflow());printf("%d",ans);
    return 0;
}
