数学表达式为ai * x = bi(mid mi)(1 <= i <= n)
解的全集可以写成x = b(mod m) 问题就转化为了求b和m
// 返回一个(b, m)的数对
pair<int, int> linear_congruence(const vector<int>& A, const vector<int>& B, const vector<int>& M) {
    //由于最开始没有任何限制、所以先把解设为表示所有整数的x = 0(mod 1)
    int x = 0, m = 1;
    for (int i = 0; i < A.size(); i++) {
        int a = A[i] * m, b = B[i] - A[i] * x, d = gcd(M[i], a);
        if (b % d != 0) return make_pair(0, -1); // 无解
        int t = b / d * mod_inverse(a / d,M[i] / d) % (M[i] / d);
        x = x + m * t;
        m *= M[i] / d;
    }
    return make_pair(x % m, m);
}
