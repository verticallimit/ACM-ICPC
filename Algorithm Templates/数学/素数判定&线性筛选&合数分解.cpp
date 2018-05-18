/*
素数判定 Miller-Rabin + 二次判定
费马小定理  a^p%p = a%p 推出 a^(p-1)%p = 1%p = 1 (p为素数)
二次探测定理 如果一个数字p是除2以外的素数那么对于方程 x^2%p = 1
它的解一定是 x = 1 或 x = p - 1
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<iostream>
#include<string.h>
#include<math.h>
#include<algorithm>
using namespace std;

//****************************************************************
// Miller_Rabin 算法进行素数测试
//速度快，而且可以判断 <2^63的数
//****************************************************************
const int S = 8;//随机算法判定次数，一般8-10次就够了
//计算 ret = (a*b)%c.   a,b都是long long的数，直接相乘可能溢出的
long long mult_mod(long long a, long long b, long long c) {
    a %= c;
    b %= c;
    long long ret = 0;
    long long tmp = a;
    while (b) {
        if (b & 1) {
            ret += tmp;
            if (ret > c) ret -= c; //直接取模慢的多
        }
        tmp <<= 1;
        if (tmp >= c) tmp -= c;
        b >>= 1;
    }
    return ret;
}
//计算 ret = (a^n)%mod
long long pow_mod(long long a, long long n, long long mod) {
    long long ret = 1;
    long long temp = a % mod;
    while (n) {
        if (n & 1) ret = mult_mod(ret, temp, mod);
        temp = mult_mod(temp, temp, mod);
        n >>= 1;
    }
    return ret;
}
//以a为基,n-1=x*2^t      a^(n-1)=1(mod n)  验证n是不是合数
//一定是合数返回true,不一定返回false
bool check(long long a, long long n, long long x, long long t) {
    long long ret = pow_mod(a, x, n);
    long long last = ret;
    for (int i = 1; i <= t; i++) {
        ret = mult_mod(ret, ret, n);
        if (ret == 1 && last != 1 && last != n-1) return true;//合数
        last = ret;
    }
    if (ret != 1) return true;
    return false;
}
// Miller_Rabin()算法素数判定
//是素数返回true.(可能是伪素数，但概率极小)
//合数返回false;
bool Miller_Rabin(long long n) {
    if (n < 2) return false;
    if (n == 2) return true;
    if ((n & 1) == 0) return false;//偶数
    long long x = n-1;
    long long t = 0;
    while ((x & 1) == 0) {x >>= 1; t++;}
    srand(time(NULL));
    for (int i = 0; i < S; i++) {
        long long a = rand() % (n - 1) + 1;//rand()需要stdlib.h头文件
        if (check(a, n, x, t))
            return false;//合数
    }
    return true;
}
//************************************************
//pollard_rho 算法进行质因数分解
//************************************************
long long factor[100];//质因数分解结果（刚返回时是无序的）
int tol;//质因数的个数。数组小标从0开始
long long gcd(long long a, long long b) {
    long long t;
    while (b) {
        t = a;
        a = b;
        b = t % b;
    }
    if (a >= 0) return a;
    else return -a;
}
//找出一个因子
long long Pollard_rho(long long x, long long c) {
    long long i = 1, k = 2;
    srand(time(NULL));
    long long x0 = rand() % (x - 1) + 1;
    long long y = x0;
    while (1) {
        i++;
        x0 = (mult_mod(x0, x0, x) + c) % x;
        long long d = gcd(y - x0, x);
        if (d != 1 && d != x) return d;
        if (y == x0) return x;
        if (i == k) {y = x0; k += k;}
    }
}
//对n进行素因子分解, 存入factor
void findfac(long long n,int k) {
    if (n == 1)  return;
    if (Miller_Rabin(n)) {
        factor[tol++] = n;
        return;
    }
    long long p = n;
    int c = k;
    while (p >= n)
        p = Pollard_rho(p, c--);//值变化，防止死循环k
    findfac(p, k);
    findfac(n / p, k);
}
int main() {
    int T;
    long long n;
    scanf("%d", &T);
    while (T--) {
        scanf("%I64d", &n);
        if (Miller_Rabin(n)) printf("Prime\n");
        else {
            tol = 0;
            findfac(n, 107);
            long long ans = factor[0];
            for (int i = 1; i < tol; i++)
              if (factor[i] < ans)
                 ans = min(ans, factor[i]);
            printf("%I64d\n", ans);
        }
    }
    return 0;
}

/*
素数线性筛选法 & 合数分解
*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
// 线性素数筛选  prime[0]存的是素数的个数
const int maxn = 1000000 + 5;
int prime[maxn];
void getPrime() {
    memset(prime, 0, sizeof(prime));
    for (int  i = 2; i <= maxn; i++) {
        if (!prime[i]) prime[++prime[0]] = i;
        for (int j = 1; j <= prime[0] && prime[j] * i <= maxn; j++) {
            prime[prime[j] * i] = 1;
            if (i % prime[j] == 0) break;
        }
    }
}
// 合数分解
long long factor[100][2];
int getFactors(long long x) {
    int fatCnt = 0;
    long long tmp = x;
    for (int i = 1; prime[i] <= tmp / prime[i]; i++) {
        factor[fatCnt][1] = 0;
        if (tmp % prime[i] == 0) {
            factor[fatCnt][0] = prime[i];
            while (tmp % prime[i] == 0) {
                factor[fatCnt][1]++;
                tmp /= prime[i];
            }
            fatCnt++;
        }
    }
    if (tmp != 1) {
        factor[fatCnt][0] = tmp;
        factor[fatCnt++][1] = 1;
    }
    return fatCnt;
}
int main() {
    getPrime();
    int n;
    scanf("%d", &n);
    int num = getFactors(n);
    for (int i = 0; i < num; i++)
        printf("%d ", factor[i][0]);
    printf("\n");
    return 0;
}
