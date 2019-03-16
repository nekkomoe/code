#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

// 竖着长度：6 * k
// 竖着宽度：1 * k
// 空格宽度：4 * k

// k 4k k 4k k

// k 9k k

void neko_put(int k, char c) {
    while(k --) {
        putchar(c);
    }
}

int main() {
    int k; scanf("%d", &k);
    for(int i = 1 ; i <= 6 * k ; ++ i) {
        neko_put(k, '*');
        neko_put(4 * k, ' ');
        neko_put(k, '*');
        neko_put(4 * k, ' ');
        neko_put(k, '*');
        puts("");
    }
    for(int i = 1 ; i <= k ; ++ i) {
        neko_put(k, ' ');
        neko_put(9 * k, '*');
        neko_put(k, ' ');
        puts("");
    }
}
