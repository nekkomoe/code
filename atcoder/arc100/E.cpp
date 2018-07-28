#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 1e6 + 10;
int n, a[N], len;
pair<int, int> f[N];
void upd(pair<int, int> &tar, pair<int, int> &src) {
    int val[4] = { tar.first, tar.second, src.first, src.second };
    sort(val, val + 4);
    tar = make_pair(val[3], val[2]);
}
int main() {
    scanf("%d", &n), len = 1 << n;
    for(int i = 0 ; i < len ; ++ i) scanf("%d", &a[i]), f[i] = make_pair(a[i], -1);
    for(int j = 0 ; j < n ; ++ j) {
        for(int i = 0 ; i < len ; ++ i) {
            if(((i >> j) & 1) == 0) {
                int t = i | (1 << j);
                upd(f[t], f[i]);
            }
        }
    }
    for(int i = 1, ans = -1 ; i < len ; ++ i) {
        ans = max(ans, f[i].first + f[i].second);
        printf("%d\n", ans);
    }
}
