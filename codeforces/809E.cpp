#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 5e5 + 10, mod = 1e9 + 7;

int head[N], rest[N * 2], to[N * 2];

void add(int u, int v) {
    static int tot = 0;
    to[++ tot] = v, rest[tot] = head[u], head[u] = tot;
}

int n, phi[N], mu[N], pri[N], vis[N], ln_tot, a[N];

int mem[N * 10], sta[N];

vector<int> g[N];

int beg_dfn[N], end_dfn[N], fa[N][21], dep[N];
int getlca(int u, int v) {
    if(dep[u] < dep[v]) swap(u, v);
    for(int i = 20 ; ~ i ; -- i) if(dep[fa[u][i]] >= dep[v]) u = fa[u][i];
    if(u == v) return u;
    for(int i = 20 ; ~ i ; -- i) if(fa[u][i] != fa[v][i]) u = fa[u][i], v = fa[v][i];
    return fa[u][0];
}
void getdfn(int u, int fa) {
    :: fa[u][0] = fa;
    for(int i = 1 ; i <= 20 ; ++ i)
        :: fa[u][i] = :: fa[:: fa[u][i - 1]][i - 1];
    dep[u] = dep[fa] + 1;    
    static int clk = 0;
    beg_dfn[u] = ++ clk;
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(v == fa) continue;
        getdfn(v, u);
    }
    end_dfn[u] = clk;
}

int cmp(int a, int b) { return beg_dfn[a] < beg_dfn[b]; }

int root;

ll pw(ll a, ll b) {
    ll r = 1;
    for(a %= mod ; b ; b >>= 1, a = a * a % mod)
        if(b & 1)
            r = r * a % mod;
    return r;
}

ll res, ans;

ll f[N], h[N]; // f: phi*dep, h: phi

int D;

void dfs(int u, int fa) {
    f[u] = h[u] = 0;
    if(a[u] % D == 0) {
        f[u] = (ll) phi[a[u]] * dep[u] % mod;
        h[u] = phi[a[u]];
    }
    for(int v: g[u]) {
        if(v == fa) continue;
        dfs(v, u);
        res += (f[u] * h[v] % mod + h[u] * f[v] % mod - 2ll * dep[u] * h[u] % mod * h[v] % mod) % mod;
        (f[u] += f[v]) %= mod;
        (h[u] += h[v]) %= mod;
    }
}

ll getans() {
    res = 0;
    dfs(root, 0);
    return res;
}

ll F[N];

int rev[N];

int main() {
//    freopen("data.in", "r", stdin);
    
    ios :: sync_with_stdio();
    cin >> n;
    for(int i = 1 ; i <= n ; ++ i)
        cin >> a[i], rev[a[i]] = i;
    for(int i = 1, u, v ; i < n ; ++ i)
        cin >> u >> v, add(u, v), add(v, u);
    phi[1] = mu[1] = 1;
    for(int i = 2 ; i <= n ; ++ i) {
        if(!vis[i]) {
            pri[++ ln_tot] = i;
            mu[i] = -1, phi[i] = i - 1;
        }
        for(int j = 1 ; j <= ln_tot && i * pri[j] <= n ; ++ j) {
            vis[i * pri[j]] = 1;
            if(i % pri[j] == 0) {
                phi[i * pri[j]] = phi[i] * pri[j];
                break;
            } else {
                phi[i * pri[j]] = phi[i] * (pri[j] - 1);
                mu[i * pri[j]] = -mu[i];
            }
        }
    }
    
    getdfn(1, 0);
    for(int d = 1 ; d <= n ; ++ d) {
        D = d;
        int mem_tot = 0;
        for(int i = d ; i <= n ; i += d) {
            mem[++ mem_tot] = rev[i];
        }
        sort(mem + 1, mem + 1 + mem_tot, cmp);
        mem_tot = unique(mem + 1, mem + 1 + mem_tot) - mem - 1;
        for(int i = mem_tot ; i >= 2 ; -- i) {
            mem[++ mem_tot] = getlca(mem[i], mem[i - 1]);
        }
        sort(mem + 1, mem + 1 + mem_tot, cmp);
        mem_tot = unique(mem + 1, mem + 1 + mem_tot) - mem - 1;
        
        root = mem[1];
        
        int top = 0;
        for(int i = 1 ; i <= mem_tot ; ++ i) {
            int u = mem[i], fa;
            while(top && end_dfn[sta[top]] < beg_dfn[u]) -- top;
            if(fa = sta[top]) {
                g[fa].push_back(u), g[u].push_back(fa);
            }
            sta[++ top] = u;
        }
        
        F[d] = getans();
        for(int i = 1 ; i <= mem_tot ; ++ i) g[mem[i]].clear();
    }

    for(int d = 1 ; d <= n; ++ d) {
	    ll f = 0;
		for(int i = d ; i <= n; i += d)
			(f += F[i] * mu[i / d] % mod) %= mod;
		(ans += f * d % mod * pw(phi[d], mod - 2) % mod) %= mod;
	}
    
    ans = ans * pw((ll) n * (n - 1) % mod, mod - 2) % mod;
    ans = ans * 2 % mod;
    cout << (ans % mod + mod) % mod << endl;
}

