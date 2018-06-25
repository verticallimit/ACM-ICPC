#include<stdlib.h>
#include<stdio.h>
#include<string.h>
using namespace std;

const int maxn = 100 + 5;
int arr[maxn];

int main() {
    int n;
    while (scanf("%d", &n) != EOF) {
        for (int i = 0; i < n; i++)
            scanf("%d", &arr[i]);
        int ans = 999999;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (ans > abs(arr[i] + arr[j]))
                    ans = abs(arr[i] + arr[j]);
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
