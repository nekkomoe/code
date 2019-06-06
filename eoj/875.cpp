#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;

vector<pair<int, int> > qrys[N]; // (pos, id)
int n, q, k, a[N];
ll ans[int(5e5) + 10];

struct BIT {
    ll a[2][N];
    void add(int x, ll v) {
        for(int i = x ; i <= n ; i += i & -i) {
            a[0][i] += v;
            a[1][i] += x * v;
        }
    }

    void add(int l, int r, ll v) {
        add(l, v), add(r + 1, -v);
    }

    ll sum(int x) {
        ll b[2] = { 0, 0 };
        for(int i = x ; i ; i -= i & -i) {
            b[0] += a[0][i];
            b[1] += a[1][i];
        }
        return (x + 1) * b[0] - b[1];
    }

    ll sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }
} bit;

typedef map<int, pair<int, int> > mmp;

void upd(ll &x, ll y) {
    x += y;
}

int main() {


    scanf("%d%d%d", &n, &q, &k);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &a[i]);
    }
    for(int i = 1 ; i <= q ; ++ i) {
        int l, r; scanf ("%d%d", &l, &r);
        qrys[r].emplace_back(l, i);
    }

    mmp cur; // (权值，权值范围)

    for(int i = 1 ; i <= n ; ++ i) {
        mmp nxt;
        nxt.emplace(a[i], make_pair(i, i));
        for(auto t: cur) {
            int val = t.first;
            int l = t.second.first, r = t.second.second;
            val &= a[i];
            if(nxt.count(val)) {
                auto it = nxt[val];
                int ql = min(it.first, l);
                int qr = max(it.second, r);
                nxt[val] = make_pair(ql, qr);
            } else {
                nxt[val] = make_pair(l, r);
            }
        }

        for(auto t: nxt) {
            if(t.first % k == 0) {
                bit.add(t.second.first, t.second.second, 1);
            }
        }

        cur = nxt;

        for(auto t: qrys[i]) {
            upd(ans[t.second], bit.sum(t.first, i));
        }
    }

    for(int i = 1 ; i <= q ; ++ i) {
        printf("%lld\n", ans[i]);
    }
}
