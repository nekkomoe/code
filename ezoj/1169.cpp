#include <bits/stdc++.h>

using namespace std;

const int N = 50010 * 2;

int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }

int head[N], rest[N], to[N], tmp[N];

void add(int u, int v) {
    static int tot = 0;
    to[++ tot] = v, rest[tot] = head[u], head[u] = tot;
}

int sz[N], son[N], top[N], fa[N], deep[N], cnt;

// seg tree

struct st {
    int x1, g, xn, d, l, r, tag;
} p[N * 10];

int val[N];

void push(int u) {
    if(p[u].tag) {
        p[u << 1].tag += p[u].tag, p[u << 1 | 1].tag += p[u].tag;
        p[u].x1 += p[u].tag;
        
        p[u].xn += p[u].tag; 
        
        if(p[u].l == p[u].r) {
            p[u].xn = p[u].g = p[u].d = p[u].x1;
        } else {
            p[u].d = gcd(p[u].x1, p[u].g);
        }
        
        p[u].tag = 0;
    }
}

void update(int u) {
    
    push(u), push(u << 1), push(u << 1 | 1);
    
    if(p[u].l == p[u].r) {
        p[u].x1 = val[p[u].l];
        p[u].xn = p[u].x1;
        p[u].g = p[u].x1;
        p[u].d = p[u].x1;
    } else {
        p[u].x1 = p[u << 1].x1;
        p[u].xn = p[u << 1 | 1].xn;
        
        if(p[u << 1].l == p[u << 1].r) {
            if(p[u << 1 | 1].l == p[u << 1 | 1].r) {
                int a = p[u << 1].xn, b = p[u << 1 | 1].x1;
                p[u].g = max(a, b) - min(a, b);
            } else {
                int a = p[u << 1].xn, b = p[u << 1 | 1].x1;
                p[u].g = gcd(max(a, b) - min(a, b), p[u << 1 | 1].g);
            }
        } else {
            if(p[u << 1 | 1].l == p[u << 1 | 1].r) {
                int a = p[u << 1].xn, b = p[u << 1 | 1].x1;
                p[u].g = gcd(p[u << 1].g, max(a, b) - min(a, b));
            } else {
                int a = p[u << 1].xn, b = p[u << 1 | 1].x1;
                p[u].g = gcd(gcd(p[u << 1].g, max(a, b) - min(a, b)), p[u << 1 | 1].g);
            }
        }
        
        p[u].d = gcd(p[u].x1, p[u].g);
    }
}

void build(int u, int l, int r) {
    p[u].l = l, p[u].r = r;
    int mid = (l + r) >> 1;
    if(l == r) {
        p[u].x1 = p[u].xn = p[u].g = p[u].d = val[l];
        
        
//        printf("build(%d, %d, %d)  x1 = %d    xn = %d   g = %d   d = %d\n", u, l, r, p[u].x1, p[u].xn, p[u].g, p[u].d);
        
        return ;
    }
    build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
    update(u);
    
//    printf("build(%d, %d, %d)  x1 = %d    xn = %d   g = %d   d = %d\n", u, l, r, p[u].x1, p[u].xn, p[u].g, p[u].d);
    
}

void print(int u, int l, int r) {
    push(u);
    p[u].l = l, p[u].r = r;
    int mid = (l + r) >> 1;
    if(l == r) {
//        printf("build(%d, %d, %d)  x1 = %d    xn = %d   g = %d   d = %d\n", u, l, r, p[u].x1, p[u].xn, p[u].g, p[u].d);    
        return ;
    }
    print(u << 1, l, mid), print(u << 1 | 1, mid + 1, r);
    update(u);
//    printf("build(%d, %d, %d)  x1 = %d    xn = %d   g = %d   d = %d\n", u, l, r, p[u].x1, p[u].xn, p[u].g, p[u].d);
    
}

void asd(int u,int ql, int qr) {
    push(u);
    
    int l = p[u].l, r = p[u].r;
    
    if(ql > r || qr < l )return;
   
   if(l == r) {
        return ;
    }
    asd(u << 1,ql,qr), asd(u << 1 | 1, ql,qr);
    update(u); 
}



int ask(int u, int ql, int qr) {
    push(u);
    int l = p[u].l, r = p[u].r;
    if(ql > r || qr < l) return 0;
    if(ql <= l && r <= qr) {
//        printf("%d: (%d, %d) = %d\n", u, ql, qr, p[u].d);
        return p[u].d;
    }
    return gcd(ask(u << 1, ql, qr), ask(u << 1 | 1, ql, qr));
}

void change(int u, int ql, int qr, int x) {
    push(u);
    int l = p[u].l, r = p[u].r;
    if(ql > r || qr < l) return ;
    if(ql <= l && r <= qr) {
        p[u].tag += x;
        return ;
    }
    change(u << 1, ql, qr, x), change(u << 1 | 1, ql, qr, x);
    update(u);
}

void dfs(int u) {
    sz[u] = 1;
    deep[u] = deep[fa[u]] + 1;
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(v != fa[u]) {
            fa[v] = u;
            dfs(v);
            sz[u] += sz[v];
            if(sz[v] > sz[son[u]]) son[u] = v;
        }
    }
}

int dfn[N];

void dfs(int u, int tp) {
    dfn[u] = ++ cnt;
    val[cnt] = tmp[u];
    top[u] = tp;
    
//    printf("son[%d] = %d\n", u, son[u]);
    
    if(son[u]) dfs(son[u], tp);
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(v != fa[u] && v != son[u]) {
            dfs(v, v);
        }
    }
}

int n, q;

int query(int u, int v) {
    int ret = 0;
    while(top[u] != top[v]) {
        if(deep[top[u]] < deep[top[v]]) swap(u, v);

//        printf("ask(%d, %d) = %d\n", dfn[top[u]], dfn[u], ask(1, dfn[top[u]], dfn[u]));

        ret = gcd(ret, ask(1, dfn[top[u]], dfn[u]));

        u = fa[top[u]];
    }
    if(deep[u] > deep[v]) swap(u, v);
    
//    printf("(%d, %d)\n", dfn[u], dfn[v]);
//    
//    cout << "ret = " << ret << endl;
//    
//    printf("ask(%d, %d) = %d\n", dfn[u], dfn[v], ask(1, dfn[u], dfn[v]));
    
    ret = gcd(ret, ask(1, dfn[u], dfn[v]));
    return ret;
}

void modify(int u, int v, int x) {
    while(top[u] != top[v]) {
        if(deep[top[u]] < deep[top[v]]) swap(u, v);
        
        
//    printf("change: (%d, %d)\n", dfn[top[u]], dfn[u]);
        
        change(1, dfn[top[u]], dfn[u], x);
        u = fa[top[u]];
    }
    if(deep[u] > deep[v]) swap(u, v);
    
//    printf("change: (%d, %d)\n", dfn[u], dfn[v]);
    
    change(1, dfn[u], dfn[v], x);
}

int main() {
    
    #ifndef ONLINE_JUDGE
    
    freopen("data.in", "r", stdin);
    
    #endif
    
    scanf("%d", &n);
    for(int i = 1, u, v ; i < n ; ++ i) {
        scanf("%d%d", &u, &v), u ++, v ++;
        add(u, v), add(v, u);
    }
    
    for(int i = 1 ; i <= n ; ++ i) scanf("%d", &tmp[i]);
    
    // build
    dfs(1), dfs(1, 1);
    
    build(1, 1, n);
    
    scanf("%d", &q);
    for(int i = 1 ; i <= q ; ++ i) {
        char op[5]; int u, v, x;
        scanf("%s%d%d", op, &u, &v), u ++, v ++;
        if(op[0] == 'F') {
            printf("%d\n", query(u, v));
        } else {
            scanf("%d", &x);
            modify(u, v, x);
            
//            if(n <= 1000) asd(1, 1, n);
//            else {
//                if(i % 100 == 0) asd(1, 1, n);
//                else if(i % 500 == 0) asd(1, min(dfn[u], dfn[v]), max(dfn[u], dfn[v]));
//            }
            
//            puts("\n!!!!!!!!!!");
//            print(1, 1, n);
//            puts("--------\n");
        }
    }
}
