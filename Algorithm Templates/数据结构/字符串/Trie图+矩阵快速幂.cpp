/*
AC自动机构造trie图+矩阵快速幂
求不含有给定的字符串的数量
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

class ACAutomaton
{
public:
    int  n;                          //当前结点总数
    int  id['z'+1];                  //字母x对应的结点编号为id[x]
    int  fail[MAX_N];                //fail指针
    bool tag[MAX_N];                 //本题所需
    int  trie[MAX_N][CLD_NUM];       //trie tree

    void init()
    {
        id['a'] = 0;id['b'] = 1;id['c'] = 2;id['d'] = 3;
        id['e'] = 4;id['f'] = 5;id['g'] = 6;id['h'] = 7;
        id['i'] = 8;id['j'] = 9;id['k'] = 10;id['l'] = 11;
        id['m'] = 12;id['n'] = 13;id['o'] = 14;id['p'] = 15;
        id['q'] = 16;id['r'] = 17;id['s'] = 18;id['t'] = 19;
        id['u'] = 20;id['v'] = 21;id['w'] = 22;id['x'] = 23;
        id['y'] = 24;id['z'] = 25;
    }

    void reset()
    {
        memset(trie[0], -1, sizeof(trie[0]));
        tag[0] = false;
        n = 1;
    }

    //插入模式串s，构造单词树(keyword tree)
    void add(char *s)
    {
        int p = 0;
        while (*s)
        {
            int i = id[*s];
            if ( -1 == trie[p][i] )
            {
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
    void construct()
    {
        queue<int> Q;
        fail[0] = 0;
        for (int i = 0; i < CLD_NUM; i++)
        {
            if (-1 != trie[0][i])
            {
                fail[trie[0][i]] = 0;
                Q.push(trie[0][i]);
            }
            else
            {
                trie[0][i] = 0;    //这个不能丢
            }
        }
        while ( !Q.empty() )
        {
            int u = Q.front();
            Q.pop();
            if (tag[fail[u]])
                tag[u] = true;         //这个很重要，当u的后缀是病毒，u也不能出现
            for (int i = 0; i < CLD_NUM; i++)
            {
                int &v = trie[u][i];
                if ( -1 != v )
                {
                    Q.push(v);
                    fail[v] = trie[fail[u]][i];
                }
                else
                {
                    v = trie[fail[u]][i];
                }
            }
        }
    }

    /* 根据trie树来构建状态转换的邻接矩阵mat[][]
       mat[i][j]表示状态i到状态j有几条边   */
    void buildMatrix()
    {
        memset(mat, 0, sizeof(mat));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < CLD_NUM; j++)
                if ( !tag[i] && !tag[trie[i][j]] )  //tag值为true的结点不能要，因为该结点的状态表示一个病毒
                    mat[i][trie[i][j]]++;
    }
} AC;

void matrixMult(MATRIX t1, MATRIX t2, MATRIX res)
{
    for (int i = 0; i < AC.n; i++)
        for (int j = 0; j < AC.n; j++)
        {
            res[i][j] = 0;
            for (int k = 0; k < AC.n; k++)
            {
                res[i][j] += ((t1[i][k] % mod) * (t2[k][j] % mod) % mod);
            }
            res[i][j] %= mod;
        }
}

/*
    递归二分计算矩阵的p次幂，结果存在m2[][]中
*/
void matrixPower(int p)
{
    if (p == 1)
    {
        for (int i = 0; i < AC.n; i++)
            for (int j = 0; j < AC.n; j++)
                m2[i][j] = mat[i][j];
        return;
    }

    matrixPower(p/2);          //计算矩阵的p/2次幂，结果存在m2[][]
    matrixMult(m2, m2, m1);    //计算矩阵m2的平方，结果存在m1[][]

    if (p % 2)                 //如果p为奇数，则再计算矩阵m1乘以原矩阵mat[][]，结果存在m2[][]
        matrixMult(m1, mat, m2);
    else
        swap(m1, m2);
}

int main()
{
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
