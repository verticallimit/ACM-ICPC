#include <stdio.h>

int main() {
    int n, m;
    freopen("C:\\Users\\Administrator\\Desktop\\省赛题目\\A\\1.in", "r", stdin);
    freopen("C:\\Users\\Administrator\\Desktop\\省赛题目\\A\\1.out", "w", stdout);
    while (scanf("%d%d", &m, &n) != EOF) {
        if (m % (n + 1) == 0) {
            printf("none\n");
            continue;
        }
        if (m <= n) {
            printf("%d", m);
            for (int i = m + 1; i <= n; i++)
                printf(" %d", i);
            printf("\n");
            continue;
        }
        printf("%d\n", m % (n + 1));
    }
    return 0;
}
