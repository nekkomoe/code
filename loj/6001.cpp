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

vector<int> aaa[N];

int main() {
    memset(head, -1, sizeof head);
    scanf("%d%d", &m, &n), s = n + m + 1, t = s + 1;
    int sum = 0;
    for(int i = 1 ; i <= m ; ++ i) {
        int p; scanf("%d", &p);
        add(s, i, p), sum += p;
        int x, c;
        do {
            c = getchar();
            if(c == '\n' || c == '\r' || c == EOF) break;
            scanf("%d", &x);
            add(i, m + x, 0x3f3f3f3f);
            aaa[i].push_back(x);
        } while(c != '\n' || c != '\r' || c != EOF);
    }
    for(int i = 1 ; i <= n ; ++ i) {
        int x; scanf("%d", &x);
        add(m + i, t, x);
    }
    int ans = sum - sol();
    
    for(int i = 1 ; i <= m ; ++ i) {
        if(~dis[i]) {
            printf("%d ", i);
        }
    }
    
    puts("");
    
    for(int i = 1 ; i <= n ; ++ i) {
        if(~dis[i + m]) {
            printf("%d ", i);
        }
    }
    
    puts("");
    
    printf("%d\n", ans);
}
