#include "bits/stdc++.h"
using namespace std;
const int N = 1e6 + 10;
int cnt[N], n, m;
void ns() { puts("-1"); exit(0); }
int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i < n ; ++ i) cnt[i] = 1, -- m;
    if(m < 0) ns();
    if(m) -- m, cnt[n] = 1;
    for(int i = 1 ; i <= n ; ++ i) if(m) -- m, cnt[i] = 2;
    cnt[0] = m;
    if(cnt[0] > 2) ns();
    for(int i = 1 ; i <= cnt[0] ; ++ i) putchar('1');
    for(int i = 1 ; i <= n ; ++ i) {
        putchar('0');
        for(int j = 1 ; j <= cnt[i] ; ++ j) putchar('1');
    }
    puts("");
}
