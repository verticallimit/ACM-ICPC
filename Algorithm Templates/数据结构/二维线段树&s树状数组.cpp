//二维树状数组
#include<iostream>
#include<algorithm>
using namespace std;
const int MAXN = 1010;
int a[MAXN][MAXN];
bool b[MAXN][MAXN];
int lowbit(int x)
{
    return x & (-x);
}
void modify(int x,int y,int data)
{
    for(int i=x;i<MAXN;i+=lowbit(i))
        for(int j=y;j<MAXN;j+=lowbit(j))
            a[i][j]+=data;
}
int get_sum(int x,int y)
{
    int res=0;
    for(int i=x;i>0;i-=lowbit(i))
        for(int j=y;j>0;j-=lowbit(j))
            res+=a[i][j];
    return res;
}
int main()
{
    int n,x,y,x1,y1;
    char str[2];
    scanf("%d",&n);
    memset(a,0,sizeof(a));
    memset(b,false,sizeof(b));
    while(n--)
    {
        scanf("%s",str);
        if(str[0]=='B')
        {
            scanf("%d %d",&x,&y);
            x++;y++;
            if(b[x][y]) continue;
            modify(x,y,1);
            b[x][y]=true;
        }
        else if(str[0]=='D')
        {
            scanf("%d %d",&x,&y);
            x++;y++;
            if(!b[x][y]) continue;
            modify(x,y,-1);
            b[x][y]=false;
        }
        else {
            scanf("%d %d %d %d",&x,&x1,&y,&y1);
            x++,y++;
            x1++,y1++;
            if(x>x1) swap(x,x1);
            if(y>y1) swap(y,y1);
            int ans=get_sum(x1,y1)-get_sum(x-1,y1)-get_sum(x1,y-1)+get_sum(x-1,y-1);
            printf("%d\n",ans);
        }
    }
    return 0;
}
