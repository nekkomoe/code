// 二分答案，然后tarjn缩点后跑dp

#include <cstdio>
#include <cctype>

const int N = 2e5 + 10;

int n, m, T;

int head[N], rest[N], to[N];

int tot, wid[N];

int dfn[N], low[N], ins[N];

int clk, cnt, id[N];

int in[N], out[N], mx, mn;

int s[N], p, mid;

int beg[N], nxt[N], target[N], total;

int ss, tt;

int f[N];

inline int max(int a, int b) {
	return a > b ? a : b;
}

inline int min(int a, int b) {
	return a < b ? a : b;
}

inline void read(int &x) {
	x = 0;
	char c = getchar();
	while(!isdigit(c)) c = getchar();
	while(isdigit(c)) x = x * 10 + c - '0', c = getchar();
}

inline void add(int u, int v, int w) {
	to[++ tot] = v, wid[tot] = w, rest[tot] = head[u], head[u] = tot;
}

void tarjan(int u) {
    dfn[u] = low[u] = ++ clk;
    s[++ p] = u;
    ins[u] = 1;
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(wid[i] > mid) continue;
        if(!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if(ins[v]){
            low[u] = min(low[u], dfn[v]);
        }
    }
    if(dfn[u] == low[u]) {
        ++ cnt;
        int v;
        do {
            ins[v = s[p --]] = 0;
            id[v] = cnt;
        } while(u != v);
    }
}

inline void insert(int u, int v) {
	target[++ total] = v;
	nxt[total] = beg[u];
	beg[u] = total;
}

int dfs(int u) {
	if(f[u]) return f[u];
	if(u == tt) return f[u] = 1;
	int ret = 0;
	for(int i = beg[u] ; i ; i = nxt[i]) {
		ret = max(ret, dfs(target[i]));
	}
	return f[u] = ret + 1;
}

bool check() {
	// clear
	p = cnt = clk = 0;
	ss = tt = total = 0;

	for(int u = 1 ; u <= n ; ++ u) {
		beg[u] = id[u] = dfn[u] = 0;
		ins[u] = in[u] = out[u] = 0;
		f[u] = 0;
	}

	for(int u = 1 ; u <= n ; ++ u) {
		if(!dfn[u]) {
			tarjan(u);
		}
	}
	for(int u = 1 ; u <= n ; ++ u) {
		for(int i = head[u] ; i ; i = rest[i]) {
			int v = to[i];
			if(wid[i] > mid) continue;
			if(id[u] != id[v]) {
				++ in[id[v]];
				++ out[id[u]];
				insert(id[u], id[v]);
			}
		}
	}
	if(cnt == 1) {
		return 1;
	} else {
		for(int u = 1 ; u <= cnt ; ++ u) {
			if(in[u] == 0) {
				if(ss) return 0;
				else ss = u;
			}
			if(out[u] == 0) {
				if(tt) return 0;
				else tt = u;
			}
		}
		return dfs(ss) == cnt;
	}
}

int main() {
	read(T);
	while(T --) {
		read(n), read(m);
		for(int i = 1 ; i <= n ; ++ i) head[i] = 0;
		tot = 0;
		mx = 0;
		mn = (int) 1e9;
		for(int i = 1, u, v, w ; i <= m ; ++ i) {
			read(u), read(v), read(w);
			add(u, v, w);
			mx = max(mx, w);
			mn = min(mn, w);
		}

		int l = mn, r = mx;
		mid = r + 1;
		if(!check()) {
			puts("Impossible");
			continue;
		}

		while(l < r) {
			mid = (l + r) >> 1;
			if(check()) r = mid;
			else l = mid + 1;
		}
		mid = l - 1;
		printf("%d\n", l - check());
	}
}