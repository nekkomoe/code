#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1e5 + 10;

int n, q, a[N], sum[N], mu[N], vis[N], pri[N], tot;
 
int upd(int n, int v) {
    int res = 0;
    for(int i = 1 ; i * i <= n ; ++ i) {
        if(n % i == 0) {
            int j = n / i;
            sum[i] += v, res += sum[i] * mu[i];
            if(i != j) sum[j] += v, res += sum[j] * mu[j];
        }
    }
    return res;
}

int main() {
    ios :: sync_with_stdio(0);
    cin >> n >> q;
    mu[1] = 1;
    for(int i = 2 ; i <= n ; ++ i) {
        if(!vis[i]) {
            pri[++ tot] = i;
            mu[i] = -1;
        }
        for(int j = 1 ; j <= tot && i * pri[j] <= n ; ++ j) {
            vis[i * pri[j]] = 1;
            if(i % pri[j]) mu[i * pri[j]] = -mu[i];
            else break;
        }
    }
    
    for(int i = 1 ; i <= n ; ++ i) {
        cin >> a[i];
        upd(i, a[i]);
    }
    
    for(int i = 1 ; i <= q ; ++ i) {
        int op, pos, val;
        cin >> op >> pos;
        if(op == 1) {
            cin >> val;
            upd(pos, val - a[pos]); 
            a[pos] = val;
        } else {
            cout << upd(pos, 0) << endl;
        }
    }
}

