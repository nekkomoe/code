#include "bits/stdc++.h"
using namespace std;

const int N = 1e5 + 10;

int fa[30];
int get(int x) { return x == fa[x] ? x : fa[x] = get(fa[x]); };

char s[N], t[N];
vector<pair<char, char> > ans;

int main() {
    scanf("%*d%s%s", s, t);
    for(int i = 1 ; i <= 26 ; ++ i) fa[i] = i;
    for(int i = 0 ; s[i] ; ++ i) {
        if(s[i] != t[i]) {
            int u = get(s[i] - 'a' + 1), v = get(t[i] - 'a' + 1);
            if(u != v) {
                ans.push_back(make_pair(s[i], t[i]));
                fa[u] = v;
            }
        }
    }
    printf("%d\n", int(ans.size()));
    for(int i = 0 ; i < ans.size() ; ++ i) {
        printf("%c %c\n", ans[i].first, ans[i].second);
    }
}
