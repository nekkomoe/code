#include <bits/stdc++.h>

using namespace std;

const int N = 100010;

char s[N];

int n, lg[N], x[N], y[N], a[N], b[N], tmp[N], sa[N], rk[N], h[N][30];

void build() {
    for(int i = 2 ; i <= n ; ++ i) lg[i] = lg[i >> 1] + 1;
    for(int i = 1 ; i <= n ; ++ i) x[s[i]] ++;
    for(int i = 'a' ; i <= 'z' ; ++ i) x[i] += x[i - 1];
    for(int i = n ; i ; -- i) sa[x[s[i]] --] = i;
    for(int i = 'a' ; i <= 'z' ; ++ i) x[i] = 0;
    rk[sa[1]] = 1;
    for(int i = 2 ; i <= n ; ++ i) {
        rk[sa[i]] = rk[sa[i - 1]] + (s[sa[i]] != s[sa[i - 1]]);
    }
    for(int k = 1 ; rk[sa[n]] < n ; k <<= 1) {
        for(int i = 1 ; i <= n ; ++ i) x[i] = y[i] = 0;
        for(int i = 1 ; i <= n ; ++ i) x[a[i] = rk[i]] ++, y[b[i] = i + k <= n ? rk[i + k] : 0] ++;
        for(int i = 1 ; i <= n ; ++ i) x[i] += x[i - 1], y[i] += y[i - 1];
        for(int i = n ; i ; -- i) tmp[y[b[i]] --] = i;
        for(int i = n ; i ; -- i) sa[x[a[tmp[i]]] --] = tmp[i];
        rk[sa[1]] = 1;
        for(int i = 2 ; i <= n ; ++ i) {
            rk[sa[i]] = rk[sa[i - 1]] + (a[sa[i]] != a[sa[i - 1]] || b[sa[i]] != b[sa[i - 1]]);
        }
    }
    for(int i = 1, j = 0 ; i <= n ; ++ i) {
        if(j) -- j;
        while(s[i + j] == s[sa[rk[i] - 1] + j]) ++ j;
        h[rk[i]][0] = j;
    }
    for(int j = 1 ; j <= 25 ; ++ j) {
        for(int i = 1 ; i + (1 << j) - 1 <= n ; ++ i) {
            h[i][j] = min(h[i][j - 1], h[i + (1 << (j - 1))][j - 1]);
        }
    }
}

int lcp(int i, int j) {
    int l = min(rk[i], rk[j]) + 1, r = max(rk[i], rk[j]);
    int k = lg[r - l + 1];
    return min(h[l][k], h[r - (1 << k) + 1][k]);
}

int main() {
    n = strlen(s + scanf("%s", s + 1));
    build();
    int ans = 0;
    for(int L = 1 ; L <= n ; ++ L) {
        for(int i = 1 ; i + L <= n ; i += L) {
            int len = lcp(i, i + L);
            ans = max(ans, len / L + 1);
            if(i >= L - len % L) {
                ans = max(ans, lcp(i - L + len % L, i + len % L) / L + 1);
            }
        }
    }
    printf("%d\n", ans);
}
