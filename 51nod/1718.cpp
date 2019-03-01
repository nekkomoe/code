#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

ll n, lp[] = { 2, 1, -1, -2, -1, 1 };

int main() {
    cin >> n;
    cout << lp[n % 6] << endl;
}
