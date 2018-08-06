#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 200010;

int size, sz[N], root, f[N] = { 0x3f3f3f }, ans, n, k;

int head[N], w[N * 2], rest[N * 2], to[N * 2], tot, ban[N];

int a[(int) 1e6 + 10];

void add(int u, int v, int w) {
    to[++ tot] = v, :: w[tot] = w, rest[tot] = head[u], head[u] = tot;
}

void getroot(int u, int fa) {
    sz[u] = 1, f[u] = 0;
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(v != fa && !ban[v]) {
            getroot(v, u);
            sz[u] += sz[v];
            f[u] = max(f[u], sz[v]);
        }
    }
    f[u] = max(f[u], size - sz[u]);
    if(f[u] < f[root]) root = u;
}

void dfs(int u, int fa, int w, int cnt) {
    if(w > k) return ;
    a[w] = min(a[w], cnt);
    if(w == k) ans = min(ans, cnt);
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(v != fa && !ban[v]) {
            dfs(v, u, w + :: w[i], cnt + 1);
        }
    }
}

void sol(int u, int fa, int w, int cnt) {
    if(w >= k) return ;
    ans = min(ans, a[k - w] + cnt);
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(v != fa && !ban[v]) {
            sol(v, u, w + :: w[i], cnt + 1);
        }
    }
}

void reset(int u, int fa, int w) {
    if(w > k) return ;
    a[w] = f[0];
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(v != fa && !ban[v]) {
            reset(v, u, w + :: w[i]);
        }
    }
}

void dfs(int u) {
    ban[u] = 1;
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(!ban[v]) {
            sol(v, u, w[i], 1);
            dfs(v, u, w[i], 1);
        }
    }
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(!ban[v]) {
            reset(v, u, w[i]);
        }
    }
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(!ban[v]) {
            root = 0, size = sz[v], getroot(v, u), dfs(root);
        }
    }
}

int main() {
    memset(a, 0x3f, sizeof a);
    ans = f[0];
    scanf("%d%d", &n, &k);
    for(int i = 1, u, v, w ; i < n ; ++ i) {
        scanf("%d%d%d", &u, &v, &w); u ++, v ++;
        add(u, v, w), add(v, u, w);
    }
    size = n, getroot(1, 0), dfs(root);
    printf("%d\n", ans == f[0] ? -1 : ans);
}

