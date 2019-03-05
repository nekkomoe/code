#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
// typedef __int128 ll;

const int N = 1e6 + 10, mod = 1e9 + 7;

pair<int, ll> val[N];

int n, a[N], lim;

pair<int, ll> merge(pair<int, ll> a, pair<int, ll> b) {
    if(a.first == b.first) {
        return make_pair(a.first, (a.second + b.second) % mod);
    } else {
        return max(a, b);
    }
}

void lsh() {
    vector<int> num;
    for(int i = 1 ; i <= n ; ++ i) {
        num.push_back(a[i]);
    }
    sort(num.begin(), num.end());
    num.erase(unique(num.begin(), num.end()), num.end());
    lim = num.size();
    for(int i = 1 ; i <= n ; ++ i) {
        a[i] = lower_bound(num.begin(), num.end(), a[i]) - num.begin() + 1;
    }
    for(int i = n + 1, j = n ; i <= 2 * n ; ++ i, -- j) {
        a[i] = a[j];
    }
}

// <长度，次数>
#define lc (id << 1)
#define rc (id << 1 | 1)
void modify(int id, int l, int r, int pos, pair<int, ll> tar) {
    // cout << l << ' ' << r << endl;
    int mid = (l + r) >> 1;
    if(l == r) {
        val[id] = merge(val[id], tar);
        return ;
    } else if(pos <= mid) {
        modify(lc, l, mid, pos, tar);
    } else {
        modify(rc, mid + 1, r, pos, tar);
    }
    val[id] = merge(val[lc], val[rc]);
}

pair<int, ll> ask(int id, int l, int r, int ql, int qr) {
    // cout << l << ' ' << r << endl;
    if(ql > qr) return make_pair(0, 0);
    int mid = (l + r) >> 1;
    if(ql <= l && r <= qr) {
        return val[id];
    } else if(qr <= mid) {
        return ask(lc, l, mid, ql, qr);
    } else if(ql >= mid + 1) {
        return ask(rc, mid + 1, r, ql, qr);
    } else {
        return merge(ask(lc, l, mid, ql, mid), ask(rc, mid + 1, r, mid + 1, qr));
    }
}

int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &a[n - i + 1]);
    }
    lsh();

    // for(int i = 1 ; i <= 2 * n ; ++ i) {
    //     cout << a[i] << ' ';
    // } cout << endl;

    pair<int, ll> ans = make_pair(0, 0ll);
    for(int i = 1 ; i <= 2 * n ; ++ i) {
        pair<int, ll> res = ask(1, 1, lim, 1, a[i] - 1);
        if(res.first == 0) {
            res.first = 1;
            res.second = 1;
        } else {
            res.first ++;
        }
        modify(1, 1, lim, a[i], res);
    }
    ans = val[1];
    if(ans.first == n) {
        ans.second = 1;
    } else {
        for(int i = 1 ; i <= n - ans.first - 1 ; ++ i) {
            ans.second = ans.second * 2 % mod;
        }
    }
    printf("%d %lld\n", ans.first, ans.second);
}
