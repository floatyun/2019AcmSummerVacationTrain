#include <algorithm>
#include <iostream>
#include <bits/stdc++.h>
#include <cmath>
using namespace std;
#define LL long long
int main()
{
    LL a,b;
    while(scanf("%lld%lld",&a,&b) == 2){
        LL k = __gcd(a,b);
        LL td = a * a - 4 * b * k;
        if(td < 0){
            puts("No Solution");
            continue;
        }
        LL d = sqrt(td);
        if(d * d != td){
            puts("No Solution");
            continue;
        }
        int x = (a - d) / 2;
        int y = (a + d) / 2;
        bool flag = ((a + d) & 1);
        if(flag) {
            puts("No Solution");
            continue;
        }
        printf("%d %d\n",x,y);
    }
}