#include "bits/stdc++.h"
using namespace std;
typedef long double ld;
const int N = 1e5 + 10;

int n;
ld p;

vector<int> G[N];

struct D {
    ld x, c; // x * f1 + c
    D(ld x = 0, ld c = 0): x(x), c(c) {}
    D operator * (ld w) { return D(x * w, c * w); }
    D operator / (ld w) { return D(x / w, c / w); }
    D operator + (ld w) { return D(x, c + w); }
    D operator + (D t) { return D(x + t.x, c + t.c); }
} f[N];

void dfs(int u) {
    if(u == n) { f[u] = D(0, 0); return ; }
    if(G[u].empty()) { f[u] = D(1, 0); return ; }
    f[u] = D(0, 0);
    for(int v: G[u]) {
        dfs(v);
        f[u] = f[u] + f[v] + 1;
    }
    f[u] = D(0, (1 - p) / p) + f[u] / G[u].size();
}

int main() {
    cin >> n >> p;
    for(int i = 2, f ; i <= n ; ++ i) cin >> f, G[f].push_back(i);
    dfs(1);
    cout << fixed << setprecision(2) << (f[1].c / (1 - f[1].x)) << endl;
}
