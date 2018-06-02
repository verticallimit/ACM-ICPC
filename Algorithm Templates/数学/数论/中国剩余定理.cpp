/*
中国剩余定理
M % w[0] = a[0]; M % w[1] = a[1]; M % w[2] = a[2];
已知w[]和a[]求M
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;
typedef int LL;
void extend_gcd(LL a, LL b, LL &x, LL &y, LL &d) {
    if (!b) {d = a, x = 1, y = 0;}
    else {
        extend_gcd(b, a % b, y, x, d);
        y -= a / b * x;
    }
}
//中国剩余定理 a[]存放余数 w[]存放两两互质的数
int Chinese_Remainder(int a[], int w[], int len) {
    int d, x, y, m;
    int ret = 0;
    int n = 1;
    for (int i = 0; i < len; i++)
        n *= w[i];
    for (int i = 0; i < len; i++) {
        m = n / w[i];
        extend_gcd(w[i], m, x, y, d);
        ret = (ret + y * m * a[i]) % n;
    }
    return (n + ret % n) % n;
}
//模线性方程组
int m[10], a[10];//模数为m，余数为a, X % m = a
bool solve(int &m0, int &a0, int m, int a) {
    LL x, y, d;
    extend_gcd(m0, m, x, y, d);
    if (abs(a - a0) % d) return false;
    x *= (a - a0) / d;
    x %= m / d;
    a0 = (x * m0 + a0);
    m0 *= m / d;
    a0 %= m0;
    if (a0 < 0) a0 += m0;
    return true;
}
// 无解返回false 有解返回true
// 解的形式最后为 a0 + m0 * t (0 <= a0 < m0)
bool MLES(int &m0, int &a0, int m[], int a[], int n) {
    bool flag = true;
    m0 = 1;
    a0 = 0;
    for (int i = 0; i < n; i++) {
        if (!solve(m0, a0, m[i], a[i])) {
            flag = false;
            break;
        }
    }
    return flag;
}
int main()
{
    int n, day, ans, T = 1;
    int w[15]={23,28,33}, a[15];
    int x;
    scanf("%d", &x);
    while (scanf("%d%d%d%d",&a[0], &a[1], &a[2], &day) != EOF) {
        if (a[0] == -1 && a[1] == -1 && a[2] == -1) break;
        a[0] %= w[0];
        a[1] %= w[1];
        a[2] %= w[2];
        //ans = Chinese_Remainder(a, w, 3);
        int m0;
        int flag = MLES(m0, ans, w, a, 3);
        ans = ans - day;
        if (ans <= 0) ans = ans + w[0] * w[1] * w[2];
        printf("Case %d: the next triple peak occurs in %d days.\n", T++,ans);
    }
    return 0;
}
