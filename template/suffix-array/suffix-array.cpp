#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 20000;

int n, sa[N], rk[N], h[N], x[N], y[N], tmp[N], a[N], b[N];

char s[N];

int main() {
    scanf("%d%s", &n, s + 1);
    for(int i = 1 ; i <= n ; ++ i) ++ x[s[i]];
    for(int i = 1 ; i <= 256 ; ++ i) x[i] += x[i - 1];
    for(int i = n ; i ; -- i) sa[x[s[i]] --] = i;
    for(int i = 1 ; i <= n ; ++ i) x[s[i]] = 0;
    rk[sa[1]] = 1;
    for(int i = 2 ; i <= n ; ++ i) rk[sa[i]] = rk[sa[i - 1]] + (s[sa[i]] != s[sa[i - 1]]);
    for(int k = 1 ; rk[sa[n]] < n ; k <<= 1) {
        for(int i = 1 ; i <= n ; ++ i) x[i] = y[i] = 0;
        for(int i = 1 ; i <= n ; ++ i) ++ x[a[i] = rk[i]], ++ y[b[i] = i + k <= n ? rk[i + k] : 0];
        for(int i = 1 ; i <= n ; ++ i) x[i] += x[i - 1], y[i] += y[i - 1];
        for(int i = n ; i ; -- i) tmp[y[b[i]] --] = i;
        for(int i = n ; i ; -- i) sa[x[a[tmp[i]]] --] = tmp[i];
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
