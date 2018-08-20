typedef long long ll;
ll mod_pow(ll x, ll y, ll mod) {
    ll res = 1;
    while (y > 0) {
        if (y & 1) res = res * x % mod; //如果二进制最低位为1、则乘上x^(2^i)
        x = x * x % mod;  // 将x平方
        y >>= 1;
    }
    return res;
}

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const long long MOD = 1e9+7;

struct Matrix
{
    long long mat[4][4];
};
Matrix mul(Matrix a, Matrix b) {
    Matrix ret;
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            ret.mat[i][j] = 0;
            for(int k = 0; k < 4; k++) {
                ret.mat[i][j] += ((a.mat[i][k] % MOD) * (b.mat[k][j] % MOD) + MOD) % MOD;
                ret.mat[i][j] %= MOD;
            }
        }
    }
    return ret;
}
Matrix pow_M(Matrix a,long long n) {
    Matrix ret;//系数矩阵
    memset(ret.mat, 0, sizeof(ret.mat));
    ret.mat[0][0] = ret.mat[0][2] = ret.mat[1][0] = ret.mat[2][1] = ret.mat[3][2] = 1;
    ret.mat[0][1] = 5, ret.mat[0][3] = -1;
    Matrix temp = ret;
    n--;
    while (n) {
        if (n&1) ret = mul(ret, temp);
        temp = mul(temp, temp);
        n >>= 1;
    }
    ret = mul(ret, a);//系数矩阵乘以初始矩阵a得到结果矩阵
    return ret;
}


int main() {
    ll n;
    while (cin >> n) {
        Matrix tmp;
        memset(tmp.mat, 0, sizeof(tmp.mat));
        tmp.mat[0][0] = 36;
        tmp.mat[1][0] = 11;
        tmp.mat[2][0] = 5;
        tmp.mat[3][0] = 1;
        if (n == 1) cout << "1" << endl;
        else if (n == 2) cout << "5" << endl;
        else if (n == 3) cout << "11" << endl;
        else if (n == 4) cout << "36" << endl;
        else {
            Matrix p=pow_M(tmp,n - 4);
            ll ans= p.mat[0][0] % MOD;
            cout << ans << endl;
        }
    }
    return 0;
}
