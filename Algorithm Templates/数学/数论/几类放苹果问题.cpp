几类放苹果问题
苹果m 盘子n 允许有空盘 放法数
不同 不同 允许 n^m
不同 不同 不允许 n!*S(m,n)
不同 相同 允许 S(m,1)+S(m,2)+...+S(m,n),m>=n
S(m,1)+S(m,2)+...+S(m,m),m<=n
不同 相同 不允许 S(m,n)
相同 不同 允许 C(m+n+1,m)
相同 不同 不允许 C(m-1,n-1)
相同 相同 允许 F(n,m)
相同 相同 不允许 F(n,m-n)

F(n,m)是简单放苹果问题。S(m,n)是第二类Stirling数
递推公式：
int F(int m,int n) {
    if (m == 0 || n == 1)
        return 1;
    if (m < n)
        return (F(m, m));
    else
        return (F(m - n, n) + F(m, n - 1));
}
int S(int m, int n) {
    if (m == n || n == 1) return 1;
    return m * S(n - 1, m) + S(m - 1, m - 1);
}s
