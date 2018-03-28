//tarjan_scc

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <map>
#include <string>

using namespace std;

int n, m, idTot;

map<string, int> id;
map<int, string> reid;

string str1, str2;

int a[30][30];

void insert(string s) {
    if(id.find(s) == id.end()) {
        id[s] = ++ idTot;
        reid[idTot] = s;
    }
}

#include <stack>

#include <vector>

int instack[30], clk, dfn[30], low[30];

stack<int> s;

void dfs(int u) {
    dfn[u] = low[u] = ++ clk;
    s.push(u);
    instack[u] = 1;
    for(int v = 1 ; v <= n ; v ++) {
        if(v != u && a[u][v]) {
            if(!dfn[v]) {
                dfs(v);
                low[u] = min(low[u], low[v]);
            } else if(instack[v]) {
                low[u] = min(low[u], dfn[v]);
            }
        }
    }
    if(low[u] == dfn[u]) {
        int v;
        do {
            v = s.top();
            s.pop();
            instack[v] = 0;
            cout << reid[v];
            if(v != u) {
                cout << ", ";
            }
        } while(v != u);
        cout << endl;
    }
}

int main() {
    static int TOTAL = 0;
    ios :: sync_with_stdio(0);
    cin.tie(0);
    while(1) {
        cin >> n >> m;
        if(!(n || m)) break;
        TOTAL ++;
        if(TOTAL > 1) cout << endl;
        id.clear();
        reid.clear();
        idTot = 0;
        memset(instack, 0, sizeof(instack));
        while(s.size()) s.pop();
        memset(dfn, 0, sizeof(dfn));
        memset(low, 0, sizeof(low));
        clk = 0;
        memset(a, 0, sizeof(a));
         for(int i= 1 ; i <= m ; i ++) {
            cin >> str1 >> str2;
            insert(str1), insert(str2);
            int u = id[str1], v = id[str2];
            a[u][v] = 1;
        }
        cout << "Calling circles for data set " << TOTAL << ":" << endl;
        for(int i = 1 ; i <= n ; i ++) {
            if(!dfn[i]) {
                dfs(i);
            }
        }
    }
}
