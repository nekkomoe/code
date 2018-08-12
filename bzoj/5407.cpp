#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const int N = 2e5 + 10;
struct REL {
	int x, y;
} rel[N];

int n, m;

ull A, B, C, cnt[4], ans;

vector<int> lt[N], gt[N], g[N];

int deg[N];

ull sumA[N], sumB[N], sumC[N];

ull calc1(int x, int y) {
	if(x > y) swap(x, y);
	ull res = 0;
	
	if(x > 0) {
		res += sumA[x - 1] + x * (B * x + C * y);
	}
	
	if(x + 1 < y) {
		res += (y - x - 1) * (A * x + C * y) + (sumB[y - 1] - sumB[x]);
	}
	
	if(y + 1 < n) {
		res += (n - 1 - y) * (A * x + B * y) + (sumC[n - 1] - sumC[y]);
	}
	
	return res;
}

ull calc3(int x, int y, int z) {
	if(x > y) swap(x, y);
	if(x > z) swap(x, z);
	if(y > z) swap(y, z);
	assert(x < y && y < z);
	ull res = 0;
	res += A * x + B * y + C * z;
	return res;
}

int vis[N];

void sol() {
	for(int i = 0 ; i < n ; ++ i) {
		ull c = C * i * (1ll * i * (i - 1) / 2);
		ull b = B * i * i * (n - i - 1);
		ull a = A * i * ((1ll * n - i - 1) * (n - i - 2) / 2);
		cnt[0] += a + b + c;
	}
	for(int i = 1 ; i <= m ; ++ i) {
		int x = rel[i].x, y = rel[i].y; // x < y
		gt[x].push_back(y), lt[y].push_back(x);
		++ deg[x], ++ deg[y];
		cnt[1] += calc1(x, y);
	}
	for(int i = 0 ; i < n ; ++ i) {
		if(lt[i].size()) sort(lt[i].begin(), lt[i].end());
		if(gt[i].size()) sort(gt[i].begin(), gt[i].end(), greater<int>());
		ull tot = lt[i].size() * gt[i].size();
		ull sumlt = 0, sumgt = 0, res = 0;
		int lttot = 0, gttot = 0;
		for(int _x = 0 ; _x < lt[i].size() ; ++ _x) {
			int x = lt[i][_x];
			res += sumlt + lttot * B * x + lttot * C * i;
			sumlt += A * x;
			++ lttot;
		}
		for(int _y = 0 ; _y < gt[i].size() ; ++ _y) {
			int y = gt[i][_y];
			res += gttot * A * i + gttot * B * y + sumgt;
			sumgt += C * y;
			++ gttot;
		}
		if(lt[i].size() && gt[i].size()) {
			res += sumlt * gt[i].size();
			res += B * i * tot;
			res += sumgt * lt[i].size();
		}
		cnt[2] += res;
	}
	for(int i = 1 ; i <= m ; ++ i) {
		int x = rel[i].x, y = rel[i].y;
		if(deg[x] < deg[y]) swap(x, y);
		if(deg[x] == deg[y] && x > y) swap(x, y);
		g[x].push_back(y);
	}
	for(int i = 0 ; i < n ; ++ i) {
		deg[i] = 0;
		for(int _y = 0 ; _y < g[i].size() ; ++ _y) {
			int y = g[i][_y];
			++ deg[y];
		}
		if(g[i].size()) sort(g[i].begin(), g[i].end());
	}
	queue<int> q;
	for(int i = 0 ; i < n ; ++ i) if(deg[i] == 0) q.push(i);
	while(q.size()) {
		int x = q.front(); q.pop();
		for(int _y = 0 ; _y < g[x].size() ; ++ _y) {
			int y = g[x][_y];
			if(! -- deg[y]) q.push(y);
			vis[y] = 1;
		}
		for(int _y = 0 ; _y < g[x].size() ; ++ _y) {
			int y = g[x][_y];
			for(int _z = 0 ; _z < g[y].size() ; ++ _z) {
				int z = g[y][_z];
				if(vis[z]) {
					cnt[3] += calc3(x, y, z);
				}
			}
		}
		for(int _y = 0 ; _y < g[x].size() ; ++ _y) {
			int y = g[x][_y];
			vis[y] = 0;
		}
	}
	ans = cnt[0] - cnt[1] + cnt[2] - cnt[3];
}

int main() {
	ios :: sync_with_stdio(0);
	cin >> n >> m;
	cin >> A >> B >> C;
	for(int i = 0 ; i < n ; ++ i) {
		if(i) sumA[i] += sumA[i - 1], sumB[i] += sumB[i - 1], sumC[i] += sumC[i - 1];
		sumA[i] += A * i;
		sumB[i] += B * i;
		sumC[i] += C * i;
	}
	vector<pair<int, int> > tmp;
	for(int i = 1 ; i <= m ; ++ i) {
		cin >> rel[i].x >> rel[i].y;
		assert(rel[i].x != rel[i].y);
		tmp.push_back(make_pair(min(rel[i].x, rel[i].y), max(rel[i].x, rel[i].y)));
	}
	sort(tmp.begin(), tmp.end());
	tmp.erase(unique(tmp.begin(), tmp.end()), tmp.end());
	m = tmp.size();
	for(int i = 1 ; i <= m ; ++ i) rel[i].x = tmp[i - 1].first, rel[i].y = tmp[i - 1].second;
	sol();
	cout << ans << endl;
}
