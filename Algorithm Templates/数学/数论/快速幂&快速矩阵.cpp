typedef long long ll;
ll mod_pow(ll x, ll y, ll mod) {
    ll res = 1;
    while (n > 0) {
        if (n & 1) res = res * x % mod; //如果二进制最低位为1、则乘上x^(2^i)
        x = x * x % mod;  // 将x平方
        n >>= 1;
    }
    return res;
}

const int MOD = 1e9 + 7;
struct Matrix {
    long long mat[2][2];
};
Matrix mul(Matrix a, Matrix b) {
    Matrix ret;
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            ret.mat[i][j] = 0;
            for(int k = 0; k < 2; k++) {
                ret.mat[i][j] += a.mat[i][k] * b.mat[k][j];
                ret.mat[i][j] %= (MOD - 1);
            }
        }
    }
    return ret;
}
Matrix pow_M(Matrix a,int n) {
    Matrix ret;
    memset(ret.mat, 0, sizeof(ret.mat));
    ret.mat[0][0] = ret.mat[1][1] = 1;
    Matrix temp = a;
    while (n) {
        if (n&1) ret = mul(ret, temp);
        temp = mul(temp, temp);
        n >>= 1;
    }
    return ret;
}
