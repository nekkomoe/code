#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>

using namespace std;

typedef long long ll;

const int N = 1e5 + 10;

int n, m;

ll seed, vmax, a[N];

ll rnd() { ll ret = seed; seed = (seed * 7 + 13) % 1000000007; return ret; }

ll pw(ll a, ll b, ll p) { ll res = 1; for(a %= p ; b ; b >>= 1, a = a * a % p) if(b & 1) res = res * a % p; return res; }

struct node {
    int l, r;
    mutable ll v;
    node(int l, int r = -1, ll v = 0) : l(l), r(r), v(v) {}
    bool operator < (const node &t) const { return l < t.l; }
};

set<node> s;

set<node> :: iterator split(int pos) {
    auto it = s.lower_bound(node(pos));
    if(it != s.end() && it -> l == pos) return it;
    -- it;
    if(pos > it -> r) return s.end();
    int l = it -> l, r = it -> r; ll v = it -> v;
    s.erase(it);
    s.insert(node(l, pos - 1, v));
    return s.insert(node(pos, r, v)).first;
}

void op1(int l, int r, int x) {
    split(l);
    for(auto itr = split(r + 1), itl = split(l) ; itl != itr ; ++ itl)
        itl -> v += x;
}

void op2(int l, int r, int x) {
    split(l);
    auto itr = split(r + 1), itl = split(l);
    s.erase(itl, itr);
    s.insert(node(l, r, x));
}


void op3(int l, int r, int x) {
    split(l);
    vector<pair<ll, int> > vec;
    for(auto itr = split(r + 1), itl = split(l) ; itl != itr ; ++ itl)
        vec.push_back({ itl -> v, itl -> r - itl -> l + 1 });
    sort(vec.begin(), vec.end());
    for(auto i : vec) {
        if((x -= i.second) <= 0) {
            cout << i.first << endl;
            return ;
        }
    }
    cout << -1 << endl;
}

void op4(int l, int r, int x, int y) {
    ll res = 0;
    for(auto itr = split(r + 1), itl = split(l) ; itl != itr ; ++ itl) {
        res = (res + (ll) (itl -> r - itl -> l + 1) % y * pw(itl -> v, x, y) % y) % y;
    }
    cout << res << endl;
}

void sol() {
    for(int i = 1 ; i <= n ; ++ i) s.insert(node(i, i, a[i] = (rnd() % vmax) + 1));

    for(int i = 1, op, l, r, x, y ; i <= m ; ++ i) {
        op = (rnd() % 4) + 1, l = (rnd() % n) + 1, r = (rnd() % n) + 1;
        if (l > r) swap(l, r);
        x = op == 3 ? (rnd() % (r - l + 1)) + 1 : (rnd() % vmax) + 1;
        if (op == 4) y = (rnd() % vmax) + 1;

        if(op == 1) op1(l, r, x);
        else if(op == 2) op2(l, r, x);
        else if(op == 3) op3(l, r, x);
        else if(op == 4) op4(l, r, x, y);
    }
}

int main() { cin >> n >> m >> seed >> vmax; sol(); }

