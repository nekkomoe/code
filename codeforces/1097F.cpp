#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1e5 + 10, M = 7010;

int mu[N], pri[N], tot, vis[N], n, q;

bitset<M> b1[N], b2[M];

void init(int n) {
    mu[1] = 1;
    for(int i = 2 ; i <= n ; ++ i) {
        if(!vis[i]) {
            pri[++ tot] = i;
            mu[i] = -1;
        }
        for(int j = 1 ; j <= tot && i * pri[j] <= n ; ++ j) {
            vis[i * pri[j]] = 1;
            if(i % pri[j] == 0) break;
            mu[i * pri[j]] = -mu[i];
        }
    }
    
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 1 ; i * j <= n ; ++ j) {
            if(mu[j]) {
                b2[i][i * j] = 1;
            }
        }
    }
}

int main() {
	ios :: sync_with_stdio(0);
    scanf("%d%d", &n, &q);
    init(7000);
    for(int i = 1 ; i <= q ; ++ i) {
        int op; scanf("%d", &op);
        if(op == 1) {
            int x, v; scanf("%d%d", &x, &v);
            b1[x] = 0;
            for(int k = 1 ; k * k <= v ; ++ k) {
                if(v % k == 0) {
                    int u = v / k;
                    b1[x][k] = b1[x][k] ^ 1;
                    if(u != k) {
                        b1[x][u] = b1[x][u] ^ 1;
                    }
                }
            }
        } else if(op == 2) {
            int x, y, z; scanf("%d%d%d", &x, &y, &z);
            b1[x] = b1[y] ^ b1[z];
        } else if(op == 3) {
            int x, y, z; scanf("%d%d%d", &x, &y, &z);
            b1[x] = b1[y] & b1[z];
        } else if(op == 4) {
            int x, v; scanf("%d%d", &x, &v);
            putchar(((b1[x] & b2[v]).count() & 1) + '0'); 
        }
    }
}

