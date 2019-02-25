#include "bits/stdc++.h"
using namespace std;
struct P {
    double x, y;
} a, b;
double dis(P a, P b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
int main() {
    int r; cin >> r;
    cin >> a.x >> a.y;
    cin >> b.x >> b.y;
    double ans = dis(a, b);
    for(double t = 0, pi = acos(-1) ; t < pi ; t += 0.0000007) {
        P p = (P) { r * cos(t), r * sin(t) };
        P q = (P) { -p.x, -p.y };
        ans = min(ans, min(dis(a, q) + dis(p, b), dis(a, p) + dis(q, b)));
    }
    cout << fixed << setprecision(15) << ans << endl;
}
