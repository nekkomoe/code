//tarjan_scc + dp

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <stack>
#include <vector>

using namespace std;

const int N = 500100;


struct E {
    int u, v;
};

vector<E> e;

int T, n, m, tot, clk, cnt, ans;

int head[N], rest[N], to[N], dfn[N], low[N], instack[N], id[N], vis[N], mem[N], scc[N];

stack<int> s;

void init() {
    e.clear();
    tot = clk = cnt = ans = 0;
    memset(head, 0, sizeof(head));
    memset(rest, 0, sizeof(rest));
    memset(to, 0, sizeof(to));
    memset(dfn, 0, sizeof(dfn));
    memset(low, 0, sizeof(low));
    memset(instack, 0, sizeof(instack));
    memset(id, 0, sizeof(id));
    memset(vis, 0, sizeof(vis));
    memset(mem, 0, sizeof(mem));
    memset(scc, 0, sizeof(scc));
    while(s.size()) s.pop();
}

void add(int u, int v) {
    tot ++;
    to[tot] = v;
    rest[tot] = head[u];
    head[u] = tot;
}

void dfs(int u) {
    low[u] = dfn[u] = ++ clk;
    s.push(u);
    instack[u] = 1;
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(!dfn[v]) {
            dfs(v);
            low[u] = min(low[u], low[v]);
        } else if(instack[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if(dfn[u] == low[u]) {
        int v;
        cnt ++;
        do {
            v = s.top();
            s.pop();
            instack[v] = 0;
            scc[cnt] ++;
            id[v] = cnt;
        } while(v != u);
    }
}

int f(int u) {
    if(vis[u]) {
        return mem[u];
    } else {
        vis[u] = 1;
        mem[u] = scc[u];
        for(int i = head[u] ; i ; i = rest[i]) {
            int v = to[i];
            mem[u] = max(mem[u], f(v) + scc[u]);
        }
        return mem[u];
    }
}

int main() {
    scanf("%d", &T);
    while(T --) {
        scanf("%d%d", &n, &m);
        init();
        for(int i = 1, u, v ; i <= m ; i ++) {
            scanf("%d%d", &u, &v);
            add(u, v);
            E a;
            a.u = u, a.v = v;
            e.push_back(a);
        }
        for(int i = 1 ; i <= n ; i ++ ) {
            if(!dfn[i]) {
                dfs(i);
            }
        }
        tot = 0;
        memset(head, 0, sizeof(head));
        for(int i = 0 ; i < e.size() ; i ++) {
            if(id[e[i].u] != id[e[i].v]) {
                add(id[e[i].u], id[e[i].v]);
            }
        }
        for(int i = 1 ; i <= cnt ; i ++) {
            ans = max(ans, f(i));
        }
        printf("%d\n", ans);
    }
}
