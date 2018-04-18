#include <bits/stdc++.h>

using namespace std;

const int N = 500000 * 2 + 10;

typedef long long ll;

typedef pair<int, int> p;

p a[N];

int n, m, head[N], rest[N], to[N], val[N], l[N], r[N];

ll ans;

void add(int u, int v) {
    static int tot = 0;
    to[++ tot] = v, rest[tot] = head[u], head[u] = tot;
}

void dfs(int u, int fa) {
    if(!rest[head[u]]) return ;
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(v != fa) dfs(v, u);
    }
    int cnt = 0;
    ll mn = 0x3f3f3f3f3f3f3f3fll, now, sz = 0, tmp = 0;
    ll sz_sum = 0, tmp_sum = 0;
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(v != fa) {
            a[cnt ++] = p(l[v], 0);
            a[cnt ++] = p(r[v], 1);
            sz ++;
            sz_sum += l[v];
        }
    }
    sort(a, a + cnt);
    for(int i = 0 ; i < cnt ; ++ i) {
        if(a[i].second) {
            tmp ++;
            tmp_sum += a[i].first;
        } else {
            sz --;
            sz_sum -= a[i].first;
        }
        now = sz_sum - sz * a[i].first + tmp * a[i].first - tmp_sum;
        if(now < mn) mn = now, l[u] = a[i].first;
        if(now == mn) r[u] = a[i].first;
    }
    ans += mn;
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1, u, v ; i < n ; ++ i) {
        scanf("%d%d", &u, &v);
        add(u, v), add(v, u);
    }
    for(int i = 1 ; i <= m ; ++ i) {
        scanf("%d", &val[i]);
        l[i] = r[i] = val[i];
    }
    if(n == m) {
        for(int i = 1 ; i <= n ; ++ i) for(int j = head[i] ; j ; j = rest[j]) ans += abs(val[i] - val[to[j]]);
        printf("%lld\n", ans / 2);
    } else {
        dfs(n, 0);
        printf("%lld\n", ans);
    }
}
