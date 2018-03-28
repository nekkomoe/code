#include <cstdio>

typedef long long ll;

ll f[1000010];

int n, head[1000010], rest[1000000 * 2 + 10], to[1000000 * 2 + 10], tot;

int deep[1000010], sz[1000010];

void add(int u, int v) {
    to[++ tot] = v, rest[tot] = head[u], head[u] = tot;
}

void dfs(int u, int fa = 0) {
    sz[u] = 1;
    f[u] = deep[u];
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(v != fa) {
            deep[v] = deep[u] + 1, dfs(v, u);
            f[u] += f[v];
            sz[u] += sz[v];
        }
    }
}

void sol(int u, int fa = 0) {
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(v != fa) {
            f[v] = f[u] + n - 2 * sz[v];
            sol(v, u);
        }
    }
}

int main() {
    scanf("%d", &n);
    for(int i = 1, u, v ; i < n ; ++ i) {
        scanf("%d%d", &u, &v);
        add(u, v), add(v, u);
    }
    dfs(1), sol(1);
    int ans = 0;
    for(int i = 1 ; i <= n ; ++ i) if(f[i] > f[ans]) ans = i;
    printf("%d\n", ans);
}

