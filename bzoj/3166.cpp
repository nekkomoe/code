#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 50000 + 10;

int n, a[N], b[N], ans;

int cmp(int x, int y) { return a[x] > a[y]; }

int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) scanf("%d", &a[i]), b[i] = i;
    sort(b + 1, b + 1 + n, cmp);
    set<int> pos;
    pos.insert(-1), pos.insert(-2);
    pos.insert(n + 1), pos.insert(n + 2);
    pos.insert(b[1]);
    for(int i = 2 ; i <= n ; ++ i) {
        int l = max(1, (* -- -- pos.lower_bound(b[i])) + 1);
        int r = min(n, (* ++ pos.upper_bound(b[i])) - 1);
        if(l <= r) {
            pos.insert(b[i]); 
            for(int j = l ; j <= r ; ++ j)
                ans = max(ans, a[b[i]] ^ a[j]);
        }
    }
    printf("%d\n", ans);
} 

