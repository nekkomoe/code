#include "meetings.h"
#include "bits/stdc++.h"
using namespace std;

const int N = 1e5 + 10;

vector<int> pak[N];
int sta[N], top;

int query(int u, int v, int w) {
    int a[3] = { u, v, w };
    sort(a, a + 3);
    u = a[0], v = a[1], w = a[2];
    if(u == v) return u;
    if(v == w) return v;
    return Query(u - 1, v - 1, w - 1) + 1;
}

void check(int u, int v) {
    if(u > v) swap(u, v);
    Bridge(u, v);
}

void sol(vector<int> pts) {
    random_shuffle(pts.begin(), pts.end());
    for(int x: pts) {
        pak[x].clear();
    }
    int n = pts.size();
    if(n <= 1) return ;
    if(n == 2) {
        check(pts[0] - 1, pts[1] - 1);
        return ;
    }
    int u = pts[0], v = pts[1];
    pak[u].push_back(u), pak[v].push_back(v);
    for(int x: pts) {
        if(x != u && x != v) {
            pak[query(x, u, v)].push_back(x);
        }
    }
    top = 0;
    for(int x: pts) {
        if(pak[x].size()) {
            sta[++ top] = x;
        }
    }
    swap(sta[2], sta[top]);
    sort(sta + 2, sta + top, [&] (int a, int b) { return query(a, b, u) == a; });
    for(int i = 2 ; i <= top ; ++ i) {
        check(sta[i] - 1, sta[i - 1] - 1);
    }
    for(int x: pts) {
        sol(pak[x]);
    }
}

void Solve(int n) {
    srand((unsigned long long) new char);
    vector<int> pts;
    for(int i = 1 ; i <= n ; ++ i) {
        pts.push_back(i);
    }
    sol(pts);
}
