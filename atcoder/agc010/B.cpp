// 差分 数学

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

typedef long long ll;

ll a[100010], n, k, sum;

int main() {
    cin >> n;
    for(int i = 1 ; i <= n ; ++ i) {
        cin >> a[i];
        sum += a[i];
        k += i;
    }
    if(sum % k) cout << "NO";
    else {
        k = sum / k;
        ll t = a[1];
        for(int i = 1 ; i < n ; ++ i) {
            a[i] = a[i + 1] - a[i];
        }
        a[n] = t - a[n];
        for(int i = 1 ; i <= n ; ++ i) {
            a[i] -= k;
            if(a[i] % n || a[i] > 0) {
                cout << "NO";
                return 0;
            }
        }
        cout << "YES";
    }
}
