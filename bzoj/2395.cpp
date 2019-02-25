#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 10000 + 10;
struct E { int u, v; ll a, b, c; } e[N];
struct P { ll x, y; P(ll x = 0, ll y = 0) : x(x), y(y) { } } ans, mnA, mnB;
bool operator < (P a, P b) {
    ll A = a.x * a.y, B = b.x * b.y;
    return A == B ? a.x < b.x : A < B;
}
P operator - (P a, P b) {
    return P(a.x - b.x, a.y - b.y);
}
ll operator * (P a, P b) {
    return a.x * b.y - b.x * a.y;
}

int n, m, fa[N]; int get(int x) { return x == fa[x] ? x : fa[x] = get(fa[x]); }

P kru() {
    for(int i = 1 ; i <= n ; ++ i) fa[i] = i;
    P res;
    for(int i = 1 ; i <= m ; ++ i) {
        int u = get(e[i].u), v = get(e[i].v);
        if(u != v) {
            fa[u] = v;
            res.x += e[i].a;
            res.y += e[i].b;
        }
    }
    ans = min(ans, res);
    return res;
}

bool cmpA(E a, E b) { return a.a < b.a; }
bool cmpB(E a, E b) { return a.b < b.b; }
bool cmpC(E a, E b) { return a.c < b.c; }

void sol(P A, P B) {
    for(int i = 1 ; i <= m ; ++ i) e[i].c = e[i].b * (A.x - B.x) + e[i].a * (B.y - A.y);
    sort(e + 1, e + 1 + m, cmpC);
    P C = kru();
    if((B - A) * (C - A) <= 0) return ;
    sol(A, C), sol(C, B);
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= m ; ++ i) {
        scanf("%d%d%lld%lld", &e[i].u, &e[i].v, &e[i].a, &e[i].b);
        ++ e[i].u, ++ e[i].v;
    }
    sort(e + 1, e + 1 + m, cmpA), mnA = kru(), ans = mnA;
    sort(e + 1, e + 1 + m, cmpB), mnB = kru();
    sol(mnB, mnA);
    printf("%lld %lld\n", ans.x, ans.y);
}
