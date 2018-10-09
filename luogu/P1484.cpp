// 贪心 堆
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 500000 + 10;
struct T { int id; ll val; };
bool operator < (T a, T b) { return a.val < b.val; }
priority_queue<T> pq;
ll a[N]; int l[N], r[N], vis[N];

int main() {
	int n, k; cin >> n >> k;
	for(int i = 1 ; i <= n ; ++ i) cin >> a[i], pq.push((T) { i, a[i] }), l[i] = i - 1, r[i] = i + 1;
	ll ans = 0;
	r[0] = 1, l[n + 1] = n;
	for(int i = 1 ; i <= k ; ++ i) {
		while(vis[pq.top().id]) pq.pop();
		T t = pq.top(); pq.pop();
		if(t.val < 0) break;
		ans += t.val;
		int id = t.id;
		t.val = a[id] = -a[id] + a[l[id]] + a[r[id]];
		vis[l[id]] = vis[r[id]] = 1;
		l[id] = l[l[id]], r[id] = r[r[id]];
		l[r[id]] = id, r[l[id]] = id;
		pq.push(t);
	}
	printf("%lld\n", ans);
}

// wqs二分
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 500000 + 10;
int n, k, _a[N]; ll a[N];

struct T {
    ll res, cnt;
    T(ll res = 0, ll cnt = 0) : res(res), cnt(cnt) { }
    T operator + (ll x) {
        return T(res + x, cnt + 1);
    }
} f[N][2];

bool operator < (T a, T b) {
    if(a.res != b.res) return a.res < b.res;
    else return a.cnt > b.cnt;
}

T check(ll cost) {
    for(int i = 1 ; i <= n ; ++ i) a[i] = _a[i] - cost;
    for(int i = 1 ; i <= n ; ++ i) {
        f[i][0] = max(f[i - 1][0], f[i - 1][1]);
        f[i][1] = f[i - 1][0] + a[i];
    }
    return max(f[n][0], f[n][1]);
}

int main() {
    scanf("%d%d", &n, &k);
    for(int i = 1 ; i <= n ; ++ i) scanf("%d", &_a[i]);
    ll l = 0, r = 1e17, ans = 0;
    
    while(l <= r) {
        ll mid = (l + r) / 2;
        T t = check(mid);
        if(t.cnt <= k) {
            ans = t.res + k * mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    printf("%lld\n", ans);
}