#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 10010 * 215 + 10;
char str[30];
int n, m;
int cnt[N], tot = 1;
map<int, int> ch[N];
vector<int> nds;
string val[N];

void ins(int fro) {
    int x = 1;
    for(int j = fro ; str[j] ; ++ j) {
        int c = str[j] - 'a';
        if(!ch[x][c]) ch[x][c] = ++ tot;
        x = ch[x][c];
        nds.push_back(x);
    }
}

int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%s", str + 1);
        nds.clear();
        for(int j = 1 ; str[j] ; ++ j) {
            ins(j);
        }
        sort(nds.begin(), nds.end());
        nds.erase(unique(nds.begin(), nds.end()), nds.end());
        for(int j = 0 ; j < nds.size() ; ++ j) {
            ++ cnt[nds[j]];
            val[nds[j]] = string(str + 1);
        }
    }
    scanf("%d", &m);
    for(int i = 1 ; i <= m ; ++ i) {
        scanf("%s", str + 1);
        int x = 1;
        for(int j = 1 ; str[j] ; ++ j) {
            int c = str[j] - 'a';
            x = ch[x][c];
        }
        if(cnt[x])
	        printf("%d %s\n", cnt[x], val[x].c_str());
	    else puts("0 -");
    }
}
