#include <bits/stdc++.h>
using namespace std;
int fa[110];
vector<pair<int, int> > col[20];
int n, m, s;
int get(int x) {
    return x == fa[x] ? x : fa[x] = get(fa[x]);
}
void rebuild(vector<pair<int, int> > &pak) {
    auto tmp = pak; pak.clear();
    for(int i = 1 ; i <= n ; ++ i) {
        fa[i] = i;
    }
    for(auto e: tmp) {
        int u = get(e.first), v = get(e.second);
        if(u != v) {
            fa[u] = v;
            pak.emplace_back(e);
        }
    }
}
void runprog() {
    scanf("%d%d%d", &n, &m, &s);

//    assert(1 <= n && n <= 10 && 1 <= m && m <= 10); // 10%
//    assert(1 <= n && n <= 100 && 1 <= m && m <= 100 && 1 <= s && s <= 12); // 40%
//    assert(1 <= n && n <= 100 && 1 <= m && m <= int(1e5) && 1 <= s && s <= 6); // ano 20%
    assert(1 <= n && n <= 100 && 1 <= m && m <= int(1e5) && 1 <= s && s <= 12); // 100%

    for(int i = 1 ; i <= s ; ++ i) {
        col[i].clear();
    }
    for(int i = 1, u, v, c ; i <= m ; ++ i) {
        scanf("%d%d%d", &u, &v, &c);
        assert(1 <= c && c <= s);
        col[c].emplace_back(u, v);
    }

    for(int i = 1 ; i <= s ; ++ i) {
        rebuild(col[i]);
    }

    int ans = s;
    for(int t = 0 ; t < (1 << s) ; ++ t) {
        for(int i = 1 ; i <= n ; ++ i) {
            fa[i] = i;
        }
        int cnt = 0;
        for(int i = 1 ; i <= s ; ++ i) {
            if((t >> (i - 1)) & 1) {
                ++ cnt;
                for(auto e: col[i]) {
                    int u = get(e.first), v = get(e.second);
                    if(u != v) {
                        fa[u] = v;
                    }
                }
            }
        }
        for(int i = 1 ; i <= n ; ++ i) {
            if(get(i) != get(1)) {
                cnt = -1;
                break;
            }
        }
        if(cnt != -1) {
            ans = min(ans, cnt);
        }
    }
    printf("%d\n", ans);
}

int main() {
    int t; scanf("%d", &t);
    assert(1 <= t && t <= 5);
    while(t --) {
        runprog();
    }
}

