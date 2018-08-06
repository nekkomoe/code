// 构造 xor 位运算 数学

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

const int pw1 = 1 << 17;

const int pw2 = 1 << 18;

int n, x, ans;

int main() {
    scanf("%d%d", &n, &x);
    if(n == 1) {
        printf("YES\n%d\n", x);
    } else if(n == 2 && x == 0) {
        printf("NO\n");
    } else if(n == 2) {
        printf("YES\n%d %d\n", 0, x);
    } else {
        puts("YES");
        for(int i = 1 ; i <= n - 3 ; i ++) {
            printf("%d ", i);
            ans ^= i;
        }
        if(ans == x) {
            printf("%d %d %d", pw1, pw2, pw1 ^ pw2);
        } else {
            printf("%d %d %d", pw1, pw1 ^ (ans ^ x), 0);
        }
    }
}
