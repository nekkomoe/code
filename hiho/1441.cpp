#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <string>
#include <set>

using namespace std;

const int N = 50 * 2 + 10;

int len[N], pre[N], tot = 1, last = 1, ch[N][30];

string str[N], s;

int bak[N], tmp[N];

int nd(int l) {
    return len[++ tot] = l, tot;
}

set<int> rig[N];

void ins(int c) {
    int p, np, q, nq;
    pre[np = last = nd(len[p = last] + 1)] = 1;
    rig[np].insert(len[np]);
    str[np] = s.substr(0, len[np]);
    while(p && !ch[p][c]) ch[p][c] = np, p = pre[p];
    if(p) {
        pre[np] = q = ch[p][c];
        if(len[p] + 1 != len[q]) {
            nq = nd(len[p] + 1);
            pre[nq] = pre[q], pre[q] = pre[np] = nq;
            memcpy(ch[nq], ch[q], sizeof ch[q]);
            while(p && ch[p][c] == q) ch[p][c] = nq, p = pre[p];
        }
    }
}

int q;

int main() {
    cin >> s;
    for(int i = 0 ; i < s.length() ; ++ i) ins(s[i] - 'a');
    for(int i = 1 ; i <= tot ; ++ i) tmp[len[i]] ++;
    for(int i = 1 ; i <= tot ; ++ i) tmp[i] += tmp[i - 1];
    for(int i = 1 ; i <= tot ; ++ i) bak[tmp[len[i]] --] = i;
    for(int i = tot ; i ; -- i) {
        int p = bak[i];
        str[pre[p]] = str[p];
        rig[pre[p]].insert(rig[p].begin(), rig[p].end());
    }
    cin >> q;
    while(q --) {
        cin >> s;
        int p = 1;
        for(int i = 0 ; i < s.length() ; ++ i) p = ch[p][s[i] - 'a'];
        // cout << p << ' ' << len[pre[p]] + 1 << ' ' << len[p] << ' ' << str[p] << endl;
        cout << str[p].substr(str[p].length() - (len[pre[p]] + 1), str[p].length()) << ' ' << str[p].substr(str[p].length() - len[p], str[p].length()) << ' ';

        for(set<int> :: iterator it = rig[p].begin() ; it != rig[p].end() ; ++ it) {
            cout << *it << ' ';
        }
        cout << endl;
    }
}

