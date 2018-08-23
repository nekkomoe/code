#include "bits/stdc++.h"
using namespace std;
const int N = 1010;
int a[N][N], n, m, ans;
struct T {
    int val, x, y;
} g[N * N];
bool operator < (T a, T b) {
    return a.val > b.val;
}
int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= n ; ++ i)
        for(int j = 1 ; j <= m ; ++ j)
            scanf("%d", &a[i][j]),
            g[(i - 1) * m + j] = ((T) { a[i][j], i, j });
    sort(g + 1, g + 1 + n * m);
    int tot = min(4 * max(n, m), n * m);
    for(int i = 1 ; i <= tot ; ++ i) {
        for(int j = i + 1 ; j <= tot ; ++ j) {
            if(g[i].x != g[j].x && g[i].y != g[j].y) {
                ans = max(ans, min(min(a[g[i].x][g[i].y], a[g[j].x][g[j].y]), min(a[g[i].x][g[j].y], a[g[j].x][g[i].y])));
            }
        }
    }
    printf("%d\n", ans);
}
