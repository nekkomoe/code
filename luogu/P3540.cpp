#include <bits/stdc++.h>
//#include <unordered_map>
using namespace std;
typedef long long ll;
const int N = 310;
int n; ll a[N * N];

ll num[N]; vector<vector<ll> > out; int cnt[N * N];
unordered_map<ll, int> tra;
//map<ll, int> tra;
ll ans[310][310]; int T;

void get() {
    int q = 1; cnt[0] = 0;
    for(int i = 1 ; i <= n * (n - 1) / 2 ; ++ i) cnt[tra[a[i]]] = 0;
    for(int i = 1 ; i <= n * (n - 1) / 2 ; ++ i) ++ cnt[tra[a[i]]];
    for(int i = 2 ; i <= n ; ++ i) {
        while(!cnt[tra[a[q]]]) ++ q;
        num[i] = a[q] - num[1];
        for(int j = 1 ; j < i ; ++ j)
            if(-- cnt[tra[num[j] + num[i]]] < 0)
                return ;
    }
    ++ T; for(int i = 1 ; i <= n ; ++ i) ans[T][i] = num[i];
}

int main() {
//	freopen("2797.in", "r", stdin);
//	freopen("2797.out", "w", stdout); 
	scanf("%d", &n);
	for(int i = 1 ; i <= n * (n - 1) / 2 ; ++ i) scanf("%lld", &a[i]);
    sort(a + 1, a + 1 + n * (n - 1) / 2);
    tra[0] = 0; for(int i = 1, tot = 0 ; i <= n * (n - 1) / 2 ; ++ i) tra[a[i]] = ++ tot;
    
    unordered_map<ll, int> vis;
//	map<ll, int> vis; 
    for(int i = 3 ; i <= n ; ++ i) {
        num[1] = (a[1] + a[2] - a[i]);
        if(num[1] <= 0) break;
        if((num[1] & 1) || vis[num[1] /= 2]) continue;
        vis[num[1]] = 1, get();
    }
    printf("%d\n", T);
	for(int t = 1 ; t <= T ; ++ t, puts(""))
    	for(int i = 1 ; i <= n ; ++ i)
    		printf("%d ", ans[t][i]);
} 
