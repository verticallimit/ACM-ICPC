// 错排问题
#include<iostream>
#include<stdio.h>
#include<string.h>
using namespace std;
long long int a[25];
long long int num[25][25];
void solve()
{
    memset(num,1,sizeof(num));
    a[1]=0;
    a[2]=1;
    a[3]=2;
    num[3][0]=1,num[3][1]=3,num[3][2]=3,num[3][3]=1;
    long long int sum=6;
    for(int i=4; i<=20; i++)
    {
        sum*=i;///当前的阶乘
        a[i]=sum;
        for(int j=1; j<i; j++)///减去1~i-1个全部放错，就是说i-1~1个放对的，（这里i也可以从2开始，因为a[1]=0,不过这样好理解）
        {
            num[i][j]=num[i-1][j]+num[i-1][j-1];
            a[i]=a[i]-a[j]*num[i][j];
        }
        a[i]-=1;///减去i个全部放对的
        num[i][1]=i;
        num[i][i]=1;
    }
}
int main()
{
    int n;
    solve();
    while(~scanf("%d",&n))
    {
        printf("%lld\n",a[n]);
    }
    return 0;
}

容斥定理一般使用二进制压缩来实现：给定一个数组a,求1到n的整数中至少能整除a中一个元素的数有几个
typedef long long ll;
int a[MAX_M];
int n, m;
void solve() {
    ll res = 0;
    for (int i = 1; i < (1 << m); i++) {
        int num = 0;
        for (int j = i; j != 0; j >>= 1) num += j & i; // i的二进制表示中1的数量
        ll lcm = 1;
        for (int j = 0; j < m; j++) {
            if (i >> j & 1) {
                lcm = lcm / gcd(lcm, a[j]) * a[j];
                // 如果lcm大于n，则n/lcm=0 因此在溢出之前break
                if (lcm > n) break;
            }
        }
        if (num % 2 == 0) res -= n / lcm;
        else res += n / lcm;
    }
    printf("%d\n", res);
}

鸽巢定理更多用于证明、比如求最近点对中枚举周围最多6个点便是使用鸽巢定理证明、

然而容斥定理需要枚举所有集合之间的组合情况、复杂度过高、可用莫比乌斯函数反演来优化、

f(n)=g(d) (d|n) <==> g(n)=u(n/d)*f(d) (d|n)
f(d)是周期为d的约数的字符串的个数、g(d)是周期恰好为d的字符串的个数
由于f(d)已经可以高效的求出了、因此可以由右边的式子推出g(n)

若n可以被除1以外的完全平方数整除 u(n)=0
否则设n的质因数的个数为k u(n)=(-1)^k

由于整数分解可以在O(sqrt(n))时间内完成、所以u(n)也是
如果使用埃氏筛法、可以在O(n)时间内求出1-n所有的u值


求所有的由a-z组成的(不一定要使用所有字母)长度为n的字符串中，没有周期性的字符串的个数。

// 把n的约数的莫比乌斯函数值用map的形式返回  O(sqrt(n))
map<int, int> moebius(int n) {
    map<int, int> res;
    vector<int> primes;
    // 枚举n的质因数
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            primes.push_back(i);
            while (n % i == 0) n /= i;
        }
    }
    if(n != 1)primes.push_back(n);
    int m = primes.size();
    for (int i = 0; i < (1 << m); i++) { // 虽然要执行2^m次、但是这不超过n的约数个数
        int mu = 1, d = 1;
        for (int j = 0; j < m; j++) {
            if (i >> j & 1) {
                mu *= -1;
                d *= primes[j];
            }
        }
        res[d] = mu;
    }
    return res;
}
const int MOD = 10009;
//输入
int n;
void solve() {
    int res = 0;
    map<int, int> mu = moebius(n);
    for (map<int, int>::iterator it = mu.begin(); it != mu.end(); ++it) {
        res += it->second * mod_pow(26, n / it->first, MOD);
        res = (res % MOD + MOD) % MOD;
    }
    printf("%d\n", res);
}
