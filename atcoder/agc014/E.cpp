#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 5e5 + 10;
int n;
queue<pair<int, int> > q;
int fa[N];
int get(int x) { return x == fa[x] ? x : fa[x] = get(fa[x]); }
set<int> g[N];

pair<int, int> gid(int x, int y) {
    if(x > y) swap(x, y);
    return make_pair(x, y);
}
map<pair<int, int>, int> cnt;

void lk(int u, int v) {
    g[u].emplace(v);
    g[v].emplace(u);
    int cur = ++ cnt[gid(u, v)];
    if(cur == 2) {
        q.emplace(u, v);
    } else if(cur == 3) {
        puts("NO");
        exit(0);
    }
}

int main() {
    scanf("%d", &n);
    for(int i = 1, u, v ; i <= 2 * (n - 1) ; ++ i) {
        scanf("%d%d", &u, &v);
        lk(u, v);
    }
    for(int i = 1 ; i <= n ; ++ i) {
        fa[i] = i;
    }
    for(int i = 1 ; i < n ; ++ i) {
        if(q.empty()) return puts("NO"), 0;
        int x = get(q.front().first), y = get(q.front().second);
        q.pop();
        if(g[x].size() > g[y].size()) {
            swap(x, y);
        }
        fa[x] = y;
        cnt.erase(gid(x, y));
        g[y].erase(x);
        g[x].erase(y);
        for(auto z: g[x]) {
            z = get(z);
            if(z == y) continue;
            cnt.erase(gid(x, z));
            lk(z, y);
            g[z].erase(x);
            g[x].erase(z);
        }
    }
    puts("YES");
}
