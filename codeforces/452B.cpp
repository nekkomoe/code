#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
int n, m;
void put(int x, int y) { printf("%d %d\n", x, y); }
int dis(int x, int y) { return x * x + y * y; }
int main() {
    scanf("%d%d", &n, &m);
    if(n == 0) {
        put(0, 1);
        put(0, m);
        put(0, 0);
        put(0, m - 1);
    } else if(m == 0) {
        put(1, 0);
        put(n, 0);
        put(0, 0);
        put(n - 1, 0);
    } else {
        int dis1 = 2 * dis(n, m - 1), dis2 = 2 * dis(n - 1, m), dis3 = dis(n, m) + dis(0, m), dis4 = dis(n, m) + dis(n, 0);
        int mx = max(max(dis1, dis2), max(dis3, dis4));
        if(mx == dis1)
        // 1
        put(n, m - 1),
        put(0, 0),
        put(n, m),
        put(0, 1);
        else if(mx == dis2)
        // 2
        put(n - 1, m),
        put(0, 0),
        put(n, m),
        put(1, 0);
        else if(mx == dis3)
        // 3
        put(0, 0),
        put(n, m),
        put(n, 0),
        put(0, m);
        else if(mx == dis4)
        // 4
        put(0, 0),
        put(n, m),
        put(0, m),
        put(n, 0);
    }
}
