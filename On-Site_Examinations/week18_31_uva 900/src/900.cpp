#include <iostream>
#include <vector>
using namespace std;

int main()
{
	int n;
	int max_mount = 50;
	vector <long long > dp(max_mount +1, 0);

	dp[0] = 1;
	dp[1] = 1;
	for (int i = 2; i <= 50; i++) {
		dp[i] = dp[i - 1] + dp[i - 2];
	}
	while (cin >> n && n != 0) {
		
		cout << dp[n] << endl;
		
	}
	return 0;
}