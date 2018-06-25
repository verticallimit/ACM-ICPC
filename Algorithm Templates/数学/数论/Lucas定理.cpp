A、B是非负整数，p是质数。AB写成p进制：A=a[n]a[n-1]...a[0]，B=b[n]b[n-1]...b[0]。
则组合数C(A,B)与C(a[n],b[n])*C(a[n-1],b[n-1])*...*C(a[0],b[0]) modp同余
即：Lucas(n,m,p)=c(n%p,m%p)*Lucas(n/p,m/p,p)

对于大组合数取模，n,m不大于10^5的话，用逆元的方法，可以解决。对于n,m大于10^5的话，那么要求p<10^5，这样就是Lucas定理了，将n,m转化到10^5以内解。

推广：奇偶性质（联系2进制分析） 0C1=1 0C0=1C0=1C1=1
注：14年上海网络赛B题也是一个Lucas定理的应用
long long Lucas(long long a, long long k, long long p) {
//求C(n,m)%p p最大为10^5。a,b可以很大！
    long long re = 1;
    while (a && k) {
        long long aa = a % p;
        long long bb = k % p;
        if (aa < bb) return 0; //C(aa,bb) 表示 在aa里面取bb个，取法为0
        //由于p是素数，所以 a / b % p ，b 对于 mod a 肯定存在逆元
        re = re * fact[aa] * mod_pow(fact[bb] * fact[aa-bb] % p, p - 2, p) % p;
        //这儿的求逆不可先处理
        a /= p;
        k /= p;
    }
    return re;
}  
