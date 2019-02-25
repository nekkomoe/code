#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 10000 + 10;
struct E { ll id, a, b, c; } e[N];
struct P { ll x, y; P(ll x = 0, ll y = 0) : x(x), y(y) { } } ans, mnA, mnB;
bool operator < (P a, P b) {
    ll A = a.x * a.y, B = b.x * b.y;
    return A == B ? a.x < b.x : A < B;
}
P operator - (P a, P b) {
    return P(a.x - b.x, a.y - b.y);
}
ll operator * (P a, P b) {
    return a.x * b.y - b.x * a.y;
}

int n;

ll bit[62];

P neko() {
    P res;

    for(int i = 0 ; i <= 60 ; ++ i) bit[i] = 0;
    for(int i = 1 ; i <= n ; ++ i) {
        ll val = e[i].id;
        for(int j = 60 ; ~ j ; -- j) {
            if((val >> j) & 1) {
                if(!bit[j]) {
                    bit[j] = val;
                    break;
                } else {
                    val ^= bit[j];
                }
            }
        }
        if(val) {
            res.x += e[i].a;
            res.y += e[i].b;
            // cout << e[i].id << ' ' << e[i].a << ' ' << e[i].b << ' ' << e[i].c << endl;
        }
    }

    // cout << res.x << ' ' << res.y << endl;
    ans = min(ans, res);
    return res;
}

bool cmpA(E a, E b) { return a.a < b.a; }
bool cmpB(E a, E b) { return a.b < b.b; }
bool cmpC(E a, E b) { return a.c < b.c; }

void sol(P A, P B) {
    for(int i = 1 ; i <= n ; ++ i) e[i].c = e[i].b * (A.x - B.x) + e[i].a * (B.y - A.y);
    sort(e + 1, e + 1 + n, cmpC);
    P C = neko();
    if((B - A) * (C - A) <= 0) return ;
    sol(A, C), sol(C, B);
}

class MagicMatchesGame {
public:
ll minimumArea(vector<int>& id, vector<int>& a, vector<int>& b) {
    // scanf("%d", &n);
    n = id.size();
    for(int i = 1 ; i <= n ; ++ i) {
        // scanf("%lld", &e[i].id);
        e[i].id = id[i - 1];
    }
    for(int i = 1 ; i <= n ; ++ i) {
        // scanf("%lld", &e[i].a);
        e[i].a = a[i - 1];
    }
    for(int i = 1 ; i <= n ; ++ i) {
        // scanf("%lld", &e[i].b);
        e[i].b = b[i - 1];
    }

    // for(int i = 1 ; i <= n ; ++ i) {
    //     cout << e[i].id << ' ' << e[i].a << ' ' << e[i].b << ' ' << e[i].c << endl;
    // } puts("");

    sort(e + 1, e + 1 + n, cmpA), mnA = neko(), ans = mnA;
    // cout << ans.x << ' ' << ans.y << endl;
    sort(e + 1, e + 1 + n, cmpB), mnB = neko();
    sol(mnB, mnA);
    // printf("%lld %lld\n", ans.x, ans.y);
    // printf("%lld\n", ans.x * ans.y);
    return ans.x * ans.y;
}
};

// int main() {
//     cout << (new MagicMatchesGame) -> minimumArea() << endl;
// }

// 2
// 1 1
// 5 6
// 5 4

// {1,2,3}
// {4,5,6}
// {9,8,7}

// 15
// 10095 16913 10198 12528 15264 19224 16442 14595 12060 11858 17900 19304 10619 15818 11670
// 9419 9448 9722 9030 9591 9451 9871 9124 9012 9047 9024 9984 9163 9852 9203
// 9706 9436 9454 9585 9592 9145 9356 9797 9523 9032 9178 9472 9594 9637 9256
