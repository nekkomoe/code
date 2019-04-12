// luogu-judger-enable-o2
#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
 
const int N = 2e5 + 10;
 
int head[N], rest[N], to[N], tot, a[N];
multiset<int> mem[N];
 
void add(int u, int v) {
    to[++ tot] = v, rest[tot] = head[u], head[u] = tot;
}
 
int p[N], n;
 
void merge(int x, int y) {
    // y -> x
    // mem[x] must not empty
 
    vector<int> tmp, way;
    for(multiset<int> :: iterator it = mem[y].begin() ; it != mem[y].end() ; ++ it) {
        way.push_back(*it);
    }
    reverse(way.begin(), way.end());
    for(int t = 0 ; t < way.size() ; ++ t) {
        int k = way[t];
        multiset<int> :: iterator it = mem[x].lower_bound(k);
        if(it != mem[x].end()) {
            tmp.push_back(*it);
            mem[x].erase(it);
        } else {
            tmp.push_back(k);
            if(it != mem[x].begin()) {
                -- it;
                mem[x].erase(it);
            }
        }
    }
    for(int t = 0 ; t < tmp.size() ; ++ t) {
        int k = tmp[t];
        mem[x].insert(k);
    }
     
    mem[y].clear();
}
 
void dfs(int u) {
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        dfs(v);
        if(mem[p[u]].size() < mem[p[v]].size()) {
            swap(p[u], p[v]);
        }
        merge(p[u], p[v]);
    }
    mem[p[u]].insert(a[u]);
}
 
int main() {
     
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &a[i]);
        p[i] = i;
    }
    for(int i = 2 ; i <= n ; ++ i) {
        int fa; scanf("%d", &fa);
        add(fa, i);
    }
    dfs(1);
     
    ll ans = 0;
    for(multiset<int> :: iterator it = mem[p[1]].begin() ; it != mem[p[1]].end() ; ++ it) {
        int x = *it;
        ans += x;
    }
    printf("%lld\n", ans);
}
