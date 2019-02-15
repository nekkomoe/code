#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
 
const int N = 1e6 + 10;
 
int n, m, q, head[N], rest[N], to[N], w[N], tot;
void add(int u, int v, int val) {
    to[++ tot] = v, w[tot] = val, rest[tot] = head[u], head[u] = tot;
}
 
struct E { int u, v, w; } e[N]; int e_cnt;
 
int cmp(E a, E b) {
    return make_pair(a.u, make_pair(a.v, a.w)) < make_pair(b.u, make_pair(b.v, b.w));
} 
 
int dfn[N], low[N], clk, sta[N], top, cnt, from[N];
int ele[N], ele_cnt;
int sum[N], the_val[N], b;
 
void neko(int u, int fa) {
    from[u] = fa;
    dfn[u] = low[u] = ++ clk, sta[++ top] = u;
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(!dfn[v]) {
         
            neko(v, u);
            low[u] = min(low[u], low[v]);
             
            if(low[v] >= dfn[u]) {
                ele_cnt = 0; 
                int cat;
                do {
                    cat = sta[top --];
                    ele[++ ele_cnt] = cat;
                } while(cat != v);
                 
                ++ cnt;
                for(int j = head[u] ; j ; j = rest[j]) {
                    int v = to[j];
                    if(v == ele[1]) {
                        sum[cnt] += w[j];
                        break;
                    }
                }
                 
                ele[++ ele_cnt] = u;
                 
                for(int j = 1 ; j < ele_cnt ; ++ j) {
                    int x = ele[j];
                    for(int k = head[x] ; k ; k = rest[k]) {
                        int y = to[k];
                        if(y == ele[j + 1]) {
                            sum[cnt] += w[k];
                            the_val[x] = w[k];
                            break;
                        }
                    }
                }
                 
//                printf("get a circle: ");
//                for(int j = 1 ; j < ele_cnt ; ++ j) {
//                    printf("%d(%d) ", ele[j], the_val[ele[j]]);
//                }
//                printf("  |  %d\n", u);
//                printf("sum cnt = %d\n", sum[cnt]);
                 
                for(int j = ele_cnt - 2 ; j >= 1 ; -- j) {
                    int x = ele[j], y = ele[j + 1];
                    the_val[x] += the_val[y];
                }
                 
//                printf("RE: ");
//                for(int j = 1 ; j < ele_cnt ; ++ j) {
//                    printf("%d(%d) ", ele[j], the_val[ele[j]]);
//                } puts("");
                 
                e[++ e_cnt] = (E) { u, cnt, 0 };
                for(int i = 1 ; i <= ele_cnt - 1 ; ++ i) {
                    int x = ele[i];
                    e[++ e_cnt] = (E) { x, cnt, min(the_val[x], sum[cnt] - the_val[x]) };
                }
            }
         
        } else if(v != fa) {
            low[u] = min(low[u], dfn[v]);
        }
    }
}
 
int fa[N][22], dep[N];
int len[N], len_from[N];
 
void dfs(int u, int fa) {
    dep[u] = dep[fa] + 1;
    :: fa[u][0] = fa;
    for(int i = 1 ; i <= 20 ; ++ i) {
        :: fa[u][i] = :: fa[:: fa[u][i - 1]][i - 1];
    }
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(v == fa) continue;
         
        len[v] = len[u] + w[i];
        len_from[v] = w[i];
         
        dfs(v, u);
    }
}
 
int getlca(int u, int v) {
    if(dep[u] < dep[v]) swap(u, v);
    for(int i = 20 ; ~ i ; -- i) {
        if(dep[fa[u][i]] >= dep[v]) {
            u = fa[u][i];
        }
    }
    if(u == v) return u;
    for(int i = 20 ; ~ i ; -- i) {
        if(fa[u][i] != fa[v][i]) {
            u = fa[u][i];
            v = fa[v][i];
        }
    }
    return fa[u][0];
}
 
int get_pts(int u, int top) {
    for(int i = 20 ; ~ i ; -- i) {
        if(dep[fa[u][i]] > dep[top]) {
            u = fa[u][i];
        }
    }
    return u;
}
 
int getdis(int u, int v) {
    int d = fa[u][0];
    int len = abs(the_val[u] - the_val[v]);
    return min(len, sum[d] - len);
}
 
int ask(int u, int v) {
    int lca = getlca(u, v);
    if(lca <= n) {
        return len[u] + len[v] - 2 * len[lca];
    } else {
        int res = len[u] + len[v] - 2 * len[lca];
        int x = get_pts(u, lca), y = get_pts(v, lca);
        res = res - len_from[x] - len_from[y] + getdis(x, y);
        return res;
    }
}
 
int main() {
     
//    freopen("data.in", "r", stdin);
//    freopen("data.out", "w", stdout);
     
    scanf("%d%d%d", &n, &m, &q);
    for(int i = 1 ; i <= m ; ++ i) {
        int u, v, w; scanf("%d%d%d", &u, &v, &w);
        if(u > v) swap(u, v);
        e[i] = (E) { u, v, w };
    }
    cnt = n;
    sort(e + 1, e + 1 + m, cmp);
    for(int i = 1 ; i <= m ; ++ i) {
        int u = e[i].u, v = e[i].v, w = e[i].w;
        if(make_pair(e[i - 1].u, e[i - 1].v) != make_pair(u, v)) {
            add(u, v, w), add(v, u, w);
             
//            printf("link: %d <-> %d, w = %d\n", u, v, w);
             
        }
    }
     
//    return 0;
     
    neko(1, 0);
     
    for(int i = 1 ; i <= n ; ++ i) head[i] = 0; tot = 0;
    for(int i = 1 ; i <= e_cnt ; ++ i) {
        int u = e[i].u, v = e[i].v, w = e[i].w;
        add(u, v, w);
        add(v, u, w);
         
//        printf("link: %d <-> %d, w = %d\n", u, v, w);
    }
     
    dfs(1, 0);
     
    while(q --) {
        int u, v; scanf("%d%d", &u, &v);
        printf("%d\n", ask(u, v));
    }
}
