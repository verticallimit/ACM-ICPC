/*
Burnside引理
对于一个置换f，若一个染色方案s经过置换后不变，称s为f的不动点。
将f的不动点数目记为c(f)，则可以证明等价类数目为所有c(f)的平均值。
l = 1/(G)*[c(a1)+c(a2)+...+c(ag)]
Polya定理
假设一个置换有k个循环，易知每个循环对应的所有位置颜色需一致，而任意两个循环之间
选什么颜色互不影响。因此，如果有m种可选颜色，则该置换对应的不动点个数为m^k。
用其替换burnside引理中的c(f)，即c(f) = m^k。
l = 1/(G)*[k^m(a1)+k^m(a2)+...+k^m(ag)]
*/
/*
n个珠子串成一个圆，用三种颜色去涂色。问一共有多少种不同的涂色方法。
不同的涂色方法被定义为：如果这种涂色情况翻转、旋转不与其他情况相同就为不同。
对于旋转问题：旋转k个位置之后和原来相同的染色方案数就是m^gcd(k,n)。
注意：同时考虑了旋转和翻转问题，置换群的个数应该为2n。
*/

#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std ;
#define LL long long
LL gcd(LL a, LL b) {
    return b == 0 ? a : gcd(b, a % b);
}
LL pow(LL x, LL k) {
    if (k == 1) return x;
    LL s = pow(x, k / 2);
    s = s * s;
    if (k % 2) s *= x;
    return s;
}
int main() {
    LL n, i, ans, num;
    while (scanf("%lld", &n) && n != -1) {
        if (n == 0) {
            printf("0\n");
            continue;
        }
        ans = 0;
        for (i = 0; i < n; i++)
            ans += pow(3, gcd(n, i));
        if (n % 2) {
            ans += n * pow(3, n / 2 + 1);
        }
        else {
            ans += n / 2 * pow(3, n / 2);
            ans += n / 2 * pow(3, n / 2 + 1);
        }
        printf("%lld\n", ans / (n * 2));
    }
    return 0;
}
