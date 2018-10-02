#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 3e6 + 10;
int root, ch[N][26], fail[N], tot, sta[N];
char str[N];

void ins() {
	if(!root) root = ++ tot;
	int x = root;
	for(int i = 1 ; str[i] ; ++ i) {
		int c = str[i] - 'A';
		if(!ch[x][c]) ch[x][c] = ++ tot;
		x = ch[x][c];
	}
	static int tmp = 0;
	sta[x] |= 1 << (tmp ++);
}

void build() {
	queue<int> q;
	for(int i = 0 ; i < 26 ; ++ i)
		if(ch[root][i])
			fail[ch[root][i]] = root,
			q.push(ch[root][i]);
		else ch[root][i] = root;
	while(q.size()) {
		int u = q.front(); q.pop();
		for(int i = 0 ; i < 26 ; ++ i) {
			if(ch[u][i])
				fail[ch[u][i]] = ch[fail[u]][i],
				q.push(ch[u][i]);
			else
				ch[u][i] = ch[fail[u]][i];
			int f = fail[u];
			while(f && !sta[f]) f = fail[f];
			sta[u] |= sta[f];
		}
	}
}

int fa[N], out[N], top, n; bool vis[1010][1 << 13];

struct T { int u, id, s; };

void print(int x) {
	if(!x) return ;
	print(fa[x]);
	putchar('A' + out[x]);
}

void bfs() {
	queue<T> q;
	q.push((T) { root, 0, 0 });
	while(q.size()) {
		T t = q.front(); q.pop();
		int u = t.u, id = t.id, s = t.s;

		if(s == (1 << n) - 1) {
			print(id);
			exit(0);
		}
		if(vis[u][s]) continue;

		// cout << u << ' ' << id << ' ' << s << endl;
		
		vis[u][s] = 1;
		for(int i = 0 ; i < 26 ; ++ i) {
			if(vis[ch[u][i]][s | sta[ch[u][i]]]) continue;
			out[++ top] = i, fa[top] = id;
			q.push((T) { ch[u][i], top, s | sta[ch[u][i]] });
		}
	}
}

int main() {
	scanf("%d", &n);
	for(int i = 1 ; i <= n ; ++ i) {
		scanf("%s", str + 1);
		ins();
	}
	build();
	bfs();
}