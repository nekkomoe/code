#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int ch[N][26], len[N], pre[N], tot, last, n, sg[N], tmp[N]; char s[N]; bool vis[N];
inline int nd(int l) { return len[++ tot] = l, memset(ch[tot], vis[tot] = 0, sizeof ch[tot]), tot; }
inline void ins(int c) {
	int p, np, q, nq;
	pre[last = np = nd(len[p = last] + 1)] = 1;
	while(p && !ch[p][c]) ch[p][c] = np, p = pre[p];
	if(p) {
		pre[np] = q = ch[p][c];
		if(len[p] + 1 != len[q]) {
			pre[nq = nd(len[p] + 1)] = pre[q], memcpy(ch[pre[q] = pre[np] = nq], ch[q], sizeof ch[q]);
			while(p && ch[p][c] == q) ch[p][c] = nq, p = pre[p];
		}
	}
}
inline void dfs(int u) {
	if(vis[u]) return ;
	vis[u] = 1;
	for(int c = 0 ; c < 26 ; ++ c) if(ch[u][c]) dfs(ch[u][c]);
	int cnt = 0;
	for(int c = 0 ; c < 26 ; ++ c) if(ch[u][c]) tmp[cnt ++] = sg[ch[u][c]];
	sg[u] = cnt;
	if(cnt) {
		sort(tmp, tmp + cnt), cnt = unique(tmp, tmp + cnt) - tmp;
		sg[u] = cnt;
		for(int i = 0 ; i < cnt ; ++ i) if(i != tmp[i]) { sg[u] = i; break; }
	}
}
int main() {
	while(scanf("%s%d", s + 1, &n) == 2) {
		int ans = tot = 0;
		last = nd(0);
		for(int i = 1 ; s[i] ; ++ i) ins(s[i] - 'a');
		dfs(1);
		for(int i = 1 ; i <= n ; ++ i) {
			scanf("%s", s + 1);
			int x = 1;
			for(int j = 1 ; s[j] ; ++ j) x = ch[x][s[j] - 'a'];
			ans ^= sg[x];
		}
		puts(ans ? "Alice" : "Bob");
	}
}
