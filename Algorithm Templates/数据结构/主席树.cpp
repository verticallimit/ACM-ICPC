主席树三个经常用到的点：
1.查询区间第k大（在线）
2.查询区间第k大且有更新节点操作（离线，离线主要是为了将线段树上的值离散化，如果数值范围小则不需要离散化，也不需要离线，另外更新操作需要套树状数组）
3.查询区间不同数的个数（树状数组可以实现，但只能离线，主席树实现可以在线）
还有很多线段树能实现的，加了一些条件，都可以用主席树来解。
//poj2104
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int maxn=1e5+100;

int a[maxn];
int rt[maxn];//rt[i]表示由数组前i个元素组成的线段树的根结点
struct node
{
    int l,r;//线段树左右子结点点
    int sum;//结点信息，表示这颗子树存在的元素的数目
}T[maxn*20];
int tot=0;//结点编号
vector<int> v;
int getid(int k)
{
    return lower_bound(v.begin(),v.end(),k)-v.begin()+1;
}
void build(int &o,int l,int r)//建立一颗空树
{
    o=++tot;
    T[o].sum=0;
    if(l==r) return;
    int mid=(l+r)/2;
    build(T[o].l,l,mid);
    build(T[o].r,mid+1,r);
}
void update(int l,int r,int &now,int last,int k)
{
    T[++tot]=T[last];//复制线段树
    //更新当前线段树的根结点
    now=tot;
    T[tot].sum++;
    if(l==r) return;//修改到叶子结点为止
    //根据需要修改的k来确定是修改左子树还是修改右子树
    int mid=(l+r)/2;
    if(k<=mid)
        update(l,mid,T[now].l,T[last].l,k);
    else
        update(mid+1,r,T[now].r,T[last].r,k);
}
int query(int l,int r,int x,int y,int k)//查询区间【x，y】中第小的数
{
    if(l==r) return l;//查询到叶子结点为止
    int mid=(l+r)/2;
    int cnt=T[T[y].l].sum-T[T[x].l].sum;//第y颗树比第x颗树在左子树上多的结点数
    if(cnt>=k)//答案在左子树上
        return query(l,mid,T[x].l,T[y].l,k);
    else
        return query(mid+1,r,T[x].r,T[y].r,k-cnt);
}
int main()
{
    int n,m;
    while(~scanf("%d%d",&n,&m))
    {
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&a[i]);
            v.push_back(a[i]);
        }
        //build(,1,n);
        sort(v.begin(),v.end());
        v.erase(unique(v.begin(),v.end()),v.end());
        build(rt[0],1,n);
        for(int i=1;i<=n;i++)
            update(1,n,rt[i],rt[i-1],getid(a[i]));
        while(m--)
        {
            int x,y,k;
            scanf("%d%d%d",&x,&y,&k);
            printf("%d\n",v[query(1,n,rt[x-1],rt[y],k)-1]);
        }
    }
    return 0;
}
