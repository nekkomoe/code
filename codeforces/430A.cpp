#include "bits/stdc++.h"
using namespace std;
int n, m, col[110];
vector<pair<int, int> > p;
int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1, x ; i <= n ; ++ i) {
        scanf("%d", &x);
        p.push_back(make_pair(x, i));
    }
    for(int i = 1, l, r ; i <= m ; ++ i) scanf("%d%d", &l, &r);
    sort(p.begin(), p.end());
    for(int i = 0 ; i < n ; ++ i) col[p[i].second] = i & 1;
    for(int i = 1 ; i <= n ; ++ i) printf("%d ", col[i]); puts("");
}
