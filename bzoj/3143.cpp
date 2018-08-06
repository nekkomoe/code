#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <ctime>
#include <cctype>
#include <cfloat>
#include <string>
#include <sstream>
#include <fstream>
#include <cassert>
#include <cmath>
#include <bitset>
 
using namespace std;
 
#ifdef ONLINE_JUDGE
    #define debug
    #define log(message)
#else
    #define debug printf("passing [%s] in line %d\n", __FUNCTION__, __LINE__)
    #define log(message) puts(message)
#endif
 
#define INF 0x3f3f3f3f
 
#define INFLL 0x3f3f3f3f3f3f3f3fLL
 
void closeSync() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
}
 
template<class T> inline void read(T &x) {
    x = 0; int f = 0; char ch = getchar();
    while(ch < '0' || ch > '9') f |= (ch == '-'), ch = getchar();
    while('0' <= ch && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ '0'), ch = getchar();
    x = f ? -x : x;
}
 
typedef long long ll;
 
typedef long double ld;
 
const ld eps = 1e-9;
 
const int N = 510;
 
int n, m, deg[N], u[N * N], v[N * N];
 
ld mat[N][N], w[N * N], ans;
 
bool cmp(ld a, ld b) {
    return b - a > eps;
}
 
int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= m ; ++ i) scanf("%d%d", &u[i], &v[i]), ++ deg[u[i]], ++ deg[v[i]];
    for(int i = 1 ; i <= m ; ++ i) {
        if(u[i] != n) mat[v[i]][u[i]] = 1.0 / deg[u[i]];
        if(v[i] != n) mat[u[i]][v[i]] = 1.0 / deg[v[i]];
    }
    for(int i = 1 ; i <= n ; ++ i) {
        mat[i][i] = -1;
    }
    mat[1][n + 1] = -1;
    for(int i = 1 ; i <= n ; ++ i) {
        int id = i;
        for(int j = i ; j <= n ; ++ j) if(fabs(mat[j][i]) > fabs(mat[id][i])) id = j;
        if(id != i) for(int j = 1 ; j <= n + 1 ; ++ j) swap(mat[i][j], mat[id][j]);
        for(int j = i + 1 ; j <= n ; ++ j) {
            ld x = mat[j][i] / mat[i][i];
            for(int k = i ; k <= n + 1 ; ++ k) {
                mat[j][k] -= mat[i][k] * x;
            }
        }
    }
    for(int i = n ; i >= 1 ; -- i) {
        for(int j = i + 1 ; j <= n ; ++ j) {
            mat[i][n + 1] -= mat[i][j] * mat[j][n + 1];
        }
        mat[i][n + 1] /= mat[i][i];
    }
    for(int i = 1 ; i <= m ; ++ i) {
        if(u[i] != n) w[i] += mat[u[i]][n + 1] / deg[u[i]];
        if(v[i] != n) w[i] += mat[v[i]][n + 1] / deg[v[i]];
    }
    sort(w + 1, w + 1 + m, cmp);
    for(int i = 1 ; i <= m ; ++ i) {
        ans += w[i] * (m - i + 1);
    }
    printf("%.3Lf\n", ans);
    return 0;
}
