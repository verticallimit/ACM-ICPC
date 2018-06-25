如果预处理出1<=n<p范围中n!mod p 的表就可以在O(logp n)时间内算出答案
否则复杂度是O(plogp n)
// 求nCk mod p O(logp n)
int mod_comb(int n, int k, int p) {
    if (n < 0 || k < 0 || n < k) return 0;
    int e1, e2, e3;
    int a1 = mod_fact(n, p, e1);
    int a2 = mod_fact(k, p, e2);
    int a3 = mod_fact(n - k, p, e3);
    return a1 * mod_inverse(a2 * a3 % p, p) % p;
}

N!%p
假设p是一个素数
int fact[MAX_P]; // 预处理的n! mod p 的表 O(p)
// 分解n!=a*p^e 返回a mod p  O(logp n)
int mod_fact(int n, int p, int& e) {
    e = 0;
    if (n == 0) return 1;
    // 计算p的倍数的部分
    int res =mod_fact(n / p, p, e);
    e += n / p;
    // 由于(p-1)!=-1 因此(p-1)!^(n/p)只需要知道n/p的奇偶性就可以计算了
    if (n / p % 2 != 0) return res * (p - fact[n % p]) % p;
    return res * fact[n % p] % p;
}
