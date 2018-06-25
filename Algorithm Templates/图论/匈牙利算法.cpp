/*
二分图匹配（匈牙利算法的DFS实现）(邻接矩阵)
初始化：g[][]两边顶点的划分情况
建立g[i][j]表示i->j的有向边就可以了，是左边向右边的匹配
g没有边相连则初始化为0
uN是匹配左边的顶点数，vN是匹配右边的顶点数
调用：res=hungary();输出最大匹配数
优点：适用于稠密图，DFS找增广路，实现简洁易于理解
时间复杂度：O（VE）
*/
//顶点编号从0顶点编号从0开始的
const int maxn = 500 + 10;
int uN, vN;//u, v的数目， 使用前面必须赋值
int g[maxn][maxn];//领接矩阵
int linker[maxn];
bool used[maxn];
bool dfs(int u) {
    for (int v = 0; v < vN; v++) {
        if (g[u][v] && !used[v]) {
            used[v] = true;
            if (linker[v] == -1 || dfs(linker[v])) {
                linker[v] = u;
                return true;
            }
        }
    }
    return false;
}
int hungary() {
    int res = 0;
    memset(linker, -1, sizeof(linker));
    for (int u = 0; u < uN; u++) {
        memset(used, false, sizeof(used));
        if (dfs(u)) res++;
    }
    return res;
}

/*
匈牙利算法邻接表形式
使用前用init()进行初始化，给uN赋值
加边使用函数addedge(u, v)
*/
const int maxn = 5000 + 10;//点数的最大值
const int maxm = 50000 + 10;//边数的最大值
struct Edge {
    int to, next;
}edge[maxm];
int head[maxn], tot;
void init() {
    tot = 0;
    memset(head, -1, sizeof(head));
}
void addedge(int u, int v) {
    edge[tot].to = v;
    edge[tot].next = head[u];
    head[u] = tot++;
}
int linker[maxn];
bool used[maxn];
int uN;
bool dfs(int u) {
    for (int i = head[u]; i != -1; i = edge[i].next) {
        int v = edge[i].to;
        if (!used[v]) {
            used[v] = true;
            if (linker[v] == -1 || dfs(linker[v])) {
                linker[v] = u;
                return true;
            }
        }
    }
    return false;
}
int hungary() {
    int res = 0;
    memset(linker, -1, sizeof(linker));
    for (int u = 0; u < uN; u++) {//点的编号0~uN-1
        memset(used, false, sizeof(used));
        if (dfs(u)) res++;
    }
    return res;
}
