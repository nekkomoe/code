#include <bits/stdc++.h>

using namespace std;

const int N = 15;

typedef unsigned long long ull;

map<ull, int> mp;

int a[N][N], b[N][N], h[N], n, m;

inline ull gethash() {
    ull res = 0;
    for(int i = 1 ; i <= n ; ++ i) res = res * 12 + h[i];
    return res;
}

inline int getcnt() {
    int res = 0;
    for(int i = 1 ; i <= n ; ++ i) res += h[i];
    return res & 1;
}

int dfs(ull state) {
    if(mp.find(state) != mp.end()) return mp[state];
    ull x = state;
    for(int i = n ; i ; -- i) h[i] = x % 12, x /= 12;
    int ty = getcnt(), res = 0x3f3f3f3f * (ty ? 1 : -1);
    for(int i = 1 ; i <= n ; ++ i) {
        if(h[i - 1] > h[i]) {
            ++ h[i];
            ull hs = gethash();
            res = ty ? min(res, dfs(hs) - b[i][h[i]]) : max(res, dfs(hs) + a[i][h[i]]);
            -- h[i];
        }
    }
    return mp[state] = res;
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 1 ; j <= m ; ++ j) {
            scanf("%d", &a[i][j]);
        }
    }
    h[0] = m;
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 1 ; j <= m ; ++ j) {
            scanf("%d", &b[i][j]);
        }
        h[i] = m;
    }
    mp[gethash()] = 0;
    printf("%d\n", dfs(0));
}
