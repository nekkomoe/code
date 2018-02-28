#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 20000;

int n, sa[N], rk[N], h[N], cnta[N], cntb[N], tmp[N], a[N], b[N];

char s[N];

int main() {
    scanf("%d%s", &n, s + 1);
    for(int i = 1 ; i <= n ; ++ i) ++ cnta[s[i]];
    for(int i = 1 ; i <= 256 ; ++ i) cnta[i] += cnta[i - 1];
    for(int i = n ; i ; -- i) sa[cnta[s[i]] --] = i;
    for(int i = 1 ; i <= n ; ++ i) cnta[s[i]] = 0;
    rk[sa[1]] = 1;
    for(int i = 2 ; i <= n ; ++ i) rk[sa[i]] = rk[sa[i - 1]] + (s[sa[i]] != s[sa[i - 1]]);
    for(int k = 1 ; rk[sa[n]] < n ; k <<= 1) {
        for(int i = 1 ; i <= n ; ++ i) cnta[i] = cntb[i] = 0;
        for(int i = 1 ; i <= n ; ++ i) ++ cnta[a[i] = rk[i]], ++ cntb[b[i] = i + k <= n ? rk[i + k] : 0];
        for(int i = 1 ; i <= n ; ++ i) cnta[i] += cnta[i - 1], cntb[i] += cntb[i - 1];
        for(int i = n ; i ; -- i) tmp[cntb[b[i]] --] = i;
        for(int i = n ; i ; -- i) sa[cnta[a[tmp[i]]] --] = tmp[i];
        rk[sa[1]] = 1;
        for(int i = 2 ; i <= n ; ++ i) rk[sa[i]] = rk[sa[i - 1]] + (a[sa[i]] != a[sa[i - 1]] || b[sa[i]] != b[sa[i - 1]]);
    }
    // 求height数组
    for(int i = 1, j = 0 ; i <= n ; ++ i) {
        if(j) -- j;
        while(s[i + j] == s[sa[rk[i] - 1] + j]) ++ j;
        h[rk[i]] = j;
    }
}
