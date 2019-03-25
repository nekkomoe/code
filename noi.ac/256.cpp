#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
int pos[2600], tra[50][50], dig[30], top;
vector<int> pak;
ll f[30][50][2600];

ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}
ll lcm(ll a, ll b) {
    return a / gcd(a, b) * b;
}

ll dfs(int stp, int LCM, int MOD, int LIM) {
    ll &res = f[stp][LCM][MOD];
    if(stp == 0) {
        return MOD % pak[LCM] == 0;
    } else if(!LIM && res != -1) {
        return res;
    } else {
        ll sum = 0;
        for(int i = (LIM ? dig[stp] : 9) ; i >= 0 ; -- i) {
            sum += dfs(stp - 1, tra[LCM][i], (MOD * 10 + i) % 2520, LIM && i == dig[stp]);
        }
        return LIM ? sum : res = sum;
    }
}

ll sol(ll x) {
    top = 0;
    while(x) {
        dig[++ top] = x % 10;
        x /= 10;
    }
    return dfs(top, 1, 0, 1);
}

void runprog() {
    ll l, r;
    scanf("%lld%lld", &l, &r);
    printf("%lld\n", sol(r) - sol(l - 1));
}

int main() {
    memset(f, -1, sizeof f);
    pak.push_back(1);
    for(int i = 1 ; i <= 2520 ; ++ i) {
        if(2520 % i == 0) {
            pak.push_back(i);
        }
    }
    for(int i = 0 ; i < pak.size() ; ++ i) {
        pos[pak[i]] = i;
    }
    for(int i = 0 ; i < pak.size() ; ++ i) {
        for(int j = 0 ; j < pak.size() ; ++ j) {
            tra[i][j] = pos[lcm(pak[i], pak[j])];
            // cout << tra[i][j] << endl;
        }
    }
    int t; scanf("%d", &t);
    while(t --){
        runprog();
    }
}
