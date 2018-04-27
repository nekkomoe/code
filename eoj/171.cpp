#include <cstdio>
#include <cctype>

using namespace std;

typedef long long ll;

const int N = 2e5 + 10;

template<typename T> inline void read(T &x) {
    char c = getchar();
    while(!isdigit(c)) c = getchar();
    while(isdigit(c)) x = x * 10 + c - '0', c = getchar();
}

int n, a[N * 2], c1[N];

ll c2[N];

inline void modify_(int x, int y) { for(int i = x ; i <= n ; i += i & -i) c1[i] += y, c2[i] += (ll) x * y; }

inline ll pres(int x) {
    ll res = 0;
    for(int i = x ; i ; i -= i & -i) res += (ll) (x + 1) * c1[i] - c2[i];
    return res;
}

inline void modify(int l, int r, int val) { modify_(l, val), modify_(r + 1, -val); }

inline ll query(int l, int r) { return pres(r) - pres(l - 1); }

namespace lala {
    int c[N];
    void add(int i) { for( ; i <= n ; i += i & -i) ++ c[i]; }
    int sum(int i) {
        int res = 0;
        for( ; i ; i -= i & -i) res += c[i];
        return res;
    }
}

void sol() {
    ll ans = 0;
    for(int i = 1 ; i <= n ; ++ i) a[i + n] = a[i];

    for(int i = n ; i ; -- i) {
        modify(a[i], a[i], n - i - lala :: sum(a[i]));
        lala :: add(a[i]);
    }

    ans = query(a[1] + 1, n);

    for(int i = 2 ; i <= n ; ++ i) {
        modify(a[i - 1], a[i - 1], -query(a[i - 1], a[i - 1]));
        modify(1, a[i + n - 1] - 1, 1);
        ans += query(a[i] + 1, n);
    }
    printf("%lld\n", ans);
}

int main() {

    read(n);
    for(int i = 1 ; i <= n ; ++ i) read(a[i]);
    sol();
}
