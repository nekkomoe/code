#include "bits/stdc++.h"
using namespace std;
const int N = 1e5 + 100, inf = 1e9;
int n;

typedef complex<double> com;
double ans;
int ban[N], f[N] = { inf }, sz[N], root, size;
vector<int> G[N];

void getroot(int u, int fa) {
    f[u] = 0, sz[u] = 1;
    for(int i = 0 ; i < G[u].size() ; ++ i) {
		int v = G[u][i];
        if(!ban[v] && v != fa) {
            getroot(v, u);
            sz[u] += sz[v];
            f[u] = max(f[u], sz[v]);
        }
    }
    f[u] = max(f[u], size - sz[u]);
    if(f[root] > f[u]) root = u;
}

int mxdep, _dep[N * 4];
com dep[N * 4], t[N * 4];

void dfs(int u, int fa, int dep) {
    ++ _dep[dep];
    mxdep = max(mxdep, dep);
    for(int i = 0 ; i < G[u].size() ; ++ i) {
    	int v = G[u][i];
        if(!ban[v] && v != fa)
            dfs(v, u, dep + 1);
	}
}

int rev(int x, int n) {
    int r = 0;
    for(int i = 0 ; (1 << i) < n ; ++ i) r = (r << 1) | ((x >> i) & 1);
    return r;
}

void fft(com *a, int n, int ty) {
    for(int i = 0 ; i < n ; ++ i) t[rev(i, n)] = a[i];

    for(int i = 2 ; i <= n ; i <<= 1) {
        com wn(cos(2 * acos(-1) * ty / i), sin(2 * acos(-1) * ty / i));
        for(int j = 0 ; j < n ; j += i) {
            com w(1);
            for(int k = j ; k < j + i / 2 ; ++ k) {
                com u = t[k], v = w * t[k + i / 2];
                t[k] = u + v, t[k + i / 2] = u - v;
                w *= wn;
            }
        }
    }

    for(int i = 0 ; i < n ; ++ i) {
        a[i] = t[i];
        if(ty == -1) a[i] /= n;
    }
}

void getcont(int ty) {
    for(int i = 0 ; i <= mxdep ; ++ i) dep[i] = _dep[i];
    int len = 1;
    while(len <= mxdep * 2 + 5) len <<= 1;
    for(int i = mxdep + 1 ; i < len ; ++ i) dep[i] = 0;
    fft(dep, len, 1);
    for(int i = 0 ; i < len ; ++ i) dep[i] *= dep[i];
    fft(dep, len, -1);

    for(int i = 1 ; i < len ; ++ i) ans += (1.0 / (i + 1)) * ty * dep[i].real();
    for(int i = 0 ; i < len ; ++ i) dep[i] = _dep[i] = 0;
}

void sol(int u) {
    ban[u] = 1;

    mxdep = 0;
    dfs(u, 0, 0);
    getcont(1);

	for(int i = 0 ; i < G[u].size() ; ++ i) {
		int v = G[u][i];
        if(!ban[v]) {
            mxdep = 0;
            dfs(v, u, 1);
            getcont(-1);
        }
	}
    for(int i = 0 ; i < G[u].size() ; ++ i) {
    	int v = G[u][i];
	    if(!ban[v])
            root = 0, size = sz[v], getroot(v, 0), sol(root);
    }
}

int main() {
    scanf("%d", &n);
    for(int i = 1, u, v ; i < n ; ++ i) {
        scanf("%d%d", &u, &v), ++ u, ++ v;
        G[u].push_back(v), G[v].push_back(u);
    }
    root = 0, size = n, getroot(1, 0), sol(root);
    printf("%.4lf\n", ans + n);
}
