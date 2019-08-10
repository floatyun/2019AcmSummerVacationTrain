#include <bits/stdc++.h>
using namespace std;

double pi = atan(1)*4;

int work()
{
	int k;
	cin>>k;
	if (cin.fail()) return 1;
	k &= 1;
	if (k == 1)
		printf("0\n");
	else
		printf("1\n");
	return 0;
}
int main()
{
	while (0 == work()) ;
	return 0;
}