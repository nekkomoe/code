#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <map>
#include <vector>
#include <set>
#include <queue>
#include <cctype>
#include <bitset>
#include <cmath>
#include <numeric>

using namespace std;

typedef long long ll;

const int N = 50010;

typedef long long ll;

int n, m;

ll a[N], f[N], g[N];

char op[10];

template<typename T> inline void read(T &x) {
    x = 0;
    char c = getchar(), f = 0;
    while(!isdigit(c)) {
        if(c == '-') f = 1;
        c = getchar();
    }
    while(isdigit(c)) x = x * 10 + c - '0', c = getchar();
    if(f) x = -x;
}


int main() {
    read(n), read(m);
    for(int i = 1 ; i <= n ; ++ i) read(a[i]);
    while(m --) {
        scanf("%s", op);
        if(op[0] == 'A') {
            int l, r, x;
            read(l), read(r), read(x);
            for(int i = l ; i <= r ; ++ i) a[i] += x;
        } else {
            int l, r;
            read(l), read(r);
            ll ans = 0, tmp = 0;
            for(int i = l ; i <= r ; ++ i) {
                tmp += a[i];
                if(tmp < 0) tmp = 0;
                ans = max(ans, tmp);
            }
            printf("%lld\n", ans);
        }
    }
}

