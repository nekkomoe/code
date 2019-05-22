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

int main() {
    srand((unsigned long long) new char);
    int n; scanf("%d", &n);
    vector<pair<double, double> > pts;
    for(int i = 1 ; i <= n ; ++ i) {
        double x, y; scanf("%lf%lf", &x, &y);
        pts.push_back(make_pair(x, y));
    }
    pair<pair<double, double>, double> res = min_circle_cov :: runprog(pts);
    printf("%.10f\n", res.second);
    printf("%.10f %.10f\n", res.first.first, res.first.second);
}
