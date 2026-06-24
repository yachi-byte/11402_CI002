#include <iostream>
#include <vector>
using namespace std;

int main()
{
	int n;
	int max_mount = 250;
	
	// 1. 修正二維 vector 的宣告方式：251行，每行是一個大小為 77 且初始值為 0 的 vector<int>
	vector<vector<int>> dp(max_mount + 1, vector<int>(77, 0));
	
	// 2. 保留你用來輔助運算的 sum 陣列
	vector<int> sum(77, 0);
	
	// 設定初始邊界值
	dp[0][0] = 1;
	dp[1][0] = 1;
	
	// 讓 sum 初始為 2 * dp[0]，也就是遞迴式中 2 * f(i-2) 的部分
	// 因為 i=2 時，i-2=0，所以 sum 先存 2 * dp[0] 的數值
	sum[0] = 2; 

	for (int i = 2; i <= 250; i++) {
		// 核心加法：f(i) = f(i-1) + 2 * f(i-2)
		// 這裡對應你原本想寫的：將前一項與 sum(即兩倍的前前項) 相加
		for (int m = 0; m < 77; m++) {
			dp[i][m] += dp[i - 1][m] + sum[m];
			
			// 處理進位：如果超過 9，就往下一格 (m+1) 推進
			if (dp[i][m] > 9) {
				dp[i][m + 1] += dp[i][m] / 10;
				dp[i][m] %= 10;
			}
		}

		// 更新下一輪要用的 sum。當下一輪是 i+1 時，它的前前項就是現在的 i-1
		// 所以要把 sum 更新為 2 * dp[i-1] 的值，幫下一輪做準備
		for (int k = 0; k < 77; k++) {
			sum[k] = dp[i - 1][k] * 2;
			if (sum[k] > 9) { // 順便幫 sum 做內部進位處理
				if (k + 1 < 77) sum[k + 1] += sum[k] / 10;
				sum[k] %= 10;
			}
		}
	}

	// 3. 輸出部分：完全保留你原本用 is 布林值來過濾前導零的邏輯
	while (cin >> n) {
		bool is = true;
		for (int h = 76; h >= 0; h--) {
			if (dp[n][h] != 0) is = false; // 遇到第一個不是 0 的數字，把開關打開
			if (!is) {
				cout << dp[n][h];
			}
		}
		// 如果輸入 0，因為 dp[0][0] = 1，上面迴圈也會正確印出 1
		cout << endl;
	}
	return 0;
}