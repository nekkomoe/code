#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

template<typename T> inline void read(T &x) {
    cin >> x;
}

const int N = 5e4 + 10;

int n, tp;

struct P {
    ll x, y, id;
    P() {}
    P(ll x, ll y) : x(x), y(y) {}
} p[N];

bool operator < (P a, P b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}

bool cmp(P a, P b) {
    return a.id < b.id;
}

P s[N];

P operator - (P a, P b) {
    return P(a.x - b.x, a.y - b.y);
}

ll cross(P a, P b) {
    return a.x * b.y - b.x * a.y;
}

int main() {
    read(n);
    for(int i = 1 ; i <= n ; ++ i) read(p[i].x), read(p[i].y), p[i].y = -p[i].y, p[i].id = i;
    sort(p + 1, p + 1 + n);
    for(int i = 1 ; i <= n ; ++ i) {
        if(p[i].x != p[i - 1].x) {
            while(tp >= 2 && cross(s[tp] - s[tp - 1], p[i] - s[tp - 1]) <= 0) -- tp;
            s[++ tp] = p[i];
        }
    }
    sort(s + 1, s + 1 + tp, cmp);
    for(int i = 1 ; i <= tp ; ++ i) printf("%lld ", s[i].id);
}

