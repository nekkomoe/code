#include "kth.h"
#include <bits/stdc++.h>
using namespace std;

int sta[100], top;

int query_kth(int n_a, int n_b, int n_c, int k) {
    top = 0;
    int sa = 0, sb = 0, sc = 0;
    while(k >= 3) {
        int len = k / 3;
        int a = get_a(sa + len - 1), b = get_b(sb + len - 1), c = get_c(sc + len - 1);
        if(a < b && a < c) {
            sa += len; 
        } else if(b < c) {
            sb += len;
        } else {
            sc += len;
        }
        k -= len;
    }
    for(int i = 0 ; i < k ; ++ i) sta[top ++] = get_a(sa + i);
    for(int i = 0 ; i < k ; ++ i) sta[top ++] = get_b(sb + i);
    for(int i = 0 ; i < k ; ++ i) sta[top ++] = get_c(sc + i);
    nth_element(sta, sta + k - 1, sta + top);
    return sta[k - 1];
}
