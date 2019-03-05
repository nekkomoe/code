#include "bits/stdc++.h"

using namespace std;

const int N = 1e6 + 10;

int sa[N], rk[N], h[N], x[N], y[N], a[N], b[N], tmp[N], n;

char s[N];

void build_sa() {
    memset(x, 0, sizeof x);
    scanf("%s", s + 1);
    n = strlen(s + 1);
    for(int i = 1 ; i <= n ; ++ i) x[s[i]] ++;
    for(int i = 1 ; i <= 256 ; ++ i) x[i] += x[i - 1];
    for(int i = n ; i >= 1 ; -- i) sa[x[s[i]] --] = i;
    for(int i = 0 ; i <= 256 ; ++ i) x[i] = 0;
    rk[sa[1]] = 1;
    for(int i = 2 ; i <= n ; ++ i) rk[sa[i]] = rk[sa[i - 1]] + (s[sa[i]] != s[sa[i - 1]]);
    for(int k = 1 ; rk[sa[n]] < n ; k <<= 1) {
        for(int i = 1 ; i <= n ; ++ i) x[i] = y[i] = 0;
        for(int i = 1 ; i <= n ; ++ i) x[a[i] = rk[i]] ++, y[b[i] = i + k > n ? 0 : rk[i + k]] ++;
        for(int i = 1 ; i <= n ; ++ i) x[i] += x[i - 1], y[i] += y[i - 1];
        for(int i = n ; i >= 1 ; -- i) tmp[y[b[i]] --] = i;
        for(int i = n ; i >= 1 ; -- i) sa[x[a[tmp[i]]] --] = tmp[i];
        rk[sa[1]] = 1;
        for(int i = 2 ; i <= n ; ++ i) rk[sa[i]] = rk[sa[i - 1]] + (a[sa[i]] != a[sa[i - 1]] || b[sa[i]] != b[sa[i - 1]]);
    }

    h[1] = 0;
    for(int k = 0, i = 1, p ; i <= n ; ++ i) {
        if(rk[i] == 1) continue;
        if(k) -- k;
        p = sa[rk[i] - 1];
        while(i + k <= n && p + k <= n && s[i + k] == s[p + k]) ++ k;
        h[rk[i]] = k;
    }
}

int lg[N];

int mn[N][22];

int getmin(int a, int b) {
    return h[a] < h[b] ? a : b;
}

int ask(int l, int r) {
    int k = lg[r - l + 1];
    return getmin(mn[l][k], mn[r - (1 << k) + 1][k]);
}

double sol(int l, int r) {
    if(l == r) {
        return n - sa[l] + 1;
    } else {
        int pos = ask(l + 1, r);
        double L = sol(l, pos - 1), R = sol(pos, r), ht = h[pos];
        double x = (R - ht) / (L + R - 2 * ht);
        return L * x + ht * (1 - x);
    }
}

void runprog() {
    build_sa();
    for(int i = 1 ; i <= n ; ++ i) {
        mn[i][0] = i;
    }
    for(int j = 1 ; j <= 20 ; ++ j) {
        for(int i = 1 ; i + (1 << j) - 1 <= n ; ++ i) {
            mn[i][j] = getmin(mn[i][j - 1], mn[i + (1 << (j - 1))][j - 1]);
        }
    }
    printf("%.10lf\n", sol(1, n));
}

int main() {
    for(int i = 2 ; i < N ; ++ i) {
        lg[i] = lg[i >> 1] + 1;
    }
    int T; scanf("%d", &T);
    while(T --) {
        runprog();
    }
}
