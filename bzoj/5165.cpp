// 题意：多次询问，每次查询k个点的lca
// 题解：相当于查询dfs序最大和最小的两个点的lca
// 标签：tarjan，lca，dfs序

#pragma GCC optimize(2)

#include <cctype>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int N = 3000010;

const int Bufsiz = 3e7;	// buffer size 
inline char get_c() {
	static char buf[Bufsiz];	// buffer
	static char *head = buf + Bufsiz;
	static char *tail = buf + Bufsiz;
	if (head == tail)	// at the end of buffer
		tail = buf + fread(head = buf, 1, BUFSIZ, stdin);	// reload from STDIN
	return *head++;
}
inline int get_i() {
	int res = 0;	// result
	int chr = get_c();	// current char
	for (; chr < 48; chr = get_c());
	for (; chr > 47; chr = get_c()) res = res * 10 + chr - 48;
	return res;
}

int T, query[1010][1010], n, m, fa[N];

int head[N], rest[2 * N], to[2 * N], tot, hd[N], nxt[2 * N], cnt, ans[N], vis[N], dfn[N], rev[N], flag[N], ddddddddd;

#define read(x) (x =  get_i())

#define add(u, v) (to[++ tot] = v, rest[tot] = head[u], head[u] = tot)

inline int get(int x) { return x == fa[x] ? x : fa[x] = get(fa[x]); }

struct Q { int v, id; } val[2 * N];

#define psh(from, v, id) (val[++ cnt] = (Q) {v, id}, nxt[cnt] = hd[from], hd[from] = cnt)

inline void ddd(int u) {
    rev[dfn[u] = ++ ddddddddd] = u;
    for(int i = head[u] ; i ; i = rest[i]) ddd(to[i]);
}

inline void dfs(int u) {fr
    vis[u] = 1;
    for(int i = hd[u] ; i ; i = nxt[i]) {
        if(vis[val[i].v]) {
            ans[val[i].id] = get(val[i].v);
        }
    }
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        
            dfs(v);
            fa[get(v)] = u;
        
    }
}

int main() {
    ++ n, read(T);
    for(int i = T, x, c ; i ; -- i) {
        while(!isalpha(c = get_c()));
        if(c == 'A') {
            read(x);
            ++ n, add(x, n);
        } else {
            ++ m, read(query[m][0]);
            for(int j = query[m][0] ; j ; -- j) read(query[m][j]);
        }
        fa[i] = i;
    }
    
    ddd(1);
    
    for(int i = 1 ; i <= m ; ++ i) {
        int mn = n, mx = 1;
        for(int j = query[i][0] ; j ; -- j) mn = min(mn, dfn[query[i][j]]), mx = max(mx, dfn[query[i][j]]);
        mn = rev[mn], mx = rev[mx];
        psh(mn, mx, i), psh(mx, mn, i);
    }
    dfs(1);
    for(int i = 1 ; i <= m ; ++ i) printf("%d\n", ans[i]);
}
