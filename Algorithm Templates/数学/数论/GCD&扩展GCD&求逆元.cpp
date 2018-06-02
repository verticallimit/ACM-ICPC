#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;
LL gcd(LL a, LL b) {
    if (b == 0) return a;
    else return gcd(b, a % b);
}
//返回d = gcd(a, b);和对应于等式ax+by = d中的x,y
void extend_gcd(LL a, LL b, LL &x, LL &y, LL &d) {
    if (!b) {d = a, x = 1, y = 0;}
    else {
        extend_gcd(b, a % b, y, x, d);
        y -= a / b * x;
    }
}
//ax = 1(mod n)   求逆元   逆元公式 (a/b)mod m = (a mod (m * b))/b
LL mod_reverse(LL a, LL n) {
    LL x, y, d;
    extend_gcd(a, n, x, y, d);
    if (d == 1) return (x % n + n) % n;
    else return -1;
}
//求解模线性方程ax=b(mod n)
LL modular_liner_equation(LL a, LL b, LL n) {
    LL x, y, x0, d;
    extend_gcd(a, n, x, y, d);
    if (b % d)//没有解
        return -1;
    x0 = (x * (b / d)) % n;//特解
    //for(int i=1;i<d;i++)
        //cout<<(x0+i*(n/d))%n<<endl;
    LL ans = x0, s = n / d;
    ans = (ans % s + s) % s;   //ans为最小整数解
    return ans;
}
int main() {
    LL a, b, c, x, y, d, n;
    scanf("%lld%lld%lld", &a, &b, &n);
    printf("%lld\n", gcd(a, b));
    extend_gcd(a, b, x, y, d);
    printf("%lld %lld %lld\n", x, y, d);
    printf("%lld\n", mod_reverse(a, n));
    // 输出ax + by = c 多组解
    scanf("%lld%lld%lld", &a, &b, &c);
    extend_gcd(a, b, x, y, d);
    printf("%lld %lld %lld\n", x, y, d);
    int k = c / d;
    x *= k; y *= k; // 这是真正的x, y的值
    int a0 = a / d, b0 = b / d;
    int x1, x2, y1, y2;
    x1 = y1 = -100;//边界
    x2 = y2 = 100;
    for (int i = -10; i <= 10; i++) { //一个可能的倍数范围
        if (x + i * b0 < x1 || x + i * b0 > x2 || y - i * a0 < y1 || y - i * a0 > y2)
            continue;
        if (a * (x + i * b0) + b * (y - i * a0) == c) {
            printf("%lld %lld\n", x + i * b0, y - i * a0);
        }
    }
    //求解模线性方程
    printf("%lld\n", modular_liner_equation(2, 2, 6));
    return 0;
}
