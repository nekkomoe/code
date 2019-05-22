#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

vector<ll> num;

void gcd(ll n, ll m) {
    if(n < m) swap(n, m);
    if(m == 0) {
        return ;
    }
    gcd(n % m, m);
    num.push_back(n / m == 1 ? 1 : 2);
}

void runprog() {
    num.clear();
    ll n, m; scanf("%lld%lld", &n, &m);
    gcd(n, m);
    // for(ll x: num) {
    //     printf("%lld, ", x);
    // } puts("");
    if(num.empty()) {
        puts("Rich");
    } else {
        int SG = 0;
        for(int i = 0 ; i < num.size() ; ++ i) {
            int x = num[i];
            if(x == 2) {
                // 有两个
                SG = 1;
            } else {
                // 有一个
                if(SG == 0) {
                    SG = 1;
                } else {
                    SG = 0;
                }
            }
        }
        puts(SG ? "Ari" : "Rich");
    }
}

int main() {
    int t; scanf("%d", &t);
    while(t --) {
        runprog();
    }
}
