# UVa 10359 - Tiling

Use this template to review your coding performance for each problem. Write clearly and use your own words.

## 1. Problem Information

- **Platform:** UVa 
- **Problem ID:** 10359
- **Problem Title:** Tiling
- **Problem Link:** [UVa10359](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=15&page=show_problem&problem=1300)
- **Source Code (Fail):** [10359.cpp](./src/10359_fail.cpp)
- **Source Code (Correct/Accepted):** [10359_modify.cpp](./src/10359_modify.cpp)

## 2. Problem Statement in My Own Words

要用兩種磁磚（2*1、2*2）去鋪滿一個 2*n 的矩形，求總共有幾種不同的鋪法。

- What is the input?
    ($0 \le testcase \le 250$）
- What is the expected output? 方法總數
- What are the main rules or constraints?
    會超出long long，要用大數加法
- What is the core task you must solve?
    磁磚的遞迴關係式
    大數

## 3. Thinking Logic and Solution Strategy

Explain how you thought about the problem and how you decided on your final approach.

### Initial Thoughts

- What was your first idea?
    偶數時會是前項和加1，基數時是前項和
- What difficulty did you notice at the beginning?
    - $n=250$ 時的答案長度大約有 70 幾位數。想用 vector 或陣列讓每一格只存一個個位數（0-9）來做大數加法，但在二維動態陣列的宣告與雙層迴圈的進位處理上卡住了。

### Final Strategy
- 如果最後一塊是直放的 $2 \times 1$ 磁磚，前方剩下 $n-1$ 的長度，共有 $f(n-1)$ 種方法。如果最後一塊是橫放的 $2 \times 1$ 磁磚，那它一定得兩塊上下堆疊，會消耗 $2$ 的長度；或者最後一塊直接放一個 $2 \times 2$ 的正方形磁磚，同樣消耗 $2$ 的長度。這兩種情況前方都剩下 $n-2$ 的長度，所以共有 $2 \times f(n-2)$ 種方法。因此得到遞迴式：$f(n) = f(n-1) + 2 \times f(n-2)$。
- What method did you finally use?
保留原有的思考架構。使用標準二維 vector<vector<int>> 建立 DP 表，並把 sum 陣列定位為「滾動更新的前前項之兩倍」
- Why does this method work?
- 每次計算 $f(i)$ 時，直接把 $f(i-1)$ 與已經乘好 2 倍的 sum（即 $2 \times f(i-2)$）做逐位加法。只要在每一位運算後檢查是否大於 9，並把 / 10 的商數加到下一位 [m + 1]，就能完美模擬大數直式加法。
- What edge cases did you consider?
    - 前導零過濾： 輸出時利用一個布林變數 is = true，從最高位第 76 格開始遞減檢查，直到遇到第一個不是 0 的數字才把 is 設為 false 並開始輸出。
    - $n = 0$ 的情況： 初始設定 dp[0][0] = 1，過濾邏輯也能正確印出 1。

## 4. Pseudocode

Write the main steps of your solution before showing the actual code.

```text
START
1. Initialize dp as a 2D vector of size 251 x 77 with 0s
2. Initialize sum vector of size 77 with 0s
3. Set dp[0][0] = 1, dp[1][0] = 1, and sum[0] = 2 (which is 2 * dp[0][0])
4. FOR i from 2 to 250:
       FOR m from 0 to 76:
           dp[i][m] += dp[i-1][m] + sum[m]
           IF dp[i][m] > 9:
               dp[i][m+1] += dp[i][m] / 10
               dp[i][m] %= 10
       // Update sum for the next iteration (sum = 2 * dp[i-1])
       FOR k from 0 to 76:
           sum[k] = dp[i-1][k] * 2
           Handle carrying inside the sum vector if sum[k] > 9
5. WHILE read n:
       Set is = true
       FOR h from 76 down to 0:
           IF dp[n][h] != 0 THEN is = false
           IF is is false THEN PRINT dp[n][h]
       PRINT newline
END
```

## 5. Fail Code vs Correct Code

Show the code that failed first, then show the corrected version.

### Fail Code

```cpp
#include <iostream>
#include <vector>
#include<array>
using namespace std;

int main()
{
	int n;
	int max_mount = 250;
	vector <int,vector<int>> dp(max_mount,(77,0)); // 錯誤的二維宣告
	vector<int> sum(77,0);
	sum[0] = 2;
	dp[0] = 1;
	dp[1] = 1;
	
	for (int i = 2; i <= 250; i++) {

		if (i % 2 == 0) dp[i] += 1; 
		for (int m = 0; m < 77; m++) {
			for (int j = 0; j < 77; j++) {
				dp[i, m] += sum[j]; // 誤用逗號運算子 dp[i, m]
				while (dp[i,m] > 9) {
					dp[i,m + 1] += 1;
					dp[i,m] -= 10;
				}
			}
		}
        // ... 後續sum更新邏輯未完成
```

**Why it failed:**

- 語法與宣告錯誤： vector <int,vector<int>> 不是合法的 C++ 二維動態陣列宣告方式。另外，在 C++ 中存取二維陣列應寫成 dp[i][m]，寫成 dp[i, m] 會觸發逗號運算子（Comma Operator），導致實質上只變成 dp[m]，造成語法與邏輯完全混亂。

- 遞迴邏輯不正確： 誤以為公式跟奇偶數或總和 sum 有關。正確的排列組合規律應該是當前項等於「前一項加兩倍的前兩項」。

- 重複疊加與死迴圈風險： 原本在內層寫了 for(j) 又用 while 扣 10，會造成同一個位數被重複加了好幾次 sum[j]，導致進位完全失控。

### Correct Code

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main()
{
	int n;
	int max_mount = 250;
	
	// 正確的二維 vector 宣告
	vector<vector<int>> dp(max_mount + 1, vector<int>(77, 0));
	vector<int> sum(77, 0);
	
	// 設定初始邊界值
	dp[0][0] = 1;
	dp[1][0] = 1;
	sum[0] = 2; // 2 * dp[0]

	for (int i = 2; i <= 250; i++) {
		// 將前一項 dp[i-1] 與代表「兩倍前前項」的 sum 相加
		for (int m = 0; m < 77; m++) {
			dp[i][m] += dp[i - 1][m] + sum[m];
			
			// 處理個位數大數進位
			if (dp[i][m] > 9) {
				dp[i][m + 1] += dp[i][m] / 10;
				dp[i][m] %= 10;
			}
		}

		// 核心修正：為下一輪 (i+1) 準備全新的 sum (即 2 * dp[i])
		// 在下一輪中，當前輪的 dp[i-1] 就會變成它的前前項
		for (int k = 0; k < 77; k++) {
			sum[k] = dp[i - 1][k] * 2;
			if (sum[k] > 9) {
				if (k + 1 < 77) sum[k + 1] += sum[k] / 10;
				sum[k] %= 10;
			}
		}
	}

	// 輸出部分：保留原本使用布林值過濾前導零的聰明寫法
	while (cin >> n) {
		bool is = true;
		for (int h = 76; h >= 0; h--) {
			if (dp[n][h] != 0) is = false;
			if (!is) {
				cout << dp[n][h];
			}
		}
		cout << endl;
	}
	return 0;
}
```

**Why it works:**

- 修正了 vector<vector<int>> 的語法和 dp[i][m] 的中括號存取，讓資料能正確存入對應的位置。
- 透過在每輪迴圈最後更新 sum[k] = dp[i - 1][k] * 2，完美達成了「用 sum 儲存兩倍前前項」的原始設計目標。
- 修正後的進位機制只用單層 m 迴圈搭配 / 10 與 % 10，乾淨俐落且不會發生重複相加的邏輯錯誤。

## 6. Difference and Reflection

### Key Differences

| Item | Fail Code | Correct Code |
|---|---|---|
| **Logic** | 內層使用雙重迴圈 `m` 和 `j`，導致 `sum` 被重複累加，且缺乏下一輪 `sum` 的更新機制。 | 單層 `m` 迴圈精準對位加法，並在每輪結束時將 `sum` 更新為下一輪所需的 `2 * dp[i-1]`。 |
| **Edge Cases** | 誤用 `dp[i, m]` 語法導致邊界存取崩潰，進位加 1 會改動到錯誤的記憶體位置。 | 正確限制 77 的陣列範圍，進位時使用 `k + 1 < 77` 確保安全的記憶體邊界。 |
| **Output Handling** | 前導零過濾想法正確（`bool is`），但因為前面算出的 DP 表格子全是錯的，導致無法印出正確答案。 | 語法修正後，原創的 `bool is` 過濾法發揮功效，能順利由高位至低位完整輸出大數。 |
| **Other (語法)** | 誤寫為 `vector <int,vector<int>>` 與逗號存取 `dp[i, m]`。 | 改回標準的 `vector<vector<int>>` 與標準二維存取 `dp[i][m]`。 |

### Reflection

- **What mistake did you make?**
  這次主要是在 C++ 二維容器的宣告和多維存取語法上不小心混淆了（把中括號 `[][]` 誤寫成逗號 `[,]`），並且在處理進位時把迴圈層序想得太複雜，導致邏輯打結。

- **What did you learn from debugging this problem?**
  1. 我原本想用 `sum` 來充當「兩倍前前項」並用 `bool is` 過濾前導零的直覺與架構是非常好的！只要確保語法正確、處理好每輪遞迴後的 `sum` 更新，自己的邏輯完全行得通。
  2. 在 C++ 中，`dp[i, m]` 的逗號是有其他特殊含義的（逗號運算子），以後寫二維陣列或 `vector` 一定要牢記使用雙重中括號 `dp[i][m]`。

- **If you solve a similar problem again, what will you do better?**
  下次再遇到類似的大數題目，我會更有信心去實作自己想出來的輔助陣列法。寫程式時我會先在紙上確認好「這一輪算完後，輔助陣列該如何幫下一輪鋪路」，並注意保持進位程式碼的簡潔。。
