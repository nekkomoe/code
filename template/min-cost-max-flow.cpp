#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <queue>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1000010;

int head[N], rest[N], from[N], to[N], flow[N], cost[N], tot;

void add_sub(int u, int v, int f, int c) {
    from[tot] = u;
    to[tot] = v;
    flow[tot] = f;
    cost[tot] = c;
    rest[tot] = head[u];
    head[u] = tot ++;
}

void add(int u, int v, int f, int c) {
    add_sub(u, v, f, c);
    add_sub(v, u, 0, -c);
}

typedef long long ll;

ll dis[N];

int inq[N], pre[N];

int n, m, s, t;

queue<int> q;

bool spfa() {
    memset(dis, 0x3f, sizeof dis);
    memset(pre, -1, sizeof pre);
    q.push(s);
    dis[s] = 0;
    inq[s] = 1;
    while(q.size()) {
        int u = q.front();
        q.pop();
        inq[u] = 0;
        for(int i = head[u] ; ~ i ; i = rest[i]) {
            int v = to[i];
            if(dis[v] > dis[u] + cost[i] && flow[i]) {
                dis[v] = dis[u] + cost[i];
                pre[v] = i;
                if(!inq[v]) {
                    q.push(v);
                    inq[v] = 1;
                }
            }
        }
    }
    return dis[t] < 0x3f3f3f3f3f3f3f3fLL;
}

ll sol() {
    ll retf = 0, retc = 0;
    while(spfa()) {
        int f = 0x3f3f3f3f;
        for(int i = pre[t] ; ~i ; i = pre[from[i]]) f = min(f, flow[i]);
        for(int i = pre[t] ; ~i ; i = pre[from[i]]) flow[i] -= f, flow[i ^ 1] += f;
        retf += f;
        retc += f * dis[t];
    }
    return retc;
}

int main() {
    memset(head, -1, sizeof head);
    scanf("%d%d", &n, &m);
    s = n + 1, t = s + 1;  // s是超级源，t是超级汇
}
