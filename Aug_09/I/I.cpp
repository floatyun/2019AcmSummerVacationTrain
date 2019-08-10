#include <bits/stdc++.h>
using namespace std;

double pi = atan(1)*4;

int work()
{
	int n,d;
	cin>>n>>d;
	if (cin.fail()) return 1;
	int angle;
	double theta, sum = 0;
	for (int i = 0; i < n; ++i) {
		cin>>angle;
		theta = angle/180.0*pi;
		sum += sin(theta);
	}
	printf("%.03lf\n", 0.5*sum*d*d);
	return 0;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	while (0 == work()) ;
	return 0;
}