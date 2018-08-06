#include <queue>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <iostream>
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

int lastid[N], con[N];

int main() {
    memset(head, -1, sizeof head);
    scanf("%d%d", &n, &m);
    s = n + 1, t = s + 1;  // s是超级源，t是超级汇
}
