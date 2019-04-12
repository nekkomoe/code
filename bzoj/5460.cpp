#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 1e5 + 10;
int n;
ll a[N], s[N], sum, ans, b[N];

void ins(ll x) {
    for(ll i = 62 ; ~ i ; -- i) {
        if(!((sum >> i) & 1)) {
            if((x >> i) & 1) {
                if(!a[i]) {
                    a[i] = x;
                    return ;
                } else {
                    x ^= a[i];
                }
            }
        }
    }
    for(ll i = 62 ; ~ i ; -- i) {
        if((sum >> i) & 1) {
            if((x >> i) & 1) {
                if(!a[i]) {
                    a[i] = x;
                    return ;
                } else {
                    x ^= a[i];
                }
            }
        }
    }
}

int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%lld", &b[i]);
        sum ^= b[i];
    }
    for(int i = 1 ; i <= n ; ++ i) {
        ins(b[i]);
    }
    for(ll i = 62 ; ~ i ; -- i) {
        if(!((sum >> i) & 1)) {
            if((ans ^ a[i]) + (sum ^ ans ^ a[i]) > ans + (sum ^ ans)
            || ((ans ^ a[i]) + (sum ^ ans ^ a[i]) == ans + (sum ^ ans)
            && (ans ^ a[i]) > ans)) {
                ans ^= a[i];
            }
        }
    }
    for(ll i = 62 ; ~ i ; -- i) {
        if((sum >> i) & 1) {
            if((ans ^ a[i]) + (sum ^ ans ^ a[i]) > ans + (sum ^ ans)
            || ((ans ^ a[i]) + (sum ^ ans ^ a[i]) == ans + (sum ^ ans)
            && (ans ^ a[i]) > ans)) {
                ans ^= a[i];
            }
        }
    }
    printf("%lld\n", sum ^ ans);
}
