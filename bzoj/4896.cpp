#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 2e6 + 10;

int n;
char str[66];
vector<pair<int, int> > ids[N]; // (时刻, 人数)
int ch[N][26], cnt = 1, ans, k;
void nek(char *str, int id) {
    int u = 1;
    for(int i = 1 ; str[i] ; ++ i) {
        int c = str[i] - 'a';
        if(!ch[u][c]) {
            ch[u][c] = ++ cnt;
        }
        u = ch[u][c];
        if(id > 0) {
            if(ids[u].empty()) {
                ids[u].push_back(make_pair(id, 1));
            } else {
                ids[u].push_back(make_pair(id, ids[u].back().second + 1));
            }
        } else if(id < 0) {
            ids[u].push_back(make_pair(id, ids[u].back().second - 1));
        }
    }
    if(id == 0) {
        ans = -1;
        for(int i = 0 ; i < ids[u].size() ; ++ i) {
            pair<int, int> t = ids[u][i];
            if(t.second > k) {
                ans = t.first;
                break;
            }
        }
    }
}

int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        int op; scanf("%d%s", &op, str + 1);
        if(op == 1) {
            nek(str, i);
        } else if(op == 2) {
            nek(str, -i);
        } else {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            k = ((ll) a * abs(ans) + b) % c;
            ans = 0;
            nek(str, 0);
            printf("%d\n", ans);
        }
    }
}
