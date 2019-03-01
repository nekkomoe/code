#include "bits/stdc++.h"
typedef long long ll;
using namespace std;
const int N = 1e6 + 10;
priority_queue<pair<ll, int>, vector<pair<ll, int> >, greater<pair<ll, int> > > p, q;
int l, n, m, L[N], nekon[N], nekom[N];

int main() {
    scanf("%d%d%d", &l, &n, &m);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &nekon[i]);
        p.push(make_pair(nekon[i], i));
    }
    for(int i = 1 ; i <= m ; ++ i) {
        scanf("%d", &nekom[i]);
        q.push(make_pair(nekom[i], i));
    }
    for(int i = 1 ; i <= l ; ++ i) {
        pair<ll, int> pr = p.top(); p.pop();
        L[i] = pr.first;
        pr.first += nekon[pr.second];
        p.push(pr);
    }
    ll ans = 0;
    for(int i = l ; i ; -- i) {
        pair<ll, int> pr = q.top(); q.pop();
        ans = max(ans, L[i] + pr.first);
        pr.first += nekom[pr.second];
        q.push(pr);
    }
    printf("%lld\n", ans);
}
