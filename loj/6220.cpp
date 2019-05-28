#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e6 + 10;

int n, pos[N], ids[N];
ll a[N], s[N];
bool cmp(int i, int j) {
    return make_pair(a[i], i) < make_pair(a[j], j);
}

int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%lld", &a[i]);
        ids[i] = i;
        pos[i] = -1;
    }
    sort(ids + 1, ids + 1 + n, cmp);
    sort(a + 1, a + 1 + n);
    pos[0] = 0;
    for(int i = 1 ; i <= n ; ++ i) {
        s[i] = (s[i - 1] + a[i] % n) % n;
        if(pos[s[i]] != -1) {
            for(int j = pos[s[i]] + 1 ; j <= i ; ++ j) {
                printf("%d %lld\n", ids[j], a[j]);
            }
            return 0;
        }
        pos[s[i]] = i;
    }
}
