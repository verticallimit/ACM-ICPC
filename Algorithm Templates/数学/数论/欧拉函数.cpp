欧拉函数
欧拉函数的值等于不超过m并且和m互素的数的个数
如果x和m互素 x^(elur(m)) = 1(mod m)

求欧拉函数值  复杂度O(sqrt(n))
int euler_phi(int n) {
    int res = n;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            res = res / i * (i - 1);
            for (; n % i == 0; n /= i);
        }
    }
    if (n != 1) res = res / n * (n - 1);
    return res;
}

O(MAX_N)时间筛出欧拉函数值的表
int euler[MAX_N];
void euler_phi2() {
    for (int i = 0; i < MAX_N; i++) euler[i] = i;
    for (int i = 2; i < MAX_N; i++) {
        if (euler[i] == i) {
            for (int j = i; j < MAX_N; j += i) euler[j] = euler[j] / i * (i - 1);
        }
    }
}
