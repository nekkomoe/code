#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 3e5 + 10;
int n;
struct P {
    double x, y;
    double operator * (P b) {
        return x * b.y - (ll) b.x * y;
    }
    P operator - (P b) {
        return (P) { x - b.x, y - b.y };
    }
} p[N];

double pw[N], area[N], cnt;

int mn;

int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

int main() {
    cin >> n;
    for(int i = 1 ; i <= n ; ++ i) {
        cin >> p[i].x >> p[i].y;
    }
    p[0] = p[n];
    mn = min(n, 60);
    pw[0] = 1;
    for(int i = 1 ; i <= mn ; ++ i) pw[i] = pw[i - 1] * 0.5;
    double S = 0;
    for(int i = 0 ; i < n ; ++ i) S += p[i] * p[i + 1] / 2.0;
    for(int i = 3 ; i <= mn ; ++ i) {
        double pb = (pw[i] - pw[n]) / (1 - pw[n] * (1 + n + (ll) n * (n - 1) / 2));
        for(int j = 1 ; j <= n ; ++ j) {
            area[j] += (p[(j + i - 2) % n] - p[j]) * (p[(j + i - 1) % n] - p[j]) / 2.0;
            S -= pb * area[j];
        }
    }
    for(int i = 2 ; i <= mn ; ++ i) {
        double pb = (pw[i] - pw[n]) / (1 - pw[n] * (1 + n + (ll) n * (n - 1) / 2));
        for(int j = 1 ; j <= n ; ++ j) {
            cnt += gcd(int(abs(p[j].x - p[(j + i - 1) % n].x) + 0.5), int(abs(p[j].y - p[(j + i - 1) % n].y) + 0.5)) * pb;
        }
    }
    printf("%.10lf\n", S - 0.5 * cnt + 1);
}
