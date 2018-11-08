#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <queue>
using namespace std; typedef long long ll;
const int N = 1e5 + 10;
ll a, b, c, h, d[N];
int inq[N]; queue<int> q; 

int main() {
    cin >> h >> a >> b >> c;
    if(a > b) swap(a, b); if(a > c) swap(a, c);
    memset(d, 0x3f, sizeof d);
    d[1 % a] = 1;
    q.push(1 % a), inq[1 % a] = 1;
    while(q.size()) {
        int u = q.front(); q.pop(); inq[u] = 0;
        int v = (u + b) % a;
        if(d[v] > d[u] + b) {
            d[v] = d[u] + b;
            if(!inq[v]) {
                q.push(v);
                inq[v] = 1;
            }
        }
        v = (u + c) % a;
        if(d[v] > d[u] + c) {
            d[v] = d[u] + c;
            if(!inq[v]) {
                q.push(v);
                inq[v] = 1;
            }
        }
    }
    ll ans = 0;
    for(int i = 0 ; i < a ; ++ i) {
        if(d[i] <= h) {
            ans += ((h - d[i]) / a) + 1;
        }
    }
    printf("%lld\n", ans);
}
