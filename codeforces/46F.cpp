#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1010;
int n, m, k, x[N], y[N];

struct DSU {
	int fa[N * 2], key[N], room[N];
	DSU() {
		for(int i = 1 ; i <= 2000 ; ++ i) fa[i] = i; 
	}
	int get(int x) {
		return x == fa[x] ? x : fa[x] = get(fa[x]);
	}
	void merge(int x, int y) {
		fa[get(x)] = get(y);
	}
} d[2];

map<string, int> mp;

int main() {
	scanf("%d%d%d", &n, &m, &k);
	for(int i = 1 ; i <= m ; ++ i) {
		scanf("%d%d", &x[i], &y[i]);
	}
	for(int t = 0 ; t <= 1 ; ++ t) {
		for(int i = 1, room, tot ; i <= k ; ++ i) {
			char name[20];
			scanf("%s%d%d", name, &room, &tot);
			int id;
			if(mp.find(name) == mp.end()) id = mp[name] = i;
			else id = mp[name];
			d[t].room[id] = room;
			while(tot --) {
				int x; scanf("%d", &x);
				d[t].key[x] = room;
			}
		}
		for(int i = 1 ; i <= 2 * n ; ++ i)
			for(int j = 1 ; j <= m ; ++ j)
				if(d[t].get(x[j]) != d[t].get(y[j])
				&& (d[t].get(d[t].key[j]) == d[t].get(x[j])
				|| d[t].get(d[t].key[j]) == d[t].get(y[j])))
					d[t].merge(x[j], y[j]);
	}
	for(int i = 1 ; i <= m ; ++ i)
		if(d[0].get(d[0].key[i]) != d[0].get(d[1].key[i])
		|| d[1].get(d[0].key[i]) != d[1].get(d[1].key[i]))
			return puts("NO"), 0;
	for(int i = 1 ; i <= k ; ++ i)
		if(d[0].get(d[0].room[i]) != d[0].get(d[1].room[i])
		|| d[1].get(d[0].room[i]) != d[1].get(d[1].room[i]))
			return puts("NO"), 0;
	puts("YES");
}
