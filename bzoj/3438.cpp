#include <bits/stdc++.h>

using namespace std;

const int N = 2e6 + 10;

typedef long long ll;

#define int ll

const int inf = 0x3f3f3f3f3f3f3f3fll;

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

int lala[N], sum;

void read(int &x) {
    x = 0;
    char c = getchar();
    while(!isdigit(c)) c = getchar();
    while(isdigit(c)) x = x * 10 + c - '0', c = getchar();
}

signed main() {
    
    memset(head, -1, sizeof head);
    
    read(n); s = N - 10, t = s + 1;
    
    for(int i = 1 ; i <= n ; ++ i) {
        int a; read(a);
        add(s, i, a);
        
        sum += a;
        
    }
    
    for(int i = 1 ; i <= n ; ++ i) {
        int b; read(b);
        add(i, t, b);
        
        sum += b;
        
    }
    
    read(m);
    
    for(int i = 1 ; i <= m ; ++ i) {
        int k; read(k);
        int p1 = n + i, p2 = n + m + i;
        
        int c1, c2;
        
        read(c1), read(c2);
        
        add(s, p1, c1), add(p2, t, c2);
        
        for(int j = 1, x ; j <= k ; ++ j) read(x), add(p1, x, inf), add(x, p2, inf);
        
        sum += c1 + c2;
        
    }
    
    printf("%lld\n", sum - sol());
    
}
