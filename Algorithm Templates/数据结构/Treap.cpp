定义：前驱，查找该元素在平衡树中不大于该元素的最大元素；后继查找该元素在平衡树中不小于该元素的最小元素。
#include <cstdio>
#include <cstring>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <utility>
#include <vector>
#include <queue>
#include <map>
#include <set>
#define max(x,y) ((x)>(y)?(x):(y))
#define min(x,y) ((x)>(y)?(y):(x))
#define INF 0x3f3f3f3f
#define MAXN 100005

using namespace std;

int cnt=1,rt=0; //节点编号从1开始

struct Tree
{
    int key, size, pri, son[2]; //保证父亲的pri大于儿子的pri
    void set(int x, int y, int z)
    {
        key=x;
        pri=y;
        size=z;
        son[0]=son[1]=0;
    }
}T[MAXN];

void rotate(int p, int &x)
{
    int y=T[x].son[!p];
    T[x].size=T[x].size-T[y].size+T[T[y].son[p]].size;
    T[x].son[!p]=T[y].son[p];
    T[y].size=T[y].size-T[T[y].son[p]].size+T[x].size;
    T[y].son[p]=x;
    x=y;
}

void ins(int key, int &x)
{
    if(x == 0)
        T[x = cnt++].set(key, rand(), 1);
    else
    {
        T[x].size++;
        int p=key < T[x].key;
        ins(key, T[x].son[!p]);
        if(T[x].pri < T[T[x].son[!p]].pri)
            rotate(p, x);
    }
}

void del(int key, int &x) //删除值为key的节点
{
    if(T[x].key == key)
    {
        if(T[x].son[0] && T[x].son[1])
        {
            int p=T[T[x].son[0]].pri > T[T[x].son[1]].pri;
            rotate(p, x);
            del(key, T[x].son[p]);
        }
        else
        {
            if(!T[x].son[0])
                x=T[x].son[1];
            else
                x=T[x].son[0];
        }
    }
    else
    {
        T[x].size--;
        int p=T[x].key > key;
        del(key, T[x].son[!p]);
    }
}

int find(int p, int &x) //找出第p小的节点的编号
{
    if(p == T[T[x].son[0]].size+1)
        return x;
    if(p > T[T[x].son[0]].size+1)
        find(p-T[T[x].son[0]].size-1, T[x].son[1]);
    else
        find(p, T[x].son[0]);
}

int find_NoLarger(int key, int &x) //找出值小于等于key的节点个数
{
    if(x == 0)
        return 0;
    if(T[x].key <= key)
        return T[T[x].son[0]].size+1+find_NoLarger(key, T[x].son[1]);
    else
        return find_NoLarger(key, T[x].son[0]);
}
