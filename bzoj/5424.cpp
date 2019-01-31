#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 1e5 + 10, M = 650;
// const ll inf = 0x3f3f3f3f3f3f3f3fll;
const int inf = 0x3f3f3f3f;

int n, m, a[N];

int f[N][M + 5], mn[N][M + 5], s[N], ans;

int cost(int x) {
    return x <= m ? 0 : x;
}

deque<int> q[M + 5];

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &a[i]);
        s[i] = s[i - 1] + a[i];
    }
    ans = s[n];
    if(ans <= m) {
        puts("0");
        return 0;
    }
    // memset(f, 0x3f, sizeof f);
    // memset(mn, 0x3f, sizeof mn);
    for(int i = 0 ; i < N ; ++ i) {
        for(int j = 0 ; j < M + 5 ; ++ j) {
            f[i][j] = mn[i][j] = ans;
        }
    }
    f[0][0] = 0;
    int k = 0;
    for(int i = 1 ; i <= n ; ++ i) {
        f[i][1] = a[i] + cost(s[i - 1]);

        while(k + 1 < i && cost(s[i - 1] - s[k + 1])) ++ k;

        for(int j = 2 ; j <= min(i, M) ; ++ j) {


            // [1..k]
            if(k >= 1) f[i][j] = min(f[i][j], mn[k][j - 1] + j * a[i] + s[i - 1]);
            // for(int t = 1 ; t <= k ; ++ t) {
            //     f[i][j] = min(f[i][j], f[t][j - 1] - s[t] + j * a[i] + s[i - 1]);
            // }

            // [k+1..i-1]
            while(q[j - 1].size() && q[j - 1].front() <= k) q[j - 1].pop_front();
            if(q[j - 1].size()) {
                f[i][j] = min(f[i][j], f[q[j - 1].front()][j - 1] + j * a[i]);
            }
            // for(int t = k + 1 ; t < i ; ++ t) {
            //     f[i][j] = min(f[i][j], f[t][j - 1] + j * a[i]);
            // }

            // for(int k = 1 ; k < i ; ++ k) {
            //     f[i][j] = min(f[i][j], f[k][j - 1] + cost(s[i - 1] - s[k]) + j * a[i]);
            // }

        }
        for(int j = 1 ; j <= min(i, M) ; ++ j) {
            ans = min(ans, f[i][j] + cost(s[n] - s[i]));
            mn[i][j] = min(mn[i - 1][j], f[i][j] - s[i]);
            
            while(q[j].size() && f[q[j].back()][j] >= f[i][j]) {
                q[j].pop_back();
            }
            q[j].push_back(i);
        }
    }
    printf("%d\n", ans);
}

/*

1 .. k: s[i-1]-s[t] > m
f[i][j] = min{ f[t][j-1]-s[t] } +j*a[i]+s[i-1]

k+1 .. i-1: s[i-1]-s[t] <= m
f[i][j] = min{ f[t][j-1] } +j*a[i]

*/
