#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 1010;

int n, m;

ll w[N], val[N];

void sol() {
    vector<pair<ll, ll> > pak, tmp;
    for(int i = 1 ; i <= n ; ++ i) {
        if(w[i] <= m) {
            for(int j = pak.size() - 1 ; j >= 0 ; -- j) {
                if(pak[j].first + w[i] <= m) {
                    pak.push_back(make_pair(pak[j].first + w[i], pak[j].second + val[i]));
                }
            }
            pak.push_back(make_pair(w[i], val[i]));
        }
        tmp.clear();
        for(int j = 0 ; j < pak.size() ; ++ j) {
            int flag = 1;
            for(int k = 0 ; k < pak.size() ; ++ k) {
                if(j == k) continue;
                if(pak[k].first <= pak[j].first && pak[k].second >= pak[j].second) {
                    flag = 0;
                    break;
                }
            }
            if(flag) {
                tmp.push_back(pak[j]);
            }
        }
        pak = tmp;
    }
    ll ans = 0;
    for(int i = 0 ; i < pak.size() ; ++ i) {
        ans = max(ans, pak[i].second);
    }
    printf("%lld\n", ans);
}

int main() {
    while(scanf("%d%d", &n, &m) == 2) {
        for(int i = 1 ; i <= n ; ++ i) {
            scanf("%lld%lld", &w[i], &val[i]);
        }
        sol();
    }
}
