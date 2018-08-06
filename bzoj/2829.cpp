#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

template<typename T> inline void read(T &x) {
	x = 0; char c = getchar();
	while(!isdigit(c)) c = getchar();
	while(isdigit(c)) x = x * 10 + c - '0', c = getchar();
}

const int N = 2e5 + 10;

const double pi = acos(-1);

int n;

double ans, a, b, r;

template<typename T> inline T pw(T x) {
    return x * x;
}

struct P {
    double x, y;
    P() {}
    P(double x, double y) : x(x), y(y) {} 
    P turn(P p, double alpha) {
        // 绕当前点逆时针旋转alpha 
        double a = p.x, b = p.y, aa, bb, L = sqrt(pw(x - a) + pw(y - b));
        double n = pw(L) * cos(alpha), m = pw(L) * sin(alpha);
        double u = a - x, v = b - y;
        bb = (n + v * y + u * x + pw(u) / v * y - u * x + u / v * m) / (v + pw(u) / v);
        aa = (n + v * y + u * x - v * bb) / u;
        return P(aa, bb);
    }
    bool operator < (P p) const {
        return x == p.x ? y < p.y : x < p.x;
    }
    P operator - (P p) {
        return P(x - p.x, y - p.y);
    }
    double dis(P p) {
        return sqrt(pw(x - p.x) + pw(y - p.y));
    }
    void put() {
        printf("(%lf, %lf)\n", x, y);
    }
};

double cross(P t, P p) {
    return t.x * p.y - p.x * t.y;
}
vector<P> pts;

P sta[N];

void sol() {
    sort(pts.begin(), pts.end());
    for(int T = 2 ; T ; -- T) {
        int top = 0;
        for(vector<P> :: iterator it = pts.begin() ; it != pts.end() ; ++ it) {
            P p = *it;
            if(top < 2) sta[++ top] = p;
            else {
                while(top >= 2 && cross(p - sta[top - 1], sta[top] - sta[top - 1]) >= 0) -- top;
                sta[++ top] = p; 
            }
        }
        for(int i = 1 ; i < top ; ++ i) {
            ans += sta[i].dis(sta[i + 1]);
        }
        reverse(pts.begin(), pts.end());
    }
}

int main() {
    scanf("%d", &n);
    scanf("%lf%lf%lf", &a, &b, &r);
    for(int i = 1 ; i <= n ; ++ i) {
        double x, y, alpha;
        scanf("%lf%lf%lf", &x, &y, &alpha);
        P p = P(x, y), lu, ru, ld, rd;
        double t1 = b / 2 - r, t2 = a / 2 - r;
        lu = P(x - t1, y + t2);        
        ru = P(x + t1, y + t2);
        ld = P(x - t1, y - t2);
        rd = P(x + t1, y - t2);
        lu = p.turn(lu, alpha);
        ru = p.turn(ru, alpha);
        ld = p.turn(ld, alpha);
        rd = p.turn(rd, alpha);        
        pts.push_back(lu), pts.push_back(ru), pts.push_back(ld), pts.push_back(rd);
    }
    sol();
    printf("%.2lf\n", ans + 2 * pi * r);
}

