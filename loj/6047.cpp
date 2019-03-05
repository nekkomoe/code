#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 5e5 + 10;

int n, a[N], X[N], Y[N];

namespace allai1 {
    int check() {
        for(int i = 1 ; i <= n ; ++ i) {
            if(a[i] != 1) {
                return 0;
            }
        }
        return 1;
    }
    void sol() {
        int ans = 0;
        multiset<int> ms;
        for(int i = 1 ; i <= n ; ++ i) {
            ms.insert(Y[i]);
        }
        for(int i = 1 ; i <= n ; ++ i) {
            auto t = ms.lower_bound(X[i]);
            if(t == ms.end()) {
                ms.erase(ms.begin());
            } else {
                ++ ans;
                ms.erase(t);
            }
        }
        printf("%d\n", ans);
    }
}

namespace pf {
    
    int cnt[N];
    multiset<int> g;
    vector<int> vec[N];

    void sol() {
        for(int i = 1 ; i <= n ; ++ i) {
            vec[a[i]].push_back(Y[i]);
        }
        int pos = 1, posval = 0x3f3f3f3f;
        for(int i = 1 ; i <= n ; ++ i) {
            cnt[i] = cnt[i - 1] + vec[i].size();
        }

        for(int i = 1 ; i <= n ; ++ i) {
            if(posval > cnt[i] - i) {
                posval = cnt[i] - i;
                pos = (i == n ? 1 : i + 1);
            }
        }

        int ans = 0;
        for(int i = 1 ; i <= n ; ++ i) {

            for(int t: vec[pos]) {
                g.insert(t);
            }

            auto t = g.lower_bound(X[pos]);
            if(t != g.end()) {
                ++ ans;
                g.erase(t);
            } else {
                g.erase(g.begin());
            }

            pos = pos == n ? 1 : pos + 1;
        }
        printf("%d\n", ans);
    }
}

int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &a[i]);
    }
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &X[i]);
    }
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &Y[i]);
    }
    if(allai1 :: check()) {
        allai1 :: sol();
    } else {
        pf :: sol();
    }
}
