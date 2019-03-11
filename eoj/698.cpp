#include "bits/stdc++.h"
using namespace std;
const int N = 3e5 + 10;
int n, q, k, a[N];
vector<int> g[N];

int fa[N][22], dep[N], sz[N];

void dfs(int u) {
    sz[u] = 1;
    dep[u] = dep[fa[u][0]] + 1;
    for(int i = 1 ; i <= 20 ; ++ i) {
        fa[u][i] = fa[fa[u][i - 1]][i - 1];
    }
    for(int v: g[u]) {
        if(v != fa[u][0]) {
            fa[v][0] = u;
            dfs(v);
            sz[u] += sz[v];
        }
    }
}

int getlca(int u, int v) {
    if(dep[u] < dep[v]) swap(u, v);
    for(int i = 20 ; ~ i ; -- i) {
        if(dep[fa[u][i]] >= dep[v]) {
            u = fa[u][i];
        }
    }
    if(u == v) return u;
    for(int i = 20 ; ~ i ; -- i) {
        if(fa[u][i] != fa[v][i]) {
            u = fa[u][i];
            v = fa[v][i];
        }
    }
    return fa[u][0];
}

int getdis(int i, int j) {
    return dep[i] + dep[j] - 2 * dep[getlca(i, j)];
}

int walk(int u, int dis) {
    for(int i = 20 ; ~ i ; -- i) {
        int len = dep[u] - dep[fa[u][i]];
        if(len <= dis) {
            dis -= len;
            u = fa[u][i];
        }
    }
    return u;
}

pair<int, int> getson(int u, int p) {
    int lca = getlca(u, p);
    if(u != lca) {
        p = fa[u][0];
        return make_pair(p, n - sz[u]);
    } else {
        for(int i = 20 ; ~ i ; -- i) {
            if(dep[fa[p][i]] > dep[u]) {
                p = fa[p][i];
            }
        }
        return make_pair(p, sz[p]);
    }
}

struct T {
    int dis, u, v;
};
bool operator < (T a, T b) {
    return a.dis < b.dis;
}

int getp(int len, int u, int v) {
    int lca = getlca(u, v);
    int dis = len / 2;
    int p = 0;
    if(dep[u] - dep[lca] >= dis) {
        p = walk(u, dis);
    } else {
        dis -= dep[u] - dep[lca];
        // lca -> v，走 dis 步
        p = walk(v, dep[v] - dep[lca] - dis);
    }
    return p;
}

void runprog() {
    scanf("%d", &k);
    for(int i = 1 ; i <= k ; ++ i) {
        scanf("%d", &a[i]);
    }
    if(k == 1) {
        printf("%d\n", n);
    } else {
        T neko = (T) { getdis(a[1], a[2]), a[1], a[2] };
        for(int i = 3 ; i <= k ; ++ i) {
            vector<T> cat;
            cat.push_back(neko);
            cat.push_back((T) { getdis(neko.u, a[i]), neko.u, a[i] });
            cat.push_back((T) { getdis(neko.v, a[i]), neko.v, a[i] });
            neko = *max_element(cat.begin(), cat.end());
        }
        int len = neko.dis;
        if(len & 1) {
            puts("0");
        } else {
            int p = getp(neko.dis, neko.u, neko.v);
            int tarlen = getdis(p, a[1]);
            vector<pair<int, int> > pak;
            for(int i = 1 ; i <= k ; ++ i) {
                if(getdis(p, a[i]) != tarlen) {
                    puts("0");
                    return ;
                }
                pak.push_back(getson(p, a[i]));
            }
            sort(pak.begin(), pak.end());
            pak.erase(unique(pak.begin(), pak.end()), pak.end());
            int sum = 0;
            for(int i = 0 ; i < pak.size() ; ++ i) {
                sum += pak[i].second;
            }
            printf("%d\n", n - sum);
        }
    }
}

int main() {
    scanf("%d%d", &n, &q);
    for(int i = 1, u, v ; i < n ; ++ i) {
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1);
    while(q --) {
        runprog();
    }
}
