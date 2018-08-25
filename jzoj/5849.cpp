#include "bits/stdc++.h"
using namespace std;
const int N = 1e5 + 10;
int n, m;
struct T {
    int a, b;
} t[N];

bool operator < (T a, T b) {
    return a.a < b.a;
}

priority_queue<int> lrg;
priority_queue<int, vector<int>, greater<int> > sml;

void ins(int x) {
    if(lrg.size() && x > lrg.top()) sml.push(x);
    else lrg.push(x);
}

int getk(int k) {
    // k = min(k, int(sml.size() + lrg.size()));
    while(lrg.size() > k) {
        sml.push(lrg.top());
        lrg.pop();
    }
    while(lrg.size() < k) {
        lrg.push(sml.top());
        sml.pop();
    }
    return lrg.top();
}

void sol() {
    while(lrg.size()) lrg.pop();
    while(sml.size()) sml.pop();
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d%d", &t[i].a, &t[i].b);
    }
    long long ans = 0;
    sort(t + 1, t + 1 + n);
    for(int i = n, mn = t[n].b ; i ; -- i) {
        // [i, n]
        ins(t[i].b);
        mn = min(mn, t[i].b);
        int k = m - (i - 1);
        if(k < 0) continue;
        // cout << "k = " << k << endl;
        if(k == 0) ans = max(ans, 1ll * t[i].a * mn);
        else {
            // vector<int> tmp; tmp.push_back(-1);
            // for(int j = i ; j <= n ; ++ j) tmp.push_back(t[j].b);
            // sort(tmp.begin(), tmp.end());
            // ans = max(ans, 1ll * t[i].a * tmp[k + 1]);
            ans = max(ans, 1ll * t[i].a * getk(k + 1));
        }
    }
    printf("%lld\n", ans);
}

int main() {
    freopen("d.in", "r", stdin);
    freopen("d.out", "w", stdout);
    int t; scanf("%d", &t);
    while(t --) sol();
}
