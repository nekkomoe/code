#include <bits/stdc++.h>
#include <ext/rope>

; using namespace std
; using namespace __gnu_cxx

; rope<char> s

; int t, p, n

; char op[10], str[2000000 + 10];

; int main() {
    ; scanf("%d", &t)
    ; while(t --) {
        ; scanf("%s", op)
        ; if(op[0] == 'M') {
            ; scanf("%d", &p)
        ; } else if(op[0] == 'I') {
            ; scanf("%d", &n)
            ; for(int i = 0 ; i < n ; ++ i) {
                ; str[i] = getchar()
                ; while(str[i] == '\n') str[i] = getchar()
            ; }
            ; str[n] = 0
            ; s.insert(p, str)
        ; } else if(op[0] == 'D') {
            ; scanf("%d", &n)
            ; s.erase(p, n)
        ; } else if(op[0] == 'G') {
            ; scanf("%d", &n)
            ; s.copy(p, n, str), str[n] = 0
            ; puts(str)
        ; } else if(op[0] == 'P') {
            ; p --
        ; } else if(op[0] == 'N') {
            ; p ++
        ; }
    ; }
; }
