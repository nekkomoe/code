#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 1e5 + 10;

int n, a[N], s[N][3], t[N];

void check1() {
    for(int i = 1 ; i < n ; ++ i) {
        if(s[i][0] == s[n][0] - s[i][0]
        && s[i][1] == s[n][1] - s[i][1]
        && s[i][2] == s[n][2] - s[i][2]) {
            puts("1");
            exit(0);
        }
    }
}

void check2() {
    map<pair<int, pair<int, int> >, int> mp;
    for(int i = 1 ; i <= n ; ++ i) {
        t[a[i]] ++;
        if(mp.count(make_pair(t[0] - s[n][0] / 2, make_pair(t[1] - s[n][1] / 2, t[2] - s[n][2] / 2)))) {
            puts("2");
            exit(0);
        }
        mp[make_pair(t[0], make_pair(t[1], t[2]))] = 1;
    }
}

int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &a[i]);
        for(int j = 0 ; j < 3 ; ++ j) {
            s[i][j] = s[i - 1][j];
        }
        s[i][a[i]] ++;
    }
    check1();
    check2();
    puts("3");
}
