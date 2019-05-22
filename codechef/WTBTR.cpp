#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 1e4 + 10;

int n;
struct P {
    int x, y;
} p[N];
double dis(P a, double k, double b) {
    double x0 = a.x, y0 = a.y;
    return abs((-k * x0 + y0 - b) / sqrt(k * k + 1));
}

double calc(P p1, P p2) {
    double x0 = (p1.x + p2.x) / 2.0, y0 = (p1.y + p2.y) / 2.0;
    double k, b, res;

    k = 1, b = y0 - k * x0;
    res = dis(p1, k, b);

    k = -1, b = y0 - k * x0;
    res = min(res, dis(p1, k, b));

    return res;
}
void runprog() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d%d", &p[i].x, &p[i].y);
    }
    double ans = calc(p[1], p[2]);

    for(int T = 1 ; T <= 2 ; ++ T) {
        set<ll> mem;
        for(int i = 1 ; i <= n ; ++ i) {
            ll cur = p[i].y - p[i].x;
            auto it = mem.lower_bound(cur);
            if(it != mem.end()) {
                ans = min(ans, abs(cur - *it) / (2.0 * sqrt(2)));
            }
            if(it != mem.begin()) {
                -- it;
                ans = min(ans, abs(cur - *it) / (2.0 * sqrt(2)));
            }
            mem.insert(cur);
        }
        for(int i = 1 ; i <= n ; ++ i) {
            p[i].x *= -1;
        }
    }
    
    printf("%.6f\n", ans * sqrt(2));
}

int main() {
    int t; scanf("%d", &t);
    while(t --) {
        runprog();
    }
}
