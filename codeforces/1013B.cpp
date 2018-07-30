#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
int n, x;
map<int, int> cnt;
int main() {
    int ans = 0x3f3f3f3f;
    scanf("%d%d", &n, &x);
    for(int i = 1, t ; i <= n ; ++ i) {
        scanf("%d", &t);
        if(cnt.find(t) != cnt.end()) {
            ans = min(ans, cnt[t]);
        } else if(cnt.find(t & x) != cnt.end()) {
            ans = min(ans, cnt[t & x] + 1);
        }
        cnt[t] = 0;
        if(cnt.find(t & x) == cnt.end()) cnt[t & x] = 1;
    }
    printf("%d\n", ans == 0x3f3f3f3f ? -1 : ans);
}
