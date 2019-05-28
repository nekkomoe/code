#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 10;

int w[N], n, m, x[N], y[N], fa[N];

int get(int x) {
    if(x == fa[x]) {
        return x;
    }
    int f = get(fa[x]);
    w[x] ^= w[fa[x]];
    return fa[x] = f;
}

void runprog() {
    int flag = 0;
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= n ; ++ i) {
        fa[i] = i, w[i] = 0;
    }
    for(int i = 1 ; i < n ; ++ i) {
        scanf("%d%d", &x[i], &y[i]);
    }
    for(int i = 1, u, v, c ; i <= m ; ++ i) {
        scanf("%d%d%d", &u, &v, &c);
        int fu = get(u), fv = get(v);
        if(fu != fv) {
            fa[fu] = fv;
            w[fu] = w[u] ^ w[v] ^ c;
        } else if(w[u] ^ w[v] ^ c) {
            flag = 1;
        }
    }
    if(flag) {
        puts("Impossible");
    } else {
        for(int i = 1 ; i <= n ; ++ i) {
            if(get(i) != get(1)) {
                puts("No");
                return ;
            }
        }
        ll mn = 0x3f3f3f3f3f3f3f3f, mx = 0;
        for(int i = 1 ; i < n ; ++ i) {
            ll c = w[x[i]] ^ w[y[i]];
            mn = min(mn, c);
            mx = max(mx, c);
        }
        printf("%lld %lld\n", mn, mx);
    }
}

int main() {
    int t; scanf("%d", &t);
    while(t --) {
        runprog();
    }
}
