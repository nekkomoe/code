#include "bits/stdc++.h"
using namespace std;
const int N = 1e5 + 10;
typedef long long ll;
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
struct Pac { int w, p; double t; } fafa[N];
bool operator < (Pac a, Pac b) { return a.t > b.t; }

int n, k; ll x, y, up, down;

bool check(double T) {
    double sum = x = y = 0;
    for(int i = 1 ; i <= n; ++ i) fafa[i].t = fafa[i].p - fafa[i].w * T;
    sort(fafa + 1, fafa + 1 + n);
    for(int i = 1 ; i <= k ; ++ i) sum += fafa[i].t, x += fafa[i].p, y += fafa[i].w;
    return sum >= 0;
}

int main() {
    scanf("%d%d", &n, &k);
    for(int i = 1 ; i <= n ; ++ i) scanf("%d%d", &fafa[i].w, &fafa[i].p);
    double l = 0, r = 1e10;
    for(int i = 1 ; i <= 100 ; ++ i) {
        double mid = (l + r) / 2;
        if(check(mid)) l = mid, up = x, down = y;
        else r = mid;
    }
    ll d = gcd(up, down);
    printf("%lld/%lld\n", up / d, down / d);
}

