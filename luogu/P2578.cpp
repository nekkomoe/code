// luogu-judger-enable-o2
#include <bits/stdc++.h>
using namespace std; typedef long long ll;
const int N = 362880 + 10;

struct STATE {
    int id;
    int a[3][3];
    // const int p = 149, x = 1e9 + 7; // 然而这个会有冲突
    const int p = 137, x = 998244853; // 神奇的不产生冲突
    void init() {
        id = 0;
        for(int i = 0 ; i < 3 ; ++ i)
            for(int j = 0 ; j < 3 ; ++ j)
                id = ((ll) id * p % x + a[i][j]) % x;
    }
} sta[N], nxt; int tot;

map<int, int> hs;
vector<int> g[N];
int a[9];

int trans[2][3][3][2] = {
    {
        { { 0, 0 }, { 0, 1 }, { 0, 2 } },
        { { 1, 2 }, { 1, 0 }, { 1, 1 } },
        { { 2, 0 }, { 2, 1 }, { 2, 2 } }
    },
    {
        { { 1, 0 }, { 0, 0 }, { 0, 1 } },
        { { 2, 0 }, { 1, 1 }, { 0, 2 } },
        { { 2, 1 }, { 2, 2 }, { 1, 2 } }
    }
};

int dis[N], que[N], from[N];

void print(int x) {
    if(!x) return ;
    print(from[x]);
    for(int i = 0 ; i < 3 ; ++ i, puts(""))
        for(int j = 0 ; j < 3 ; ++ j)
            printf("%d ", sta[x].a[i][j]);
    puts("");
}

int main() {
    for(int i = 0 ; i < 9 ; ++ i) a[i] = i;
    do {
        ++ tot;
        for(int i = 0 ; i < 9 ; ++ i)
            sta[tot].a[i / 3][i % 3] = a[i];
        sta[tot].init(), hs[sta[tot].id] = tot;
    } while(next_permutation(a, a + 9));
    tot = 0;
    do {
        ++ tot;
        for(int t = 0 ; t < 2 ; ++ t) {
            for(int i = 0 ; i < 3 ; ++ i) {
                for(int j = 0 ; j < 3 ; ++ j) {
                    nxt.a[i][j] = sta[tot].a[trans[t][i][j][0]][trans[t][i][j][1]];
                }
            }
            nxt.init(), g[tot].push_back(hs[nxt.id]);
        }
    } while(next_permutation(a, a + 9));

    STATE start;
    for(int i = 0 ; i < 3 ; ++ i)
        for(int j = 0 ; j < 3 ; ++ j)
            scanf("%d", &start.a[i][j]);
    start.init();

    memset(dis, -1, sizeof dis);
    int l = 1, r = 0;
    dis[que[++ r] = hs[start.id]] = 0;
    while(l <= r) {
        int u = que[l ++];
        if(u == 1) break;
        for(int v: g[u]) {
            if(dis[v] == -1) {
                dis[v] = dis[u] + 1;
                que[++ r] = v;
                from[v] = u;
            }
        }
    }
    if(dis[1] == -1) puts("UNSOLVABLE");
    else printf("%d\n", dis[1]), print(1);
}