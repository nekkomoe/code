#include "bits/stdc++.h"
using namespace std;

const int N = 1e5 + 10;

int fa[N], sum, n, m, need, tot, ans;

struct E {
    int u, v, col, w;
} e[N];

bool operator < (E p, E t) {
    return p.w == t.w ? p.col < t.col : p.w < t.w;
}

int get(int x) { return x == fa[x] ? x : fa[x] = get(fa[x]); }

bool check(int mid) {
    tot = sum = 0;
    for(int i = 1 ; i <= n ; ++ i) fa[i] = i;
    for(int i = 1 ; i <= m ; ++ i) e[i].w += mid * !e[i].col;
    sort(e + 1, e + 1 + m);
    for(int i = 1 ; i <= m ; ++ i) {
        int u = e[i].u + 1, v = e[i].v + 1, col = e[i].col, w = e[i].w;
        if(get(u) != get(v)) {
            fa[get(u)] = get(v);
            sum += w;
            tot += !col;
        }
    }
    for(int i = 1 ; i <= m ; ++ i) e[i].w -= mid * !e[i].col;
    return tot >= need;
}

int main() {
    scanf("%d%d%d", &n, &m, &need);
    for(int i = 1 ; i <= m ; ++ i) scanf("%d%d%d%d", &e[i].u, &e[i].v, &e[i].w, &e[i].col);
    int l = -200, r = 200;
    while(l <= r) {
        int mid = (l + r) >> 1;
        if(check(mid)) l = mid + 1, ans = sum - need * mid;
        else r = mid - 1;
    }
    printf("%d\n", ans);
}

