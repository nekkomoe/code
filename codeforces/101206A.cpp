#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

ll getans() {
    ll res = 0;
    int n; scanf("%d", &n); vector<int> a(n);
    for(int i = 0 ; i < n ; ++ i) {
        scanf("%d", &a[i]);
    }
    sort(a.begin(), a.end(), greater<int> ());
    for(int i = 0 ; i < a.size() ; i += 3) {
        for(int j = i ; j < min((int) a.size(), i + 2) ; ++ j) {
            res += a[j];
        }
    }
    return res;
}

int main() {
    int t; scanf("%d", &t);
    for(int i = 1 ; i <= t ; ++ i) {
        printf("Case #%d: %lld\n", i, getans());
    }
}
