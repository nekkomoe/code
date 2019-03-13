#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 1e6 + 10;
const ll inf = 1ll << 53;

int n;
struct E { int v; ll w; };
vector<E> to[N];

struct T {
    ll val; int cnt;
}; ll ans;
bool operator < (T a, T b) {
    return a.val == b.val ? a.cnt > b.cnt : a.val < b.val;
}
T operator + (T a, T b) {
    return (T) { a.val + b.val, a.cnt + b.cnt };
}

T f[N][2];
ll cost;
void dfs(int u, int fa) {
    f[u][1] = (T) { -inf, 0x3f3f3f3f };
    f[u][0] = (T) { 0, 0 };
    for(E e: to[u]) {
        int v = e.v;
        ll w = e.w;
        if(v != fa) {
            dfs(v, u);
            T mx = max(f[v][0], f[v][1]);
            f[u][1] = max(f[u][1] + mx, f[u][0] + (T) { w + cost, 1 } + f[v][0]);
            f[u][0] = f[u][0] + mx;
        }
    }
}
int k;

int p[N][2];

void go(int u, int fa) {
    for(E e: to[u]) {
        int v = e.v;
        if(v != fa) {
            go(v, u);
            int mx = max(p[v][0], p[v][1]);
            p[u][1] = max(p[u][1] + mx, p[u][0] + p[v][0] + 1);
            p[u][0] += mx;
        }
    }
}

int main() {
    scanf("%d%d", &n, &k);
    for(int i = 1, u, v, w ; i < n ; ++ i) {
        scanf("%d%d%d", &u, &v, &w);
        to[u].push_back((E) { v, w });
        to[v].push_back((E) { u, w });
    }
    go(1, 0);
    if(max(p[1][0], p[1][1]) < k) {
        puts("Impossible");
        return 0;
    }
    ll l = -(ll) n * int(1e6), r = -l;
    while(l <= r) {
        cost = (l + r) >> 1;
        dfs(1, 0);
        T res = max(f[1][0], f[1][1]);
        if(res.cnt <= k) {
            l = cost + 1;
            ans = res.val - k * cost;
        } else {
            r = cost - 1;
        }
    }
    printf("%lld\n", ans);
}
