#include <bits/stdc++.h>

using namespace std;

const int N = 60;

int n;

vector<int> ball[N];

bool check(int x) {
    int p = round(sqrt(x));
    return p * p == x;
}

int main() {
    scanf("%d", &n);
    for(int i = 1 ; i ; ++ i) {
        int flag = 0;
        for(int j = 1 ; j <= n ; ++ j) {
            if(ball[j].empty() || check(ball[j].back() + i)) {
                flag = 1;
                ball[j].push_back(i);
                break;
            }
        }
        if(!flag) {
            printf("%d\n", i - 1);
            break;
        }
    }
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 0 ; j < ball[i].size() ; ++ j) {
            printf("%d ", ball[i][j]);
        }
        puts("");
    }
}
