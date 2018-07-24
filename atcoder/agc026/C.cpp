#include "bits/stdc++.h"
using namespace std;
typedef unsigned long long ull;
char s[40];
int n;
map<pair<ull, ull>, int> cnt[20][20];
ull ans;
void dfs(int i, int len, ull s1, ull s2, int ty) {
    if(i == n + 1)
        ans += ty * (cnt[len][2 * n - len][make_pair(s1, s2)] += !ty);
    else
        dfs(i + 1, len + 1, s1 * 131 + s[i], s2, ty),
        dfs(i + 1, len, s1, s2 * 131 + s[i], ty);
}
int main() {
    cin >> n >> (s + 1);
    dfs(1, 0, 0, 0, 0);
    reverse(s + 1, s + 1 + 2 * n);
    dfs(1, 0, 0, 0, 1);
    cout << ans << endl;
}
