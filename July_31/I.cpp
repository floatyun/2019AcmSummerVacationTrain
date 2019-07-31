#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t;
    cin>>t;
    while (t--) {
        uint64_t a, s = 0;
        bool flag = true;
        for (int i = 0;i < 4; ++i) {
            cin>>a;
            if (flag && a < (1llu<<62))
                flag = false;
            s += a;
        }
        if (flag)
            cout << "18446744073709551616"<<endl;
        else
            cout << s << endl;
    }
    return 0;
}