#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 510;
int n, m;

struct P {
    ll x, y;
} red[N], blue[N];

P operator - (P a, P b) {
    return (P) { a.x - b.x, a.y - b.y };
}
ll operator * (P a, P b) {
    return a.x * b.y - b.x * a.y;
}
bool operator < (P a, P b) {
    return a.x == b.x ? a.y < b.y : a.x < b.x;
}

int cnt[N][N];

int calc(int i, int j, int k) {
    return cnt[i][j] + cnt[j][k] - cnt[i][k];
}

int main() {
    cin >> n >> m;
    for(int i = 1 ; i <= n ; ++ i)
        cin >> red[i].x >> red[i].y;
    for(int i = 1 ; i <= m ; ++ i)
        cin >> blue[i].x >> blue[i].y;
    sort(red + 1, red + 1 + n);
    
//    puts("");
//    for(int i = 1 ; i <= n ; ++ i)
//        cout << red[i].x << ' ' << red[i].y << endl;
    
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = i + 1 ; j <= n ; ++ j) {
            for(int k = 1 ; k <= m ; ++ k) {
                if(red[i].x < blue[k].x && blue[k].x <= red[j].x
                && (red[j] - blue[k]) * (red[i] - blue[k]) > 0) {
                    ++ cnt[i][j];
                }
            }
            
//            if(i == 2 && j == 3) {
//                cout << red[i].x << ' ' << red[i].y << ", " << red[j].x << ' ' << red[j].y << endl;
//            }
            
//            cout << "cnt[" << i << "][" << j << "] = " << cnt[i][j] << endl;
        }
    }
    int ans = 0;
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = i + 1 ; j <= n ; ++ j) {
            for(int k = j + 1 ; k <= n ; ++ k) {
                ans += calc(i, j, k) == 0;
            }
        }
    }
    cout << ans << endl;
}

