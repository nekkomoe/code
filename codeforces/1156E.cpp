#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
int n, pos[N], a[N], L[N], R[N];

int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &a[i]);
        pos[a[i]] = i;
        L[i] = R[i] = i;
    }
    stack<int> sta;
    for(int i = 1 ; i <= n ; ++ i) {
        while(sta.size() && a[sta.top()] < a[i]) {
            sta.pop();
        }
        if(sta.size()) {
            L[i] = sta.top() + 1;
        } else {
            L[i] = 1;
        }
        sta.push(i);
    }
    sta = stack<int> ();
    for(int i = n ; i >= 1 ; -- i) {
        while(sta.size() && a[sta.top()] < a[i]) {
            sta.pop();
        }
        if(sta.size()) {
            R[i] = sta.top() - 1;
        } else {
            R[i] = n;
        }
        sta.push(i);
    }

    // for(int i = 1 ; i <= n ; ++ i) {
    //     printf("[%d, %d]\n", L[i], R[i]);
    // }

    ll ans = 0;
    for(int i = 1 ; i <= n ; ++ i) {
        int la = i - L[i];
        int ra = R[i] - i;
        if(la < ra) {
            for(int j = L[i] ; j <= i ; ++ j) {
                int y = a[i] - a[j];
                if(1 <= y && y <= n) {
                    if(i <= pos[y] && pos[y] <= R[i]) {
                        ++ ans;
                    }
                }
            }
        } else {
            for(int j = i ; j <= R[i] ; ++ j) {
                int y = a[i] - a[j];
                if(1 <= y && y <= n) {
                    if(L[i] <= pos[y] && pos[y] <= i) {
                        ++ ans;
                    }
                }
            }
        }
    }
    printf("%lld\n", ans);
}
