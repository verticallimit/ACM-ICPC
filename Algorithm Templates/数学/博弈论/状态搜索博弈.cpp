题意
Alice和Bob两人玩游戏。两人各有一个棋子，开始时在有向图中不同的点上。
Bob先手，两人轮流移动棋子，每次只能将棋子移到相邻的点上（沿着图上的有向边），
不断重复这样的过程，当那人无法移动时，他就输了（规则1）。
还有两条附加规则：任何时候，当两个棋子到达同一点时，Alice胜出（规则2）。
如果游戏永远无法结束，Bob胜出（规则3）。
两人都遵循最优策略，轮流移动棋子，问最终谁会赢。图中没有自环和重边。

#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
using namespace std;

const int MAXN=100+3;

struct Node
{
    int x,y,z;//Bob位置，Alice位置，该谁走
    Node(int x,int y,int z):x(x),y(y),z(z){};
};

vector<int> G[MAXN];//反向图
int N,M,X,Y;
bool dp[MAXN][MAXN][2];//Bob位置，Alice位置，该谁走(0:Alice,1:Bob)，Bob是否会输
int cnt[MAXN][MAXN];//这个状态往下走输的情况数
int out[MAXN];//出度

int main()
{
    int T;
    scanf("%d",&T);
    for(int cas=1;cas<=T;++cas)
    {
        scanf("%d%d",&N,&M);
        for(int i=1;i<=N;++i)//初始化
        {
            G[i].clear();
            out[i]=0;
            for(int j=1;j<=N;++j)
            {
                dp[i][j][0]=dp[i][j][1]=false;
                cnt[i][j]=0;
            }
        }
        for(int i=0;i<M;++i)
        {
            int a,b;
            scanf("%d%d",&a,&b);
            G[b].push_back(a);
            ++out[a];
        }
        scanf("%d%d",&X,&Y);
        queue<Node> que;
        for(int i=1;i<=N;++i)//相遇
        {
            dp[i][i][0]=dp[i][i][1]=true;
            que.push(Node(i,i,0));
            que.push(Node(i,i,1));
        }
        for(int i=1;i<=N;++i)//无路可走
            if(out[i]==0)
                for(int j=1;j<=N;++j)
                    if(!dp[i][j][0])
                    {
                        dp[i][j][0]=true;
                        que.push(Node(i,j,0));
                    }
        while(!que.empty())
        {
            int x=que.front().x,y=que.front().y,z=que.front().z; que.pop();
            if(z)//该Bob走
            {
                for(int i=0;i<G[x].size();++i)
                    if(++cnt[G[x][i]][y]==out[G[x][i]]&&!dp[G[x][i]][y][0])//全部路径都是必败，这种情况就是必败
                    {
                        dp[G[x][i]][y][0]=true;
                        que.push(Node(G[x][i],y,0));
                    }
            }
            else//该Alice走
            {
                for(int i=0;i<G[y].size();++i)//能够然Bob必败，那么这个情况就是必败
                    if(!dp[x][G[y][i]][1])
                    {
                        dp[x][G[y][i]][1]=true;
                        que.push(Node(x,G[y][i],1));
                    }
            }
        }
        printf("Case #%d: ",cas);
        puts(dp[X][Y][0]?"No":"Yes");
    }

    return 0;
}
