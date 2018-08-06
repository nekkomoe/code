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

int n, m, sum;

typedef pair<int, int> node;

#define l first

#define r second

set<node> s;

set<node> :: iterator split(int pos) {
    if(s.empty()) return s.end();
    auto it = s.lower_bound(node(pos, 0));
    if(it != s.end() && it -> l == pos) return it;
    if(it == s.begin()) return it;
    auto lst = -- it; ++ it;
    if(it != s.end() && it -> l > pos && lst -> r < pos) return it;
    -- it;
    if(pos > it -> r) return s.end();
    int l = it -> l, r = it -> r;
    s.erase(it);
    s.insert(node(l, pos - 1));
    return s.insert(node(pos, r)).first;
}

void sol() {
    s.insert(node(1, sum = n));
    for(int i = 1, l, r, k ; i <= m ; ++ i) {
        scanf("%d%d%d", &l, &r, &k);
        split(l);
        auto itr = split(r + 1), itl = split(l);
        while(itl != itr) {
            auto tmp = itl;
            sum -= tmp -> r - tmp -> l + 1;
            ++ itl, s.erase(tmp);
        }
        if(k == 2) s.insert(node(l, r)), sum += r - l + 1;
        printf("%d\n", sum);
    }
}

int main() { scanf("%d%d", &n, &m), sol(); }

