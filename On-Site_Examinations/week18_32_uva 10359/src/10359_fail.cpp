#include <iostream>
#include <vector>
#include<array>
using namespace std;

int main()
{
	int n;
	int max_mount = 250;
	//vector <int,vector<int>> dp(max_mount,(77,0));
	vector<vector<int>> dp(max_mount + 1, vector<int>(77, 0)); //mpdify
	vector<int> sum(77,0);
	
	sum[0] = 2;
	dp[0] = 1;
	dp[1] = 1;
	//
	for (int i = 2; i <= 250; i++) {

		if (i % 2 == 0) dp[i] += 1;
		for (int m = 0; m < 77; m++) {
			for (int j = 0; j < 77; j++) {
				dp[i, m] += sum[j];
				while (dp[i,m] > 9) {
					dp[i,m + 1] += 1;
					dp[i,m] -= 10;
				}
			}
		}

		for (int k = 0; k < 77; k++) {
			sum[k] = dp[i,k];
		}
		
		
	}
	while (cin >> n ) {
		bool is = true;
		for (int h = 76; h >= 0;h--) {
			if (dp[n, h] != 0) is = false;
			if (!is) {
				
				cout << dp[n,h];
			}
			
		}
		cout << endl;
	}
	return 0;
}
/*
for (int i = 0; i < 77; i++) {
	if (dp[i] > 9) {
		dp[i + 1] += 1;
		dp[i] -= 9;
	}
}
for(int i = 0;)*/