#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 2e6 + 10;

int n, m, h[N];

struct T {
    int x, y, k;
} t[N];

bool cmpy(T a, T b) {
    return a.y < b.y;
}

pair<int, pair<int, int> > make_pair(int a, int b, int c) {
    return make_pair(a, make_pair(b, c));
}

bool operator < (T a, T b) {
    return make_pair(a.y, a.x, a.k) < make_pair(b.y, b.x, b.k);
}
bool operator == (T a, T b) {
    return make_pair(a.y, a.x, a.k) == make_pair(b.y, b.x, b.k);
}
multiset<T> inu[N];

namespace nmsmal {


    int id_cnt, f[N], g[N], mxh[N];
    vector<T> pts;

    int deal() {
        sort(pts.begin(), pts.end(), cmpy);
        int k0 = 0;
        for(int i = 0 ; i < pts.size() ; ++ i) {
            if(pts[i].k == 0) {
                ++ k0;
            }
        }
        int k1 = 0, mx = k0;
        for(int i = 0 ; i < pts.size() ; ) {
            int j = i;
            if(pts[i].k == 0) {
                -- k0;
            } else {
                ++ k1;
            }
            while(j + 1 < pts.size() && pts[i].y == pts[j + 1].y) {
                if(pts[j + 1].k == 0) {
                    -- k0;
                } else {
                    ++ k1;
                }
                ++ j;
            }

            // cout << "k0 = " << k0 << " k1 = " << k1 << endl;
            mx = max(mx, k0 + k1);

            i = j + 1;
        }
        return mx;
    }

    int sol(int l, int r) {
        int u = ++ id_cnt;

        if(l == r) {
            return u;
        } else {
            int mx = 0, pos = l;
            for(int i = l ; i < r ; ++ i) {
                if(h[i] > mx) {
                    mx = h[i];
                    pos = i;
                }
            }
            mxh[u] = mx;
            int lc = 0, rc = 0;
            // [l, pos]
            if(l <= pos) lc = sol(l, pos);

            // [pos + 1, r]
            if(pos + 1 <= r) rc = sol(pos + 1, r);

            g[u] = g[lc] + g[rc];
            // [mxh[lc], mxh[u]]
            // [mxh[rc], mxh[u]]

            int tmp = 0;
            int tmp_lc = 0, tmp_rc = 0;
            int k0_lc = 0, k0_rc = 0;

            if(lc) {
                pts.clear();
                // for(int i = 1 ; i <= m ; ++ i) {
                //     if(l <= t[i].x && t[i].x <= pos) {
                //         if(mxh[lc] <= t[i].y && t[i].y <= mxh[u]) {
                //             pts.push_back(t[i]);
                //             g[u] += t[i].k == 1;
                //             k0_lc += t[i].k == 0;
                //         }
                //     }
                // }
                for(int i = l ; i <= pos ; ++ i) {
                    while(inu[i].size()) {
                        set<T> :: iterator it = inu[i].lower_bound((T) { -1, mxh[lc], -1 });
                        if(it == inu[i].end()) break;
                        T t = *it;
                        if(mxh[lc] <= t.y && t.y <= mxh[u]) {
                            pts.push_back(t);

                            g[u] += t.k == 1;
                            k0_lc += t.k == 0;

                            inu[i].erase(it);
                        } else {
                            break;
                        }
                    }
                }
                // for(int i = l ; i <= pos ; ++ i) {
                //     for(auto it: inu[i]) {
                //         T t = it;
                //         if(mxh[lc] <= t.y && t.y <= mxh[u]) {
                //             pts.push_back(t);
                //             g[u] += t.k == 1;
                //             k0_lc += t.k == 0;
                //         }
                //     }
                // }
                tmp_lc += deal();
            }

            if(rc) {
                pts.clear();
                // for(int i = 1 ; i <= m ; ++ i) {
                //     if(pos + 1 <= t[i].x && t[i].x <= r) {
                //         if(mxh[rc] <= t[i].y && t[i].y <= mxh[u]) {
                //             pts.push_back(t[i]);
                //             g[u] += t[i].k == 1;
                //             k0_rc += t[i].k == 0;
                //         }
                //     }
                // }

                for(int i = pos + 1 ; i <= r ; ++ i) {
                    while(inu[i].size()) {
                        set<T> :: iterator it = inu[i].lower_bound((T) { -1, mxh[rc], -1 });
                        if(it == inu[i].end()) break;
                        T t = *it;
                        if(mxh[rc] <= t.y && t.y <= mxh[u]) {
                            pts.push_back(t);

                            g[u] += t.k == 1;
                            k0_rc += t.k == 0;

                            inu[i].erase(it);
                        } else {
                            break;
                        }
                    }
                }

                // for(int i = pos + 1 ; i <= r ; ++ i) {
                //     for(auto it: inu[i]) {
                //         T t = it;
                //         if(mxh[rc] <= t.y && t.y <= mxh[u]) {
                //             pts.push_back(t);
                //             g[u] += t.k == 1;
                //             k0_rc += t.k == 0;
                //         }
                //     }
                // }

                tmp_rc += deal();
            }

            tmp = tmp_lc + tmp_rc;

            f[u] = max(tmp_lc + g[lc], f[lc] + k0_lc)
                 + max(tmp_rc + g[rc], f[rc] + k0_rc);

#ifdef TO_DEBUG
            printf("in [%d, %d], f = %d, g = %d, mxh = %d, pos = %d\n", l, r, f[u], g[u], mxh[u], pos);
            printf("tmp_lc = %d, tmp_rc = %d\n", tmp_lc, tmp_rc);
            cout << tmp + g[lc] + g[rc] << ' '
                 << f[lc] + k0_lc + g[rc] + tmp_rc << ' '
                 << g[lc] + tmp_lc + f[rc] + k0_rc << endl;
            cout << f[lc] + k0_lc << ' ' << endl;
            puts("");
#endif

            return u;
        }
    }


    void runprog() {
        int rt = sol(1, n);
        printf("%d\n", f[rt]);
    }
}

void lsh() {
    vector<int> num;
    for(int i = 1 ; i < n ; ++ i) {
        h[i] = 2 * h[i];
        num.push_back(h[i]);
    }
    for(int i = 1 ; i <= m ; ++ i) {
        t[i].y = t[i].y * 2 + 1;
        num.push_back(t[i].y);
    }
    sort(num.begin(), num.end());
    num.erase(unique(num.begin(), num.end()), num.end());
    for(int i = 1 ; i < n ; ++ i) {
        h[i] = lower_bound(num.begin(), num.end(), h[i]) - num.begin() + 1;
    }
    for(int i = 1 ; i <= m ; ++ i) {
        t[i].y = lower_bound(num.begin(), num.end(), t[i].y) - num.begin() + 1;
        inu[t[i].x].insert(t[i]);
    }


#ifdef TO_DEBUG
    for(int i = 1 ; i < n ; ++ i) {
        printf("h[%d] = %d\n", i, h[i]);
    }
    for(int i = 1 ; i <= m ; ++ i) {
        printf("(%d, %d), %d\n", t[i].x, t[i].y, t[i].k);
    }
#endif

}

int allksame() {
    for(int i = 1 ; i <= m ; ++ i) {
        if(t[i].k != t[1].k) {
            return 0;
        }
    }
    return 1;
}

void runprog() {
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i < n ; ++ i) {
        scanf("%d", &h[i]);
    }
    h[n] = 1e7, ++ n;
    for(int i = 1 ; i <= m ; ++ i) {
        scanf("%d%d%d", &t[i].x, &t[i].y, &t[i].k);
    }
    lsh();
    if(allksame()) printf("%d\n", m);
    else nmsmal :: runprog();

    for(int i = 1 ; i <= m ; ++ i) {
        inu[t[i].x].clear();
    }
}

int main() {
    int t; scanf("%d", &t);
    while(t --) {
        runprog();
    }
}
