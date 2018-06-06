/*
DLX精确覆盖模板
*/
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
const int maxnode = 500010;
const int MaxM = 1010;
const int MaxN = 510;
struct DLX {
    int n, m, cnt;
    int U[maxnode], D[maxnode], R[maxnode], L[maxnode], Row[maxnode], Col[maxnode];
    int H[MaxN], S[MaxM];
    int ansd;
    void init(int _n, int _m) {
        n = _n;
        m = _m;
        for (int i = 0; i <= m; i++) {
            S[i] = 0;
            U[i] = D[i] = i;
            L[i] = i - 1;
            R[i] = i + 1;
        }
        R[m] = 0; L[0] = m;
        cnt = m;
        for (int i = 1; i <= n; i++)
            H[i] = -1;
    }
    void Link(int r, int c) {
        ++S[Col[++cnt] = c];
        Row[cnt] = r;
        D[cnt] = D[c];
        U[D[c]] = cnt;
        U[cnt] = c;
        D[c] = cnt;
        if (H[r] < 0) H[r] = L[cnt] = R[cnt] = cnt;
        else {
            R[cnt] = R[H[r]];
            L[R[H[r]]] = cnt;
            L[cnt] = H[r];
            R[H[r]] = cnt;
        }
    }
    void remove(int c) {
        L[R[c]] = L[c]; R[L[c]] = R[c];
        for (int i = D[c]; i != c; i = D[i])
            for (int j = R[i]; j != i; j = R[j]) {
                U[D[j]] = U[j];
                D[U[j]] = D[j];
                --S[Col[j]];
            }
    }
    void resume(int c) {
        for (int i = U[c]; i != c; i = U[i])
            for (int j = L[i]; j != i; j = L[j])
                ++S[Col[U[D[j]]=D[U[j]]=j]];
        L[R[c]] = R[L[c]] = c;
    }
    void Dance(int d) {
        //剪枝下
        if (ansd != -1 && ansd <= d) return;
        if (R[0] == 0) {
            if (ansd == -1) ansd = d;
            else if (d < ansd) ansd = d;
            return;
        }
        int c = R[0];
        for(int i = R[0];i != 0;i = R[i])
            if(S[i] < S[c])
                c = i;
        remove(c);
        for (int i = D[c]; i != c; i = D[i]) {
            for (int j = R[i]; j != i; j = R[j])remove(Col[j]);
            Dance(d + 1);
            for (int j = L[i]; j != i; j = L[j])resume(Col[j]);
        }
        resume(c);
    }
};
DLX g;

int main() {
    int T;
    int n, m, p;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &n, &m, &p);
        g.init(p, n * m);上
        int x1, y1, x2, y2;
        for (int k = 1; k <= p; k++) {
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
            for (int i = x1 + 1; i <= x2; i++)
                for (int j = y1 + 1; j <= y2; j++)
                    g.Link(k, j + (i - 1) * m);
        }
        g.ansd = -1;
        g.Dance(0);
        printf("%d\n", g.ansd);
    }
    return 0;
}
/*
DLX重复覆盖模板
*/
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
#define INF 0x3f3f3f3f
const int MaxM = 15 * 15 + 10;
const int MaxN = 15 * 15 + 10;
const int maxnode = MaxM * MaxN;
struct DLX {
    int n, m, cnt;
    int U[maxnode], D[maxnode], R[maxnode], L[maxnode], Row[maxnode], Col[maxnode];
    int H[MaxN], S[MaxM];
    int ansd;
    void init(int _n, int _m) {
        n = _n;
        m = _m;
        for (int i = 0;i <= m;i++) {
            S[i] = 0;
            U[i] = D[i] = i;
            L[i] = i-1;
            R[i] = i+1;
        }
        R[m] = 0; L[0] = m;
        cnt = m;
        for (int i = 1;i <= n;i++)H[i] = -1;
    }
    void Link(int r, int c) {
        ++S[Col[++cnt]=c];
        Row[cnt] = r;
        D[cnt] = D[c];
        U[D[c]] = cnt;
        U[cnt] = c;
        D[c] = cnt;
        if (H[r] < 0)H[r] = L[cnt] = R[cnt] = cnt;
        else {
            R[cnt] = R[H[r]];
            L[R[H[r]]] = cnt;
            L[cnt] = H[r];
            R[H[r]] = cnt;
        }
    }
    void remove(int c) {
        for (int i = D[c];i != c;i = D[i])
            L[R[i]] = L[i], R[L[i]] = R[i];
    }
    void resume(int c) {
        for (int i = U[c];i != c;i = U[i])
            L[R[i]] = R[L[i]] = i;
    }
    bool v[MaxM];
    int f() {
        int ret = 0;
        for (int c = R[0]; c != 0;c = R[c])v[c] = true;
        for (int c = R[0]; c != 0;c = R[c]) {
            if (v[c]) {
                ret++;
                v[c] = false;
                for (int i = D[c];i != c;i = D[i])
                    for (int j = R[i];j != i;j = R[j])
                        v[Col[j]] = false;
            }
        }
        return ret;
    }
    void Dance(int d) {
        if (d + f() >= ansd)return;
        if (R[0] == 0) {
            if(d < ansd)ansd = d;
            return;
        }
        int c = R[0];
        for (int i = R[0];i != 0;i = R[i])
            if (S[i] < S[c])
                c = i;
        for (int i = D[c];i != c;i = D[i]) {
            remove(i);
            for (int j = R[i];j != i;j = R[j])remove(j);
            Dance(d+1);
            for (int j = L[i];j != i;j = L[j])resume(j);
            resume(i);
        }
    }
};
DLX g;

int main() {
    int n, m;
    int mpt[20][20];
    int hash[400];
    while (scanf("%d%d", &n, &m) != EOF) {
        memset(mpt, 0, sizeof(mpt));
        memset(hash, 0, sizeof(hash));
        int total = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                scanf("%d", &mpt[i][j]);
                if (mpt[i][j] == 1) {
                    total++;
                    hash[(i - 1)* m + j] = total;
                }
            }
        }
        int n1, m1;
        scanf("%d%d", &n1, &m1);
        g.init((n - n1 + 1) * (m - m1 + 1), total);
        int cnt = 0;
        for (int i = 1; i <= n && i + n1 - 1 <= n; i++) {
            for (int j = 1; j <= m && j + m1 - 1 <= m; j++) {
                cnt++;
                for (int p = i; p < i + n1; p++) {
                    for (int q= j; q < j + m1; q++) {
                        if (mpt[p][q] == 1) {
                            g.Link(cnt, hash[(p - 1) * m + q]);
                        }
                    }
                }
            }
        }
        g.ansd = INF;
        g.Dance(0);
        printf("%d\n", g.ansd);
    }
    return 0;
}
