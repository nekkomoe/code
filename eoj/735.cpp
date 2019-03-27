#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 5e6 + 10;
ll ans;
int n, px[N], py[N];

vector<int> pak[N];
vector<pair<int, int> > ran[N];
int mx[N][22], lg[N];
int getmax(int l, int r) {
    int k = lg[r - l + 1];
    return max(mx[l][k], mx[r - (1 << k) + 1][k]);
}

ll f[N];

// ll getmx(int l, int r) {
//     ll res = 0;
//     for(int i = l ; i <= r ; ++ i) {
//         res = max(res, f[i]);
//     }
//     return res;
// }

// void add(int l, int r, int val) {
//     for(int i = l ; i <= r ; ++ i) {
//         f[i] += val;
//     }
// }

ll tag[N * 10], fafamx[N * 10];
void init(int n) {
    n = min(n * 10, N - 1);
    for(int i = 0 ; i <= n ; ++ i) {
        tag[i] = fafamx[i] = 0;
    }
}
#define lc (id << 1)
#define rc (id << 1 | 1)
void push(int id) {
    if(tag[id]) {
        tag[lc] += tag[id], tag[rc] += tag[id];
        fafamx[id] += tag[id], tag[id] = 0;
    }
}
void upd(int id) {
    push(id), push(lc), push(rc);
    fafamx[id] = max(fafamx[lc], fafamx[rc]);
}

void add(int id, int l, int r, int ql, int qr, ll val) {
    int mid = (l + r) >> 1;
    push(id);
    if(ql <= l && r <= qr) {
        tag[id] += val;
        return ;
    } else if(qr <= mid) {
        add(lc, l, mid, ql, qr, val);
    } else if(ql >= mid + 1) {
        add(rc, mid + 1, r, ql, qr, val);
    } else {
        add(lc, l, mid, ql, mid, val);
        add(rc, mid + 1, r, mid + 1, qr, val);
    }
    upd(id);
}
ll ask() {
    push(1);
    return fafamx[1];
}

bool cmp(pair<int, int> a, pair<int, int> b) {
    return a.second < b.second;
}

ll calc(int pos) {
    vector<int> num;
    for(int x: pak[pos]) num.push_back(x);
    sort(num.begin(), num.end());
    int n = num.size();

    init(n + 10);

    vector<pair<int, int> > tmp;
    for(auto x: ran[pos]) {
        int l = lower_bound(num.begin(), num.end(), x.first) - num.begin() + 1;
        int r = upper_bound(num.begin(), num.end(), x.second) - num.begin();
        tmp.push_back(make_pair(l, r));
    }

    sort(tmp.begin(), tmp.end(), cmp);

    for(int i = 1, j = 0 ; i <= n + 1 ; ++ i) {
        while(j < tmp.size() && tmp[j].second < i) {
            // add(1, tmp[j].first, 1);
            add(1, 1, n + 1, 1, tmp[j].first, 1);
            ++ j;
        }
        // if(i > n) return getmx(1, i);
        // add(i + 1, i + 1, getmx(1, i) + 1);
        if(i > n) return ask();
        add(1, 1, n + 1, i + 1, i + 1, ask() + 1);
    }
    assert(0);
    return -1;
}

int main() {
    // freopen("doll.in", "r", stdin);
    // freopen("doll.out", "w", stdout);
    scanf("%d", &n);
    vector<int> num;
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d%d", &px[i], &py[i]);
        num.push_back(px[i]);
        ans += py[i];
    }
    sort(num.begin(), num.end());
    num.erase(unique(num.begin(), num.end()), num.end());
    for(int i = 1 ; i <= n ; ++ i) {
        px[i] = lower_bound(num.begin(), num.end(), px[i]) - num.begin() + 1;
        mx[px[i]][0] = py[i];
        pak[py[i]].push_back(px[i]);
    }

    for(int i = 2 ; i <= n ; ++ i) {
        lg[i] = lg[i >> 1] + 1;
    }
    for(int j = 1 ; j <= 20 ; ++ j) {
        for(int i = 1 ; i + (1 << j) - 1 <= n ; ++ i) {
            mx[i][j] = max(mx[i][j - 1], mx[i + (1 << (j - 1))][j - 1]);
        }
    }

    for(int i = 1 ; i < n ; ++ i) {
        int l = px[i], r = px[i + 1];
        if(l > r) swap(l, r);
        int mx = getmax(l, r);
        ran[mx].push_back(make_pair(l, r));
        ans -= mx + 1;
    }

    for(int i = 1 ; i <= int(1e6) ; ++ i) {
        if(pak[i].size()) {
            ans += calc(i);
        }
    }

    printf("%lld\n", (int(1e6) - ans) * 2);
}
