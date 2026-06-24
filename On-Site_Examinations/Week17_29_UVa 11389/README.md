# UVa 11389 - The Bus Driver Problem

Use this template to review your coding performance for each problem. Write clearly and use your own words.

## 1. Problem Information

- **Platform:** UVa
- **Problem ID:** 11389
- **Problem Title:** The Bus Driver Problem
- **Problem Link:** [UVa 11389 - The Bus Driver Problem](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=25&page=show_problem&problem=2384)
- **Source Code (on site)(AC):** [./src/11389.cpp](./src/11389.cpp)

## 2. Problem Statement in My Own Words

要幫每位司機分配合適的上午與下午路線，使得要支付的總加班費降到最低。

- **What is the input?**
  包含多組測試資料。每組資料的第一行有三個正整數：$n$（司機人數/路線數）、$d$（每人每天常規工時限制）、$r$（每單位加班工時的加班費費率）。
  接下來兩行分別有 $n$ 個整數，第一行為上午各路線長度，第二行為下午各路線長度。當 $n=0, d=0, r=0$ 時代表輸入結束。
- **What is the expected output?**
  對於每組測試資料，輸出一個整數，代表優化分配後，政府最少需要支付的總加班費金額。
- **What are the main rules or constraints?**
  每條上午路線與下午路線都必須恰好被分配給一位司機。只有當「上午 + 下午」的總長度大於 $d$ 時才需要計算加班費，若小於或等於 $d$ 則不需要（加班費不能為負數）。
- **What is the core task you must solve?**
  利用貪婪演算法找出讓每組「上午長度 + 下午長度」超出 $d$ 的總和為最小的配對組合。

## 3. Thinking Logic and Solution Strategy

Explain how you thought about the problem and how you decided on your final approach.

### Initial Thoughts

- **What was your first idea?**
  如果要讓總加班費最少，必須儘可能避免讓某一個配對組合變得極端巨大。因此，直覺上應該要把「最長的上午路線」跟「最短的下午路線」綁在一起，這樣可以互相抵消，讓整體的分配最平均。
- **What difficulty did you notice at the beginning?**
  一開始需要思考排序後該如何配對。如果上午和下午都由小到大排序，只要一邊正序走、另一邊逆序走，就能輕鬆達到「最大配最小」的貪婪策略。

### Final Strategy

- **What method did you finally use?**
  **貪婪演算法（Greedy Algorithm）搭配排序（Sorting）**。
- **Why does this method work?**
  將上午路線陣列以升序（由小到大）排序，下午路線陣列也以升序排序。接著透過迴圈，將上午第 `g` 個（較小）與下午第 `n-g-1` 個（較大）互相配對。這種「大配小、小配大」的極端對稱組合，在數學上能確保超出限制值的總和被壓縮到最小。
- **What edge cases did you consider?**
  * **沒有超出常規工時：** 當上午與下午相加小於或等於 $d$ 時，加班時數應歸零（`k = 0`），絕對不能扣減總分。
  * **結尾計費：** 計算時可以先加總所有超出的「總時數」，在迴圈結束後再統一乘以費率 `r`，避免每次迴圈都做乘法，提高效率。

## 4. Pseudocode

Write the main steps of your solution before showing the actual code.

```text
Start
1. 當成功讀入 n, d, r 且這三個數不全為 0 時，重複執行以下步驟：
2.     建立大小為 n 的 morning 陣列與 night 陣列，並讀入各自的路線長度
3.     將 morning 陣列進行由小到大排序 (升序)
4.     將 night 陣列進行由小到大排序 (升序)
5.     初始化 總超出工時 total_overpaid = 0
6.     從 g = 0 到 n-1 進行迴圈：
           計算當前組合長度 k = morning[g] + night[n-g-1]
           如果 k > d：
               total_overpaid += (k - d)
7.     將 total_overpaid 乘以費率 r
8.     輸出 total_overpaid
End

### Correct Code

```cpp
#include <iostream>
#include <vector>
#include<algorithm>

using namespace std;

int main()
{
	int n, d, r;
	while (cin >> n >> d >> r && (n != 0 || d != 0 || r != 0)) {
		vector<int> morning (n, 0);
		vector<int> night (n, 0);

		int total_overpaid = 0;

		for (int i = 0; i < n; i++) {
			cin >> morning[i];
		}
		for (int j = 0; j < n; j++) {
			cin >> night[j];
		}
		sort(morning.begin(), morning.end());
		sort(night.begin(), night.end());

		
		for (int g = 0; g < n; g++) {
			
			int k = 0;
			k = (morning[g] + night[n-g-1]);
				
			if (k > d) k = k - d;
			else k = 0;
			total_overpaid += k;
			
		}

		total_overpaid*= r;
		cout << total_overpaid << endl;
	
	}
	return 0;
}
```
**Why it works:**

- 透過 `std::sort` 將兩組路線排序，時間複雜度為 $O(n \log n)$。接著用 $O(n)$ 的時間進行雙指標概念的配對（`morning[g]` 配對 `night[n-g-1]`），整體效率極高，能輕鬆在時限內通過。
- 邏輯中利用 `if (k > d)` 準確過濾了符合常規工時、不需支付加班費的狀況，確保不會出現負數時數。

## 6. Difference and Reflection

### Reflection

- **What mistake did you make?**
  這題的貪婪策略非常直覺，程式碼一次就順利寫對，沒有犯下語法或邏輯上的重大錯誤。

- **What did you learn from debugging this problem?**
  再次驗證了在處理「最佳配對、極值優化」的題目時，排序（Sorting）往往是貪婪演算法最強大的起手式。只要把資料排好序，最佳的配對規律（如最大配最小）就會自然浮現。

- **If you solve a similar problem again, what will you do better?**
  未來遇到類似的資源分配或成本最小化問題，我會優先思考能不能透過「一正一反」的排序對齊策略來達到最優解，並注意大數可能帶來的溢位問題（雖然此題測資範圍 `int` 已足夠）。