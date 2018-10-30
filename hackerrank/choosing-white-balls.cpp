#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 35;
int n, k; char str[N];

const int MOD = 2333333;

const int T = 3e6 + 10;
int head[MOD + 5], rest[T], tot;
ll idm[T]; double val[T];
void add(int id, ll hs, double va) {
	++ tot, idm[tot] = hs, val[tot] = va, rest[tot] = head[id], head[id] = tot;
}
double check(int id, ll hs) {
	for(int i = head[id] ; i ; i = rest[i])
		if(idm[id] == hs)
			return val[i];
	return -1;
}

ll hs(int stp, int s) {
	return (ll) s * 31 + stp;
}

double g[21][1 << 20]; bool vis[21][1 << 20];

double dfs(int stp, int s) {
    if(stp == k + 1) return 0;
    int len = n - stp + 1;
    double res = 0, pg = 1.0 / len;
    ll sta; int id;

//	printf("tot = %d\n", tot);
    
    if(len <= 20) {
    	if(vis[len][s])
			return g[len][s];
   		vis[len][s] = 1;
   	} else {
		sta = hs(stp, s);
		id = sta % MOD;
		for(int i = head[id] ; i ; i = rest[i])
			if(idm[i] == sta)
				return val[i];
	}
	
	for(int i = 1 ; i <= len ; ++ i) {
        int p = i, q = len - i + 1;
        
        int sx = (((s >> (p - 1)) << (p - 1)) ^ s) | ((s >> p) << (p - 1));
        int sy = (((s >> (q - 1)) << (q - 1)) ^ s) | ((s >> q) << (q - 1));
        
        double x = dfs(stp + 1, sx) + ((s >> (p - 1)) & 1);
        double y = dfs(stp + 1, sy) + ((s >> (q - 1)) & 1);
        res += pg * max(x, y);
    }
    
    if(len <= 20) {
    	g[len][s] = res;
    } else {
    	add(id, sta, res);
	}
    return res;
}

int main() {
    freopen("v.in", "r", stdin);
    freopen("v.out", "w", stdout);
    scanf("%d%d%s", &n, &k, str + 1);
    int init = 0;
    for(int i = 1 ; i <= n ; ++ i) init |= (str[i] == 'W') << (i - 1);
    printf("%.10f\n", dfs(1, init));
    
//    int tot = 0; for(int i = 0 ; i < MOD ; ++ i) tot += f[i].size();
//    printf("%d\n", tot);
}
