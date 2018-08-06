#include <cstdio>
#include <queue>
using std :: queue;
const int N = 2000010;
typedef long long ll;
int n;
ll s[N], f[N], g[N], inq[N];
int head[N], to[N], rest[N], tot;
queue<int> q;
void add(int u, int v) {
    ++ tot;
    to[tot] = v;
    rest[tot] = head[u];
    head[u] = tot;
}
int main() {
    scanf("%d", &n);
    for(int i = 1, t ; i <= n ; ++ i) {
        scanf("%lld%lld%d", &s[i], &g[i], &t);
        for(int j = 1, x ; j <= t ; ++ j) {
            scanf("%d", &x);
            add(x, i);
        }
        q.push(i), inq[i] = 1;
    }
    for(int i = 1 ; i <= n ; ++ i) {
        f[i] += s[i];
        for(int j = head[i] ; j ; j = rest[j]) {
            f[to[j]] += g[i];
        }
    }
    while(q.size()) {
        int u = q.front(); q.pop(); inq[u] = 0;
        if(f[u] >= g[u]) continue;
        for(int i = head[u] ; i ; i = rest[i]) {
            int v = to[i];
            f[v] -= g[u] - f[u];
            if(!inq[v]) q.push(v), inq[v] = 1;
        }
        g[u] = f[u];
    }
    printf("%lld\n", f[1]);
}

