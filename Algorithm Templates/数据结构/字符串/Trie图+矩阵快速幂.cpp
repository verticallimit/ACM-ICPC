/*
AC自动机构造trie图+矩阵快速幂
一个长度（为）n的字符串、求不含有给定的字符串的数量
*/
#include <cstdio>
#include <queue>
#include <algorithm>
#include <iostream>
#include <cstring>

using namespace std;

const int MAX_N = 10 * 10 + 5;   //最大结点数：模式串个数 X 模式串最大长度
const int CLD_NUM = 26;           //从每个结点出发的最多边数：本题是4个ATCG

typedef long long MATRIX[MAX_N][MAX_N];

MATRIX mat, mat1, mat2;
long long (*m1)[MAX_N], (*m2)[MAX_N];

int mod = 1e9 + 7;

class ACAutomaton {
public:
    int  n;                          //当前结点总数
    int  id['z'+1];                  //字母x对应的结点编号为id[x]
    int  fail[MAX_N];                //fail指针
    bool tag[MAX_N];                 //本题所需
    int  trie[MAX_N][CLD_NUM];       //trie tree
    void init() {
        id['a'] = 0;id['b'] = 1;id['c'] = 2;id['d'] = 3;
        id['e'] = 4;id['f'] = 5;id['g'] = 6;id['h'] = 7;
        id['i'] = 8;id['j'] = 9;id['k'] = 10;id['l'] = 11;
        id['m'] = 12;id['n'] = 13;id['o'] = 14;id['p'] = 15;
        id['q'] = 16;id['r'] = 17;id['s'] = 18;id['t'] = 19;
        id['u'] = 20;id['v'] = 21;id['w'] = 22;id['x'] = 23;
        id['y'] = 24;id['z'] = 25;
    }
    void reset() {
        memset(trie[0], -1, sizeof(trie[0]));
        tag[0] = false;
        n = 1;
    }
    //插入模式串s，构造单词树(keyword tree)
    void add(char *s) {
        int p = 0;
        while (*s) {
            int i = id[*s];
            if (-1 == trie[p][i]) {
                memset(trie[n], -1, sizeof(trie[n]));
                tag[n] = false;
                trie[p][i] = n++;
            }
            p = trie[p][i];
            s++;
        }
        tag[p] = true;
    }
    //用BFS来计算每个结点的fail指针，构造trie树
    void construct() {
        queue<int> Q;
        fail[0] = 0;
        for (int i = 0; i < CLD_NUM; i++) {
            if (-1 != trie[0][i]) {
                fail[trie[0][i]] = 0;
                Q.push(trie[0][i]);
            }
            else {
                trie[0][i] = 0;    //这个不能丢
            }
        }
        while (!Q.empty()) {
            int u = Q.front();
            Q.pop();
            if (tag[fail[u]])
                tag[u] = true;         //这个很重要，当u的后缀是病毒，u也不能出现
            for (int i = 0; i < CLD_NUM; i++) {
                int &v = trie[u][i];
                if ( -1 != v ) {
                    Q.push(v);
                    fail[v] = trie[fail[u]][i];
                }
                else {
                    v = trie[fail[u]][i];
                }
            }
        }
    }
    /* 根据trie树来构建状态转换的邻接矩阵mat[][]
       mat[i][j]表示状态i到状态j有几条边   */
    void buildMatrix() {
        memset(mat, 0, sizeof(mat));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < CLD_NUM; j++)
                if ( !tag[i] && !tag[trie[i][j]] )  //tag值为true的结点不能要，因为该结点的状态表示一个病毒
                    mat[i][trie[i][j]]++;
    }
} AC;

void matrixMult(MATRIX t1, MATRIX t2, MATRIX res) {
    for (int i = 0; i < AC.n; i++) {
        for (int j = 0; j < AC.n; j++) {
            res[i][j] = 0;
            for (int k = 0; k < AC.n; k++) {
                res[i][j] += ((t1[i][k] % mod) * (t2[k][j] % mod) % mod);
            }
            res[i][j] %= mod;
        }
    }
}
//递归二分计算矩阵的p次幂，结果存在m2[][]中
void matrixPower(int p) {
    if (p == 1) {
        for (int i = 0; i < AC.n; i++)
            for (int j = 0; j < AC.n; j++)
                m2[i][j] = mat[i][j];
        return;
    }
    matrixPower(p/2);          //计算矩阵的p/2次幂，结果存在m2[][]
    matrixMult(m2, m2, m1);    //计算矩阵m2的平方，结果存在m1[][]
    if (p % 2)                 //如果p为奇数，则再计算矩阵m1乘以原矩阵mat[][]，结果存在m2[][]
        matrixMult(m1, mat, m2);
    else swap(m1, m2);
}
int main() {
    int n, m;
    while (cin >>  n) {
        char s[105] = {0};
        AC.init();
        AC.reset();
        scanf("%s", s);
        AC.add(s);//这里可以增加多个字符串构造字典树
        AC.construct();
        AC.buildMatrix();
        m1 = mat1;
        m2 = mat2;
        matrixPower(n);
        long long ans = 0;
        for (int i = 0; i < AC.n; i++) {
            ans += m2[0][i];
            ans = ans % mod;
        }
        printf("%lld\n", ans);
    }
    return 0;
}




//是给定一些模式串。求出长度(不超过)m的，包含模式串的个数。
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <queue>
using namespace std;
struct Matrix
{
    unsigned long long mat[40][40];
    int n;
    Matrix(){}
    Matrix(int _n)
    {
        n=_n;
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                mat[i][j] = 0;
    }
    Matrix operator *(const Matrix &b)const
    {
        Matrix ret = Matrix(n);
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                for(int k=0;k<n;k++)
                    ret.mat[i][j]+=mat[i][k]*b.mat[k][j];
        return ret;
    }
};
unsigned long long pow_m(unsigned long long a,int n)
{
    unsigned long long ret=1;
    unsigned long long tmp = a;
    while(n)
    {
        if(n&1)ret*=tmp;
        tmp*=tmp;
        n>>=1;
    }
    return ret;
}
Matrix pow_M(Matrix a,int n)
{
    Matrix ret = Matrix(a.n);
    for(int i=0;i<a.n;i++)
        ret.mat[i][i] = 1;
    Matrix tmp = a;
    while(n)
    {
        if(n&1)ret=ret*tmp;
        tmp=tmp*tmp;
        n>>=1;
    }
    return ret;
}
struct Trie
{
    int next[40][26],fail[40];
    bool end[40];
    int root,L;
    int newnode()
    {
        for(int i = 0;i < 26;i++)
            next[L][i] = -1;
        end[L++] = false;
        return L-1;
    }
    void init()
    {
        L = 0;
        root = newnode();
    }
    void insert(char buf[])
    {
        int len = strlen(buf);
        int now = root;
        for(int i = 0;i < len;i++)
        {
            if(next[now][buf[i]-'a'] == -1)
                next[now][buf[i]-'a'] = newnode();
            now = next[now][buf[i]-'a'];
        }
        end[now] = true;
    }
    void build()
    {
        queue<int>Q;
        fail[root]=root;
        for(int i = 0;i < 26;i++)
            if(next[root][i] == -1)
                next[root][i] = root;
            else
            {
                fail[next[root][i]] = root;
                Q.push(next[root][i]);
            }
        while(!Q.empty())
        {
            int now = Q.front();
            Q.pop();
            if(end[fail[now]])end[now]=true;
            for(int i = 0;i < 26;i++)
                if(next[now][i] == -1)
                    next[now][i] = next[fail[now]][i];
                else
                {
                    fail[next[now][i]] = next[fail[now]][i];
                    Q.push(next[now][i]);
                }
        }
    }
    Matrix getMatrix()
    {
        Matrix ret = Matrix(L+1);
        for(int i = 0;i < L;i++)
            for(int j = 0;j < 26;j++)
                if(end[next[i][j]]==false)
                    ret.mat[i][next[i][j]] ++;
        for(int i = 0;i < L+1;i++)
            ret.mat[i][L] = 1;
        return ret;
    }
    void debug()
    {
        for(int i = 0;i < L;i++)
        {
            printf("id = %3d,fail = %3d,end = %3d,chi = [",i,fail[i],end[i]);
            for(int j = 0;j < 26;j++)
                printf("%2d",next[i][j]);
            printf("]\n");
        }
    }
};
char buf[10];
Trie ac;
int main()
{
    int n,L;
    while(scanf("%d%d",&n,&L)==2)
    {
        ac.init();
        for(int i = 0;i < n;i++)
        {
            scanf("%s",buf);
            ac.insert(buf);
        }
        ac.build();
        Matrix a = ac.getMatrix();
        a = pow_M(a,L);
        unsigned long long res = 0;
        for(int i = 0;i < a.n;i++)
            res += a.mat[0][i];
        res--;

        /*
         * f[n]=1 + 26^1 + 26^2 +...26^n
         * f[n]=26*f[n-1]+1
         * {f[n] 1} = {f[n-1] 1}[26 0;1 1]
         * 数是f[L]-1;
         * 此题的L<2^31.矩阵的幂不能是L+1次，否则就超时了
         */
        a = Matrix(2);
        a.mat[0][0]=26;
        a.mat[1][0] = a.mat[1][1] = 1;
        a=pow_M(a,L);
        unsigned long long ans=a.mat[1][0]+a.mat[0][0];
        ans--;
        ans-=res;
        cout<<ans<<endl;
    }
    return 0;
}
