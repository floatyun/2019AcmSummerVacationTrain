#include <iostream>
#include <string>
#include <vector>
using namespace std;
 
void binToHex(string s,vector<string> &v){
    string Result;
    for(int i = 0;i * 4 < s.length();i ++){
        int num = 0;
        for(int j = 0;j < 4;j ++){
            int pos = i * 4 + j;
            num = num * 2 + s[pos] - '0';
        }
        char t = 0;
        if(num == 10) t = 'a';
        if(num == 11) t = 'b';
        if(num == 12) t = 'c';
        if(num == 13) t = 'd';
        if(num == 14) t = 'e';
        if(num == 15) t = 'f';
        if(num < 10) t = num + '0';
        Result += t;
        if(i % 4 == 3){
            v.push_back(Result);
            Result = "";
        }
    }
}
void quilfy(vector<string> &v){
    for(int i = 0;i < v.size();i ++){
        string s = v[i];
        while(!s.empty() && s.front() == '0')
            s.erase(s.begin());
        if(s == "") v[i] = "0";
        else v[i] = s;
    }
}
void de(vector<string> &v,int &l,int &r){
    bool judge = 0; // judge标志是否触碰到最后一个最后面一个连续零个数大于等于2的连续零串的左边界
    for(int i = v.size() - 1;i >= 0;i --){
				// r==-1代表还没有找到连续的两个零
				// r!=-1表示找到了连续两个零，并且r是最后面一个连续零个数大于等于2的连续零串末尾的位置
        if(r == -1 && i != 0 && v[i] == "0" && v[i - 1] == "0"){
            r = i;
        }
        if(r != -1 && v[i] == "0" && !judge)
            l = i; // 只要还是零，并且认为还没有找完这个零串的左边界，左边界就与i保持一致
        if(r != -1 && v[i] != "0")
            judge = 1; // 已经是1了，说明左边界已经找到了
    }//这个函数找的是最后一段零个数大于2的连续零区间的[l,r]下标
}
int main()
{
    int T,c = 0;
    cin >> T;
    while(T --){
        c ++;
        string t;
        vector<string> v;
        cin >> t;
         
        printf("Case #%d: ",c);
        binToHex(t,v); // 变成十六进制，保留前导零
        quilfy(v); // 去除前导零
        int l = -1,r = -1;
        de(v,l,r); // 去除[l,r]区间的零
        if(l == 0)
            cout << ':';
        for(int i = 0;i < v.size();i ++){
            if(i == l)
                printf(":");
            if(i >= l && i <= r)
                continue;
            if(i == v.size() - 1)
                cout << v[i];
            else cout << v[i] << ":";
        }
        cout << endl;
    }
}