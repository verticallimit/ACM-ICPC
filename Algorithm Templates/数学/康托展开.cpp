/*
康拓展开
X=a[n]*(n-1)!+a[n-1]*(n-2)!+...+a[i]*(i-1)!+...+a[1]*0!
其中a[i]为第i位是i往右中的数里 第几大的-1（比他小的有几个）
判断这个数在其各个数字全排列中从小到大排第几位
*/

#include<stdio.h>
#include<string.h>

typedef long long LL;
const int maxn = 15;
LL factory[maxn];
// 打表记录阶乘
void init() {
    factory[0] = 1, factory[1] = 1;
    for (int i = 2; i < maxn; ++i)
        factory[i] = i * factory[i - 1];
}
LL Contor(char str[],int n)
{
    LL ans = 0;
    for (int i = 0; i < n; ++i) {
        LL cnt = 0;
        for (int j = i + 1; j < n; ++j) {//查找可以用线段树优化
            if (str[j] < str[i]) cnt++;
        }
        ans += cnt * factory[n - i - 1];
    }
    return ans;
}
// 康拓展开逆运算  n个数字的排列中第k个排列是多少
void reverse_contor(int n, int k, char s[]) {
    int vis[maxn] = {0};
    k--;
    for (int i = 0; i < n; i++) {
        int t = k / factory[n - i - 1];
        int j;
        for (j = 1; j <= n; j++) {
            if (!vis[j]) {
                if (!t) break;
                t--;
            }
        }
        s[i] = '0' + j;
        vis[j] = 1;
        k %= factory[n - i - 1];
    }
}
int main()
{
    init();
    char s[20] = {0};
    scanf("%s",s);
    printf("%lld\n",Contor(s,strlen(s)));
    char str[20] = {0};
    reverse_contor(3, 2, str);
    printf("%s\n", str);
    return 0;
}
