#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

//#define TO_DEBUG

#ifdef TO_DEBUG

#define debug_puts puts
#define debug_printf printf 

#else

#define debug_puts
#define debug_printf

#endif

const int N = 2e6 + 10;

int n, m, col[N], cnt, inside[N], inside_clk;

int head[N], rest[N], to[N], tot;
void add(int u, int v) {
    to[++ tot] = v, rest[tot] = head[u], head[u] = tot;
}

int root[N], rt; ll ans[N];

namespace build_CT_tree {
    
    struct E { int u, v; } e[N];
    int dfn[N], low[N], clk, sta[N], top, e_cnt;
    
    void nya(int u, int fa) {
        inside[u] = inside_clk;
        dfn[u] = low[u] = ++ clk, sta[++ top] = u;
        for(int i = head[u] ; i ; i = rest[i]) {
            int v = to[i];
            if(!dfn[v]) {
                nya(v, u);
                low[u] = min(low[u], low[v]);
                if(low[v] >= dfn[u]) {
                    e[++ e_cnt] = (E) { u, ++ cnt };
                    int neko;
                    do {
                        neko = sta[top --];
                        e[++ e_cnt] = (E) { cnt, neko };
                    } while(neko != v);
                }
            } else if(v != fa) {
                low[u] = min(low[u], dfn[v]);
            }
        }
    }
    
    void runprog() {
        cnt = n;
        for(int i = 1 ; i <= n ; ++ i) {
            if(!dfn[i]) {
                ++ inside_clk;
                root[++ rt] = i;
                nya(i, 0);
            }
        }
        for(int i = 1 ; i <= n ; ++ i) head[i] = 0; tot = 0;
        for(int i = 1 ; i <= e_cnt ; ++ i) {
            int u = e[i].u, v = e[i].v;
            debug_printf("%d <-> %d\n", u, v);
            add(u, v), add(v, u);
        } 
        
//        exit(0);
    }
}

int dfn[N], enddfn[N], fa[N];

namespace LCA {
    int f[N][25], dep[N], clk, lg[N], ele[N], lcadfn[N], lcaclk;
    
    int getmin(int u, int v) {
        return dep[u] < dep[v] ? u : v;
    }
    
//    #define FILE_DEBUG
    
    void dfs(int u, int f) {
        
        debug_printf("%d %d\n", u, f); 
        
        fa[u] = f;
        dfn[u] = ++ clk;
        dep[u] = dep[f] + 1;
        
        lcadfn[u] = ++ lcaclk;
        ele[lcaclk] = u;
        
        for(int i = head[u] ; i ; i = rest[i]) {
            int v = to[i];
            if(v == f) continue;
            dfs(v, u); 
            ele[++ lcaclk] = u; 
        }
        enddfn[u] = clk;
    }
    
    int get(int u, int v) {
        int l = lcadfn[u], r = lcadfn[v];
        if(l > r) swap(l, r);
        int k = lg[r - l + 1];
        return getmin(f[l][k], f[r - (1 << k) + 1][k]);
    }
    
    void runprog() {
        for(int i = 1 ; i <= cnt ; ++ i) {
            if(!dep[i]) {
                dfs(i, 0);
            } 
        } 
        for(int i = 2 ; i <= lcaclk ; ++ i) {
            lg[i] = lg[i >> 1] + 1;
        }
        for(int i = 1 ; i <= lcaclk ; ++ i) {
            f[i][0] = ele[i];
        }
        for(int j = 1 ; j <= 20 ; ++ j) {
            for(int i = 1 ; i + (1 << j) - 1 <= lcaclk ; ++ i) {
                f[i][j] = getmin(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
            } 
        }
    }
} 

vector<int> cont[int(1e6) + 10];

ll all_add;

namespace GETANS {
    
    int inp_neko[N], inp_size;
    
    int sta[N], top;
    
    int neko[N], nya;
    
    bool cmp_by_connect_block(int a, int b) {
        return inside[a] < inside[b];
    }
    
    bool cmp_by_dfn(int a, int b) {
        return dfn[a] < dfn[b];
    }
    
    vector<int> g[N]; int sz[N], key[N], glosize;
    
    void dfs(int u) {
        sz[u] = key[u];
        for(int i = 0 ; i < (int) g[u].size() ; ++ i) {
            int v = g[u][i];
            dfs(v);
            
            ll val = (ll) sz[v] * sz[u];
            ans[u] += val;
            ans[fa[u]] -= val;
            
            sz[u] += sz[v];
            
            val = (ll) (glosize - sz[v]) * sz[v];
            ans[fa[v]] += val;
            ans[u] -= val;
        }
        
        ll val = (ll) (glosize - sz[u]) * sz[u];
        ans[u] += val;
        ans[fa[u]] -= val;
    }
    
    void sol() {
        
        glosize = nya;
                
        for(int i = 1 ; i <= nya ; ++ i) {
            key[neko[i]] = 1;
        }
        
        sort(neko + 1, neko + 1 + nya, cmp_by_dfn);
        for(int i = nya ; i >= 2 ; -- i) {
            neko[++ nya] = LCA :: get(neko[i], neko[i - 1]);
        }
        sort(neko + 1, neko + 1 + nya, cmp_by_dfn);
        nya = unique(neko + 1, neko + 1 + nya) - neko - 1;
        
        top = 0;
        for(int i = 1 ; i <= nya ; ++ i) {
            int u = neko[i];
            while(top && enddfn[sta[top]] < dfn[u]) -- top;
            if(top) {
                g[sta[top]].push_back(u);
            }
            sta[++ top] = u;
        }
        
        debug_printf("A TREE, glosize = %d\n", glosize);
        for(int i = 1 ; i <= nya ; ++ i) {
            debug_printf("%d ", neko[i]); 
        } 
        debug_puts("\n");
        
        dfs(sta[1]);
        for(int i = 1 ; i <= nya ; ++ i) {
            g[neko[i]].clear();
            key[neko[i]] = 0;
        }
    }
    
    void runprog() {
        for(int i = 1 ; i <= int(1e6) ; ++ i) {
            if(cont[i].size()) {
                inp_size = 0;
                for(int j = 0 ; j < (int) cont[i].size() ; ++ j) {
                    inp_neko[++ inp_size] = cont[i][j];
                } 
                sort(inp_neko + 1, inp_neko + 1 + inp_size, cmp_by_connect_block);
                
                ll sum = 0;
                for(int j = 1 ; j <= inp_size ; ) {
                    nya = 0;
                    int k = j;
                    while(k <= inp_size && inside[inp_neko[j]] == inside[inp_neko[k]]) {
                        neko[++ nya] = inp_neko[k];
                        ++ k;
                    }
                    
                    all_add += (k - j) * sum;
                    sum += k - j;
                    
                    sol(); 
                    j = k;
                }
            }
        }
    }
}

namespace PUSH_TAG {
    
    void dfs(int u, int fa) {
        for(int i = head[u] ; i ; i = rest[i]) {
            int v = to[i];
            if(v == fa) continue;
            dfs(v, u);
            ans[u] += ans[v];
        }
    }
    
    void runprog() {
        for(int i = 1 ; i <= rt ; ++ i) {
            dfs(root[i], 0);
        }
    }
}

int main() {

#ifdef FILE_DEBUG
    freopen("data.in", "r", stdin);
#endif
    
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &col[i]);
        cont[col[i]].push_back(i);
    }
    for(int i = 1 ; i <= m ; ++ i) {
        int u, v; scanf("%d%d", &u, &v);
        add(u, v), add(v, u);
    }
    
    debug_puts("BEGIN TO BUILD CT");

    build_CT_tree :: runprog();
    
    debug_puts("BEGIN TO GET LCA"); 
    
    LCA :: runprog();
    
    debug_puts("BEGIN TO GETANS");
    
    GETANS :: runprog();
    PUSH_TAG :: runprog();
    
    debug_printf("all_add = %lld\n", all_add); 
    
    for(int i = 1 ; i <= n ; ++ i) {
        printf("%lld\n", ans[i] + all_add);
    }
}
