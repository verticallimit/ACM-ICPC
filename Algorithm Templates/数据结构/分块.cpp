/*
区间众数问题

*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
#define pii pair<int, int>
#define MP make_pair
#define fir first
#define sec second
const int N=4e4+5,M=350;
typedef unsigned long long ll;
inline int read(){
    char c=getchar();int x=0,f=1;
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
    return x*f;
}
int n,Q,x,y,a[N],mp[N];
int pos[N],m,block;
struct _blo{int l,r;} b[M];
inline void ini(){
    block=sqrt(n);
    m=(n-1)/block+1;
    for(int i=1;i<=n;i++) pos[i]=(i-1)/block+1;
    for(int i=1;i<=m;i++) b[i].l=(i-1)*block+1,b[i].r=i*block;
    b[m].r=n;
}

pii f[M][M];
int c[N],s[M][N];
struct Block{
    void set(int x){
        memset(c,0,sizeof(c));
        pii now(0,0);
        for(int i=b[x].l;i<=n;i++){
            c[a[i]]++; int t=pos[i];
            now=max(now,MP( c[a[i]],-a[i] ) );
            f[x][t]=now;
        }
        for(int i=1;i<=mp[0];i++) s[x][i]=s[x-1][i];
        for(int i=b[x].l;i<=b[x].r;i++) s[x][a[i]]++;
    }

    int t[N];
    int que(int l,int r){
        pii re=f[pos[l]+1][pos[r]-1];
        if(pos[l]==pos[r]){
            for(int i=l;i<=r;i++) t[a[i]]=0;
            for(int i=l;i<=r;i++) re=max(re,MP( ++t[a[i]],-a[i] ) );
        }else{
            int L=pos[l],R=pos[r]-1;
            for(int i=l;i<=b[pos[l]].r;i++) t[a[i]]=s[R][ a[i] ] - s[L][ a[i] ];
            for(int i=b[pos[r]].l;i<=r;i++) t[a[i]]=s[R][ a[i] ] - s[L][ a[i] ];
            for(int i=l;i<=b[pos[l]].r;i++) re=max(re,MP( ++t[a[i]],-a[i] ) );
            for(int i=b[pos[r]].l;i<=r;i++) re=max(re,MP( ++t[a[i]],-a[i] ) );
        }
        return -re.sec;
    }
}B;
int main(){
    //freopen("in","r",stdin);
    n=read();Q=read();
    for(int i=1;i<=n;i++) a[i]=mp[i]=read();
    sort(mp+1,mp+1+n); mp[0]=unique(mp+1,mp+1+n)-mp-1;
    for(int i=1;i<=n;i++)
        a[i]=lower_bound(mp+1,mp+1+mp[0],a[i])-mp;

    ini();
    for(int i=1;i<=m;i++) B.set(i);
    int last=0;
    while(Q--){
        int l=(read()+last-1)%n+1,r=(read()+last-1)%n+1;
        if(l>r) swap(l,r);
        last=mp[ B.que(l,r) ];
        printf("%d\n",last);
    }
}
