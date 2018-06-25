/*
Tarjan算法
复杂度O(N+M)
*/
const int maxn = 20000 + 10; // 点数
const int maxm = 50000 + 10; // 边数
struct Edge {
    int to, next;
}edge[maxm];
int head[maxn], tot;
int Low[maxn], DFN[maxn],Stack[MAXN],Belong[maxn];//Belong数组的值是1~scc
int Index, top;
int scc;//强连通分量的个数
bool Instack[maxn];
int num[maxn];//各个强连通分量包含点的个数，数组编号1~scc
//num数组不一定需要，结合实际情况

void addedge(int u, int v) {
    edge[tot].to = v;
    edge[tot].next = head[u];
    head[u] = tot++;
}
void Tarjan(int u) {
    int v;
    Low[u] = DFN[u] = ++Index;
    Stack[top++] = u;
    Instack[u] = true;
    for (int i = head[u]; i != -1; i =edge[i].next) {
        v = edge[i].to;
        if (!DFN[v]) {
            tarjan(v);
            if (Low[u] > Low[v]) Low[u] = Low[v];
        }
        else if (Instack[v] && Low[u] > DFS[v])
            Low[u] = DFN[v];
    }
    if (Low[u] == DFN[u]) {
        scc++;
        do {
            v = Stack[--top];
            Instack[v] = false;
            Belong[v] = scc;
            num[scc]++;
        }
        while (v != u);
    }
}

void solve(int N) {
    memset(DFN, 0, sizeof(DFN));
    memset(Instack, false, sizeof(Instack));
    memset(num, 0, sizeof(num));
    Index = scc = top = 0;
    for (int i = 1; i <= N; i++)
        if (!DFN[i])
            Tarjan(i);
}

void init() {
    tot = 0;
    memset(head, -1, sizeof(head));
}
