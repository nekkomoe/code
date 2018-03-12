#include <bits/stdc++.h>

using namespace std;

const int N = 100010;

int n, m, s, t;

queue<int> q;

int dis[N];

int head[N], rest[N], to[N], flow[N], tot;

void add_sub(int u, int v, int f) {
    to[tot] = v;
    flow[tot] = f;
    rest[tot] = head[u];
    head[u] = tot ++;
}

void add(int u, int v, int f) {
    add_sub(u, v, f);
    add_sub(v, u, 0);
}

bool bfs() {
    memset(dis, -1, sizeof dis);
    q.push(s);
    dis[s] = 0;
    while(q.size()) {
        int u = q.front();
        q.pop();
        for(int i = head[u] ; ~i ; i = rest[i]) {
            int v = to[i];
            if(flow[i] && dis[v] == -1) {
                dis[v] = dis[u] + 1;
                q.push(v);
            }
        }
    }
    return dis[t] != -1;
}

int dfs(int u, int fw) {
    if(u == t || !fw) return fw;
    int use = 0;
    for(int i = head[u] ; ~i ; i = rest[i]) {
        int v = to[i];
        if(flow[i] && dis[v] == dis[u] + 1) {
            int a = dfs(v, min(flow[i], fw - use));
            flow[i] -= a;
            flow[i ^ 1] += a;
            use += a;
            if(use == fw) break;
        }
    }
    if(!use) dis[u] = -1;
    return use;
}

int sol() {
    int ret = 0;
    while(bfs()) ret += dfs(s, 0x3f3f3f3f);
    return ret;
}

int main() {
    memset(head, -1, sizeof head);
    
    int k; scanf("%d%d", &k, &n); s = n + k + 1, t = s + 1;
    for(int i = 1 ; i <= k ; ++ i) {
        int x; scanf("%d", &x); m += x;
        add(s, i + n, x);
    }
    for(int i = 1 ; i <= n ; ++ i) {
        int p; scanf("%d", &p);
        for(int j = 1 ; j <= p ; ++ j) {
            int x; scanf("%d", &x);
            add(x + n, i, 1);
        }
        add(i, t, 1);
    }
    if(sol() == m) {
        vector<int> id[k + 10];
        for(int i = n + 1 ; i <= n + k ; ++ i) {
            for(int j = head[i] ; ~ j ; j = rest[j]) {
                if(!flow[j] && to[j] <= n) {
                    id[i - n].push_back(to[j]);
                }
            }
        }
        for(int i = 1 ; i <= k ; ++ i) {
            printf("%d: ", i);
            for(int j = 0 ; j < id[i].size() ; ++ j) {
                printf("%d ", id[i][j]);
            }
            puts("");
        }
    } else puts("No Solution!");
}
