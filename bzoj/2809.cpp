#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <queue>
 
using namespace std;
 
typedef long long ll;
 
const int N = 210000;
 
struct heap {
    ll sum;
    priority_queue<ll> q;
    void push(ll v) {sum += v; q.push(v);}
    void pop() {sum -= q.top(); q.pop();}
    ll top() {return q.top();}
    ll size() {return (ll)q.size();}
} *h[N], mem[N];
 
void merge(heap *a, heap *b) {
    while(b -> size()) {
        a -> push(b -> top());
        b -> pop();
    }
}
 
int n;
 
ll m, val[N], lead[N], rt, ans;
 
int head[N], rest[N], to[N], tot;
 
void add(int u, int v) {
    ++ tot;
    to[tot] = v;
    rest[tot] = head[u];
    head[u] = tot;
}
 
void dfs(int u, int fa) {
    h[u] -> push(val[u]);
    for(int i = head[u], v ; i ; i = rest[i]) {
        if((v = to[i]) != fa) {
            dfs(v, u);
            if(h[u] -> size() > h[v] -> size()) {
                merge(h[u], h[v]);
            } else {
                merge(h[v], h[u]);
                h[u] = h[v];
            }
        }
    }
    while(h[u] -> sum > m) h[u] -> pop();
    ans = max(ans, lead[u] * (ll)h[u] -> size());
}
 
int main() {
    scanf("%d%lld", &n, &m);
    for(int i = 1, fa ; i <= n ; ++ i) {
        h[i] = &mem[i];
        scanf("%d%lld%lld", &fa, &val[i], &lead[i]);
        if(fa == 0) rt = i;
        else add(fa, i), add(i, fa);
    }
    dfs(rt, 0);
   printf("%lld\n", ans);
}
