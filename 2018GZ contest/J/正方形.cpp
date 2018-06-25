#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std ;
const int maxn = 5000 + 5;
bool vis[maxn<<1][maxn<<1] = {0};//这个要定义成bool类型的，定义成int类型的会超内存
int ch[maxn],sh[maxn] ;
int main()
{
    freopen("C:\\Users\\Administrator\\Desktop\\省赛题目\\J\\1.in", "r", stdin);
    freopen("C:\\Users\\Administrator\\Desktop\\省赛题目\\J\\1.out", "w", stdout);
    int n;
    //memset(vis,0,sizeof(vis)) ;
    while(scanf("%d",&n) != EOF)
    {
        if (n == 0) break;
        int a,b ;
        int cnt = 0 ;
        for(int i = 1 ; i <= n ; i++)
        {
            scanf("%d %d",&a,&b) ;
            ch[i] = a ;
            sh[i] = b ;
            vis[maxn+a][maxn+b] = 1 ;//因为存在负坐标，而数组下标只能为正
        }
        int x1,x2,x3,x4,y1,y2,y3,y4 ;
        for(int i = 2 ; i <= n ; i++)
        {
            x1 = ch[i] ;
            y1 = sh[i] ;
            for(int j = 1 ; j < i ; j++)
            {
                x2 = ch[j] ;
                y2 = sh[j] ;
                x3=x1+(y1-y2);
                y3= y1-(x1-x2);
                x4=x2+(y1-y2);
                y4= y2-(x1-x2);
                if(abs(x3) < maxn && abs(y3) < maxn && abs(x4) < maxn && abs(y4) < maxn) {
                    if(vis[x3+maxn][y3+maxn]&&vis[x4+maxn][y4+maxn])
                    cnt++ ;
                }
                x3=x1-(y1-y2);
                y3= y1+(x1-x2);
                x4=x2-(y1-y2);
                y4= y2+(x1-x2);
                if(abs(x3) < maxn && abs(y3) < maxn && abs(x4) < maxn && abs(y4) < maxn) {
                    if(vis[x3+maxn][y3+maxn]&&vis[x4+maxn][y4+maxn])
                    cnt++ ;
                }
            }
        }
        printf("%d\n",cnt>>2) ;
        for(int i = 1 ; i <= n ; i++) {
            vis[ch[i] + maxn][sh[i] + maxn] = 0;
        }
    }
    return 0 ;
}

/*
 hash解法
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

const int N = 1010;
const int H = 10007;
int ptx[N], pty[N];

struct Node
{
    int x;
    int y;
    int next;
};
Node node[N];
int cur;
int n;
long ans;
int hashTable[H];

void initHash()
{
    for (int i = 0; i < H; ++i) hashTable[i] = -1;
    cur = 0;
    ans = 0;
}

void insertHash(int x, int y)
{
    int h = (x * x + y * y) % H;
    node[cur].x = x;
    node[cur].y = y;
    node[cur].next = hashTable[h];
    hashTable[h] = cur;
    ++cur;
}

bool searchHash(int x, int y)
{
    int h = (x * x + y * y) % H;
    int next;
    next = hashTable[h];
    while (next != -1)
    {
        if (x == node[next].x && y == node[next].y) return true;
        next = node[next].next;
    }
    return false;
}

int main()
{
    while (scanf("%d", &n) != EOF && n)
    {
        initHash();
        for (int i = 0; i < n; ++i)
        {
            scanf("%d%d", &ptx[i], &pty[i]);
            insertHash(ptx[i], pty[i]);
        }
        for (int i = 0; i < n; ++i)
        {
            for (int j = i + 1; j < n; ++j)
            {
                int x1 = ptx[i] - (pty[i] - pty[j]);
                int y1 = pty[i] + (ptx[i] - ptx[j]);
                int x2 = ptx[j] - (pty[i] - pty[j]);
                int y2 = pty[j] + (ptx[i] - ptx[j]);
                if (searchHash(x1, y1) && searchHash(x2, y2)) ++ans;
            }
        }
        for (int i = 0; i < n; ++i)
        {
            for (int j = i + 1; j < n; ++j)
            {
                int x1 = ptx[i] + (pty[i] - pty[j]);
                int y1 = pty[i] - (ptx[i] - ptx[j]);
                int x2 = ptx[j] + (pty[i] - pty[j]);
                int y2 = pty[j] - (ptx[i] - ptx[j]);
                if (searchHash(x1, y1) && searchHash(x2, y2)) ++ans;
            }
        }
        ans >>= 2;
        printf("%ld\n", ans);
    }
    return 0;
}
