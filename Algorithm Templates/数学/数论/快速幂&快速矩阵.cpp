typedef long long LL;
LL quick_mod(LL a, LL b, int mod) {
    LL res = 1;
    while (b > 0) {
        if (b & 1) res = (res * a) % mod;
        b = b >> 1;
        a = (a * a) % mod;
    }
    return res;
}

struct Matrix {
    int m[3][3];
};
Matrix Mul(Matrix a, Matrix b) {
    Matrix c;
    memset(c.m, 0, sizeof(c.m));
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            for (int k = 0; k < 3; k++)
                c.m[i][j] += ((a.m[i][k] * b.m[k][j]) % Mod + Mod) % Mod;
    return c;
}
Matrix fast_mod(Matrix a, int n) {
    Matrix res;
    memset(res.m,0,sizeof(res.m));
    res.m[0][0] = res.m[1][1] = res.m[2][2] = 1;
    while (n) {
        if (n & 1) res = Mul(res, a);
        n >>= 1;
        a = Mul(a, a);
    }
    return res;
}
