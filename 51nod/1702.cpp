#include "bits/stdc++.h"
using namespace std;
const int N = 1e5 + 10;
const int NODE = 1113436 + 10;
const int EDGE = 2518462 + 10;

// const int NODE = 4e6;
// const int EDGE = 4e6;


int n, a[N], b[N], c[N], d[N];

int head[NODE], rest[EDGE], to[EDGE], nek;
bool w[EDGE];

void lk(int u, int v, int w) {
    to[++ nek] = v, :: w[nek] = w, rest[nek] = head[u], head[u] = nek;
}

int dis[NODE];
deque<int> q;

void bfs() {
    while(q.size()) {
        int u = q.front(); q.pop_front();
        for(int i = head[u] ; i ; i = rest[i]) {
            int v = to[i], w = :: w[i];
            if(dis[v] == -1) {
                dis[v] = dis[u] + w;
                if(w) {
                    q.push_back(v);
                } else {
                    q.push_front(v);
                }
            }
        }
    }
}

int lim, sz;
struct TMP {
    int first, second;
};
bool operator < (TMP a, TMP b) {
    return a.first == b.first ? a.second < b.second : a.first < b.first;
}
vector<TMP> pts[NODE];

void add(int x, int y, int i) {
    for( ; x <= sz ; x += x & -x) {
        pts[x].push_back((TMP) { y, i });
    }
}
void ask(int x, int y, int tar) {
    for( ; x ; x -= x & -x) {
        int j = -1;
        int l = 0, r = pts[x].size() - 1;
        while(l <= r) {
            int mid = (l + r) >> 1;
            if(pts[x][mid].first <= y) {
                j = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }

        if(j != -1) {
            lk(tar, pts[x][j].second, 0);
        }
    }
}

int main() {
    scanf("%d", &n);
    int s = n + 1;
    vector<int> num;
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d%d%d%d", &a[i], &b[i], &c[i], &d[i]);
        if(a[i] <= 0 && b[i] <= 0) {
            lk(s, i, 1);
        }
        num.push_back(a[i]);
        num.push_back(c[i]);
    }
    sort(num.begin(), num.end());
    num.erase(unique(num.begin(), num.end()), num.end());

    for(int i = 1 ; i <= n ; ++ i) {
        a[i] = lower_bound(num.begin(), num.end(), a[i]) - num.begin() + 1;
        c[i] = lower_bound(num.begin(), num.end(), c[i]) - num.begin() + 1;
    }

    lim = n + 1;
    sz = num.size();
    
    for(int i = 1 ; i <= n ; ++ i) {
        add(a[i], b[i], i);
    }
    for(int i = 1 ; i <= sz ; ++ i) {
        sort(pts[i].begin(), pts[i].end());
        int lst = 0;
        for(auto &it: pts[i]) {
            ++ lim;
            if(lst) {
                lk(lim, lst, 0);
            }
            lk(lim, it.second, 1);
            it.second = lim;
            lst = lim;
        }
    }

    for(int i = 1 ; i <= n ; ++ i) {
        ask(c[i], d[i], i);
    }

    // printf("lim = %d, nek = %d\n", lim, nek);
    
    memset(dis, -1, sizeof dis);
    q.push_back(s), dis[s] = 0;
    bfs();
    int ans = dis[n];
    printf("%d\n", ans == -1 ? -1 : ans);
}
