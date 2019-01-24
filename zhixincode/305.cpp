#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 2010;

struct P {
    ll x, y;
} p[N];
P operator - (P a, P b) {
    return (P) { a.x - b.x, a.y - b.y };
}
ll operator * (P a, P b) {
    return a.x * b.y - b.x * a.y;
}
bool operator == (P a, P b) {
    return a.x == b.x && a.y == b.y;
}

int n, m;

struct Line {
    int u, v;
    P a, b, p[2];
} ln[N];

int ch_in(Line ln, P p) {

    if((p - ln.a) * (ln.b - ln.a)) return 0;

    return min(ln.a.x, ln.b.x) <= p.x && p.x <= max(ln.a.x, ln.b.x) && min(ln.a.y, ln.b.y) <= p.y && p.y <= max(ln.a.y, ln.b.y);
}

pair<ll, ll> getside(Line u, Line v) {
    pair<ll, ll> res;
    res.first = (u.b - u.a) * (v.a - u.a);
    res.second = (u.b - u.a) * (v.b - u.a);
    return res;
}

int check(Line u, Line v) {
    if(u.a == u.b || v.a == v.b) return 0;

    if(ch_in(u, v.p[0]) && ch_in(u, v.p[1])) return 1;
    if(ch_in(v, u.p[0]) && ch_in(v, u.p[1])) return 1;

    pair<ll, ll> tuv = getside(u, v), tvu = getside(v, u);

    if(tuv.first > 0 && tuv.second > 0) return 0;
    if(tuv.first < 0 && tuv.second < 0) return 0;

    if(tvu.first > 0 && tvu.second > 0) return 0;
    if(tvu.first < 0 && tvu.second < 0) return 0;

    if(tuv.first == 0 && tuv.second == 0 && tvu.first == 0 && tvu.second == 0) {
        int flag = 1;
        for(int i = 0 ; i < 2 ; ++ i) {
            if(ch_in(u, v.p[i])) {
                flag = 0;
            }
            if(ch_in(v, u.p[i])) {
                flag = 0;
            }
        }
        if(flag) return 0;
    }


    for(int i = 0 ; i < 2 ; ++ i) {
        for(int j = 0 ; j < 2 ; ++ j) {
            if(u.p[i] == v.p[j]) {
                int flag = 1;

                if(ch_in(u, v.p[j ^ 1])) flag = 0;
                if(ch_in(v, u.p[i ^ 1])) flag = 0;

                if(flag) return 0;
            }
        }
    }

    return 1;
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= m ; ++ i) {
        int u, v; scanf("%d%d", &u, &v);
        if(u > v) swap(u, v);
        ln[i].u = u, ln[i].v = v;
    }
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%lld%lld", &p[i].x, &p[i].y);
    }
    for(int i = 1 ; i <= m ; ++ i) {
        ln[i].a = ln[i].p[0] = p[ln[i].u];
        ln[i].b = ln[i].p[1] = p[ln[i].v];
    }
    int ans = 0;
    for(int i = 1 ; i <= m ; ++ i) {
        for(int j = 1 ; j < i ; ++ j) {
            if(check(ln[i], ln[j])) {
                // printf("%d, %d, (%lld, %lld)-(%lld, %lld)   (%lld, %lld)-(%lld, %lld)\n", i, j, ln[i].a.x, ln[i].a.y, ln[i].b.x, ln[i].b.y, ln[j].a.x, ln[j].a.y, ln[j].b.x, ln[j].b.y);
                ++ ans;
            }
        }
    }
    printf("%d\n", ans);
}

