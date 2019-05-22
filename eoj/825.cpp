#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

namespace min_circle_cov {

    inline double sqr(double x) {
        return x * x;
    }

    inline double dis(pair<double, double> a, pair<double, double> b) {
        return sqrt(sqr(a.first - b.first) + sqr(a.second - b.second));
    }

    // (x, y), R
    pair<pair<double, double>, double> runprog(vector<pair<double, double> > pts) {
        random_shuffle(pts.begin(), pts.end());
        double x = 0, y = 0, R = 0;
        for(int i = 0 ; i < pts.size() ; ++ i) {
            if(!(dis(make_pair(x, y), pts[i]) <= R)) {
                x = pts[i].first, y = pts[i].second, R = 0;
                for(int j = 0 ; j < i ; ++ j) {
                    if(!(dis(make_pair(x, y), pts[j]) <= R)) {
                        x = (pts[i].first + pts[j].first) / 2;
                        y = (pts[i].second + pts[j].second) / 2;
                        R = dis(pts[i], pts[j]) / 2;
                        for(int k = 0 ; k < j ; ++ k) {
                            if(!(dis(make_pair(x, y), pts[k]) <= R)) {
                                double a1 = pts[j].first - pts[i].first;
                                double b1 = pts[j].second - pts[i].second;
                                double c1 = (sqr(pts[j].first) + sqr(pts[j].second) - sqr(pts[i].first) - sqr(pts[i].second)) / 2;

                                double a2 = pts[k].first - pts[i].first;
                                double b2 = pts[k].second - pts[i].second;
                                double c2 = (sqr(pts[k].first) + sqr(pts[k].second) - sqr(pts[i].first) - sqr(pts[i].second)) / 2;

                                x = (c1 * b2 - c2 * b1) / (a1 * b2 - a2 * b1);
                                y = (c1 * a2 - c2 * a1) / (b1 * a2 - b2 * a1);
                                R = dis(make_pair(x, y), pts[i]);
                            }
                        }
                    }
                }
            }
        }
        return make_pair(make_pair(x, y), R);
    }
}

struct P {
    ll x, y;
};
bool operator == (P a, P b) {
    return make_pair(a.x, a.y) == make_pair(b.x, b.y);
}
bool operator < (P a, P b) {
    return make_pair(a.x, a.y) < make_pair(b.x, b.y);
}
P operator - (P a, P b) {
    return (P) { a.x - b.x, a.y - b.y };
}
ll operator * (P a, P b) {
    return a.x * b.y - b.x * a.y;
}

vector<P> operator + (vector<P> a, vector<P> b) {
    vector<P> res, up, down;
    for(auto p: b) a.push_back(p);
    sort(a.begin(), a.end()), a.erase(unique(a.begin(), a.end()), a.end());
    for(int i = 0 ; i < a.size() ; ++ i) {
        while(up.size() >= 2) {
            int sz = up.size();
            if((up[sz - 1] - up[sz - 2]) * (a[i] - up[sz - 2]) <= 0) {
                up.pop_back();
            } else {
                break;
            }
        }
        up.push_back(a[i]);
    }
    for(int i = 0 ; i < a.size() ; ++ i) {
        while(down.size() >= 2) {
            int sz = down.size();
            if((down[sz - 1] - down[sz - 2]) * (a[i] - down[sz - 2]) >= 0) {
                down.pop_back();
            } else {
                break;
            }
        }
        down.push_back(a[i]);
    }
    for(auto p: up) res.push_back(p);
    for(auto p: down) res.push_back(p);
    sort(res.begin(), res.end()), res.erase(unique(res.begin(), res.end()), res.end());
    return res;
}

const int N = 1e5 + 10;
int lg[N];
vector<P> tb[N][21];

int main() {
    // srand((unsigned long long) new char);
    int n, m; scanf("%d%d", &n, &m);
    for(int i = 0 ; i < n ; ++ i) {
        ll x, y; scanf("%lld%lld", &x, &y);
        tb[i][0].push_back((P) { x, y });
    }
    for(int i = 2 ; i <= n ; ++ i) {
        lg[i] = lg[i >> 1] + 1;
    }
    for(int j = 1 ; j <= 20 ; ++ j) {
        for(int i = 0 ; i + (1 << j) - 1 < n ; ++ i) {
            tb[i][j] = tb[i][j - 1] + tb[i + (1 << (j - 1))][j - 1];
        }
    }
    while(m --) {
        int l, r; scanf("%d%d", &l, &r);
        int k = lg[r - l + 1];
        vector<P> nek = tb[l][k] + tb[r - (1 << k) + 1][k];
        vector<pair<double, double> > inp;
        for(auto p: nek) {
            inp.push_back(make_pair((double) p.x, (double) p.y));
        }
        pair<pair<double, double>, double> res = min_circle_cov :: runprog(inp);
        printf("%.5f\n", res.second);
    }
}
