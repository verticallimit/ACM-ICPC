#include <stdio.h>
#define  mod 2333

int fac(int x) {
    if (x == 0) return 1;
    else return x * fac(x - 1) % mod;
}

int main() {
    int n;
    while (scanf("%d", &n) != EOF) {
        int ans = fac(n) % mod;
        printf("%d\n", ans);
    }
    return 0;
}
