SG函数模板
如果sg[n] = 0，表示必败
如果sg[n] > 0, 说明肯定能转移到必败态，则必胜
int f[N],SG[N];
bool S[M];
void getSG(int n)
{
    memset(SG,0,sizeof(SG));
    for(int i=1;i<=n;i++)
    {
        memset(S,false,sizeof(S));
        for(int j=1;f[j]<=i&&j<M;j++)
        {
             S[SG[i-f[j]]]=true;
        }
        for(int j=0;;j++)
        if(!S[j])
        {
            SG[i]=j;
            break;
        }
    }
}

SG 函数是对游戏图中每一个节点的评估函数。它的定义如下：

f(v) = mex{f(u)|图中有一条从v到u的边}

其中，mex（minimal excludant）是定义在整数集合上的操作。
它的 自变量是任意整数集合，函数值是不属于该集合的最小自然数。
mex{A} = min{k | k不属于A and k属于N}

SG函数的性质：
1.对于任意的局面，如果它的SG值为0，那么它的任何一个后继局面的SG值不为0
2.对于任意的局面，如果它的SG值不为0，那么它一定有一个后继局面的SG值为0

【定理】
在我们每次只能进行一步操作的情况下，对于任何的游戏的和，我们若将其中的任一单一SG-组合游戏
换成数目为它的SG值的一堆石子，该单一SG-组合游戏的规则变成取石子游戏的规则（可以任意取，
甚至取完），则游戏的和的胜负情况不变。

Anti-nim游戏
1.桌子上有 N 堆石子，游戏者轮流取石子。
2.每次只能从一堆中取出任意数目的石子，但不能不取。
3.取走最后一个石子者败。
Anti-SG游戏规定，决策集合为空的游戏者赢。
Anti-SG其他规则与SG游戏相同。

先手必胜当且仅当：
1.所有堆的石子数都为1且游戏的SG值为0
2.有些堆的石子数大于1且游戏的SG值不为0
【SJ定理】
先手必胜当且仅当：
1.游戏的SG函数不为0且游戏中某个单一游戏的SG函数大于1
2.游戏的SG函数为0且游戏中没有单一游戏的SG函数大于1

树的删边游戏
规则如下：
 1.给出一个有 N 个点的树，有一个点作为树的根节点。
 2.游戏者轮流从树中删去边，删去一条边后，不与根节点相连的 部分将被移走。
 3.谁无路可走谁输。
 [定理]
 叶子节点的 SG 值为 0；中间节点的 SG 值为它的所有子节点的 SG 值加 1 后的异或和。

 PKU3710
题目大意：
1. 有 N 个局部联通的图。
2. Harry 和 Sally 轮流从图中删边，删去一条边后，不与根节点相 连的部分将被移走。Sally 为先手。
3. 图是通过从基础树中加一些边得到的。
4. 所有形成的环保证不共用边，且只与基础树有一个公共点。
5. 谁无路可走谁输。
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int N=100+5;
struct Edge{int to,next;}e[N<<1];
int head[N],cnt;
void ins(int u,int v){
	e[++cnt]=(Edge){v,head[u]};head[u]=cnt;
}
int pre[N],vis[N],sg[N];
bool oncircle[N];
int calc(int s,int t){
	int step=1;
	do{oncircle[s]=1;s=pre[s];step++;}while(s!=t);
	oncircle[t]=0;
	return step&1;
}
void dfs(int u,int fa){
	vis[u]=1;sg[u]=0;oncircle[u]=0;
	for(int i=head[u];i;i=e[i].next){
		int v=e[i].to;if(v==fa)continue;
		if(!vis[v]){
			pre[v]=u;
			dfs(v,u);
		}else if(vis[v]==1)sg[v]^=calc(u,v);
	}
	vis[u]=2;
}
void dp(int u,int fa){
	for(int i=head[u];i;i=e[i].next){
		int v=e[i].to;if(v==fa||oncircle[v])continue;
		dp(v,u);sg[u]^=sg[v]+1;
	}
}
int main(){
	//freopen("a.in","r",stdin);
	int n;
	while(~scanf("%d",&n)){
		int ans=0;
		while(n--){
			int m,k;scanf("%d%d",&m,&k);
			for(int i=1;i<=m;i++)vis[i]=head[i]=0;
			cnt=0;
			for(int i=1;i<=k;i++){
				int u,v;scanf("%d%d",&u,&v);
				ins(u,v);ins(v,u);
			}
			dfs(1,-1);
			dp(1,-1);
			ans^=sg[1];
		}
		if(ans)puts("Sally");
		else puts("Harry");
	}
	return 0;
}

无向图的删边游戏
1.一个无相联通图，有一个点作为图的根。
2.游戏者轮流从图中删去边，删去一条边后，不与根节点相连的部 分将被移走。
3.谁无路可走谁输
[定理]
我们可以对无向图做如下改动：将图中的任意一个偶环缩成一个新点，
任意一个奇环缩成一个新点加一个新边，所有连到原先环上的边全部改为与新点相连。
这样的改动不会影响图的 SG 值。
