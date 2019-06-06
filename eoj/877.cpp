#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 5e5 + 10;

int n, m;

int tot = 1;
int rt = 1;
map<int, int> ch[N];
set<int> st[N];
ll val[N], cur;
ll ans;
void ins(int u, int pos) {
    ll l = pos + 1, r = n - pos;
    auto it = st[u].insert(pos).first;
    if(it != st[u].begin()) {
        l = pos - *prev(it);
    }
    if(next(it) != st[u].end()) {
        r = *next(it) - pos;
    }
    val[u] += l * r;
    cur += l * r;
}
int merge(int x, int y) {
    if(!x || !y) {
        return x | y;
    }
    if(ch[x].size() < ch[y].size()) {
        swap(x, y);
    }
    for(auto t: ch[y]) {
        ch[x][t.first] = merge(ch[x][t.first], t.second);
    }
    if(st[x].size() < st[y].size()) {
        swap(val[x], val[y]);
        swap(st[x], st[y]);
    }
    for(int pos: st[y]) {
        ins(x, pos);
    }
    cur -= val[y];
    return x;
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 0 ; i < n ; ++ i) {
        int u = rt;
        for(int j = 0 ; j < m ; ++ j) {
            int x; scanf("%d", &x);
            if(!ch[u][x]) {
                ch[u][x] = ++ tot;
            }
            u = ch[u][x];
            ins(u, i);
        }
    }
    ans = cur;
    for(int i = 1 ; i < m ; ++ i) {
        int nr = 0;
        for(auto t: ch[rt]) {
            nr = merge(nr, t.second);
        }
        rt = nr;
        cur -= val[rt];
        ans += cur;
    }
    printf("%lld\n", ans);
}
