#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6 + 10;
int n, k, p, a[N], nxt[N], pos[N];

struct T { int id; }; 
bool operator < (T a, T b) { return nxt[a.id] < nxt[b.id]; }

priority_queue<T> pq;

int vis[N];

int main() {
	scanf("%d%d%d", &n, &k, &p);
	for(int i = 1, x ; i <= p ; ++ i) scanf("%d", &a[i]);
	for(int i = 1 ; i <= n ; ++ i) pos[i] = p + 1;
	for(int i = p ; i ; -- i) nxt[i] = pos[a[i]], pos[a[i]] = i;
	int ans = 0;
	for(int i = 1 ; i <= p ; ++ i) {
//		cout << "run in: " << i << " nxt = " << nxt[i] << endl;
		if(!vis[a[i]]) {
			++ ans;
//			cout << "get: " << a[i] << endl;
			if(pq.size() == k) {
//				cout << "del: " << pq.top().id << endl;
				vis[a[pq.top().id]] = 0, pq.pop();
			}
			pq.push((T) { i });
			vis[a[i]] = 1;
		} else ++ k, pq.push((T) { i }); 
	}
	printf("%d\n", ans);
}
