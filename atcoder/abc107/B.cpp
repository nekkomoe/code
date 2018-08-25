#include "bits/stdc++.h"
using namespace std;
const int N = 110;
int n, m;
 
char s[N][N];
 
int vis[N][N];
 
int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%s", s[i] + 1);
    }
    for(int i = 1 ; i <= n ; ++ i) {
        bool flag = 1;
        for(int j = 1 ; j <= m ; ++ j) {
            if(s[i][j] == '#') {
                flag = 0;
            }
        }
        if(flag) {
            for(int j = 1 ; j <= m ; ++ j) {
                vis[i][j] = 1;
            }
        }
    }
    for(int j = 1 ; j <= m ; ++ j) {
        bool flag = 1;
        for(int i = 1 ; i <= n ; ++ i) {
            if(s[i][j] == '#') {
                flag = 0;
            }
        }
        if(flag) {
            for(int i = 1 ; i <= n ; ++ i) {
                vis[i][j] = 1;
            }
        }
    }
    // for(int i = 1 ; i <= n ; ++ i) {
    //     for(int j = 1 ; j <= m ; ++ j) {
    //         cout << vis[i][j] << ' ';
    //     }
    //     cout << endl;
    // }
    for(int i = 1 ; i <= n ; ++ i) {
        bool flag = 0;
        for(int j = 1 ; j <= m ; ++ j) {
            if(!vis[i][j]) {
                flag = 1;
                putchar(s[i][j]);
            }
        }
        if(flag) puts("");
    }
}
