/**
 * @file main.cpp
 * @brief F God of Gamblers
 * bet k, if win, get 2k, otherwise get 0
 * 下注k元，赢了就得2k元，输了就没了。
 * A有n元，赌场老板m元。A的赌博策略是，一开始下注1元，输了就下注翻倍，直到赢了，然后重新从1元开始下注。如果钱不够前面的策略进行下注，就下注所有钱。
 * 当一方没有钱的时候，赌局结束。
 * @author 知世就是力量
 * @date 2019年7月29日
 * */
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int main() {
    int n, m;
    while (cin>>n>>m) {
        // 根据期望可以算出概率是n/(n+m)
        printf("%.05lf\n", n / double(n + m));
    }
    return 0;
}