# UVa 11292 - Dragon of Loowater

Use this template to review your coding performance for each problem. Write clearly and use your own words.

## 1. Problem Information

- **Platform:** UVa
- **Problem ID:** 11292
- **Problem Title:** Dragon of Loowater
- **Problem Link:** [UVa 11292 - Dragon of Loowater](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2267)
- **Source Code (Fail):** [11292_fail.cpp](./src/11292_fail.cpp)
- **Source Code (Correct/Accepted):** [11292.cpp](./src/11292.cpp)

## 2. Problem Statement in My Own Words

騎士的身高必須大於或等於惡龍的頭部直徑才能砍下該惡龍的頭，而cost 就等於該騎士的身高。我們要用最低的成本把所有的龍頭都砍掉。

- **What is the input?**
  包含多組測試資料。每組開頭有兩個整數 $n$（惡龍的頭數）與 $m$（騎士的人數）。
  接下來 $n$ 行為每頭龍的直徑，再接下來 $m$ 行為每個騎士的身高。當 $n = 0, m = 0$ 時代表輸入結束。
- **What is the expected output?**
  對於每組測試資料，如果能砍掉所有的龍頭，輸出最少需要花費的金幣總數；如果騎士不夠用或能力不足以砍完全部的龍，則輸出 `Loowater is doomed!`。
- **What are the main rules or constraints?**
  一個騎士只能砍一頭龍。當騎士身高小於龍頭直徑時無法砍殺。必須要**所有**的龍都被砍掉才算成功。
- **What is the core task you must solve?**
  利用貪婪演算法（Greedy），讓防禦成本最低化。最理想的狀態就是「用能力值最接近且大於龍頭直徑的騎士」去處理每頭龍。

## 3. Thinking Logic and Solution Strategy

Explain how you thought about the problem and how you decided on your final approach.

### Initial Thoughts

- **What was your first idea?**
  既然希望花費最少，那面對一頭直徑較小的龍，就應該派一個身高剛好能砍牠的矮騎士去，把高大的騎士留給後面直徑更大的龍。所以應該把惡龍和騎士的陣列都進行**由小到大排序（升序）**。
- **What difficulty did you notice at the beginning?**
  最一開始寫的時候，思維卡在傳統的巢狀迴圈，想用標記陣列（`waste`）去記錄騎士有沒有被使用過，卻不小心把大括號和陣列判斷寫錯，導致編譯失敗。

### Final Strategy

- **What method did you finally use?**
  **貪婪演算法（Greedy）搭配雙指標法（Two Pointers）**。
- **Why does this method work?**
  雙方排序後，利用 `d++` 搭配 `k = i` 讓騎士指標一路上前不回頭。這樣在單層迴圈中，可以確保每頭龍都配到當前最便宜且合格的騎士，避免了複雜的雙重迴圈與標記陣列。
- **What edge cases did you consider?**
  * **第一層過濾（人數不夠）**：如果騎士總人數小於惡龍數（`m < n`），絕對不可能砍完全部的龍，直接判定失敗。
  * **第二層過濾（實力不夠）**：人數雖然夠（`m >= n`），但如果騎士實力太弱，迴圈走完後仍有龍沒被砍到（`d < n`），依然必須判定為失敗，只有在 `d == n` 時才能輸出金幣成本。

## 4. Pseudocode

Write the main steps of your solution before showing the actual code.

```text
Start
1. 當成功讀入 n 和 m，且兩者不皆為 0 時，重複執行：
2.     讀入大小為 n 的 dragon 陣列與大小為 m 的 knight 陣列
3.     如果 m < n：
           輸出 "Loowater is doomed!"
4.     如果 m >= n：
           將 dragon 陣列與 knight 陣列由小到大排序
           初始化變數: cost = 0, d = 0, k = 0
           從 i = k 到 m-1 進行迴圈：
               如果 d == n 則跳出迴圈
               如果 knight[i] >= dragon[d]：
                   k = i
                   cost += knight[i]
                   d++
           如果 d == n：
               輸出 cost
           否則：
               輸出 "Loowater is doomed!"
End
```
### Correct Code

```cpp
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int main()
{
	int n, m;
	int test = 0;

	while (cin >> n >> m && (n != 0 || m != 0)) {
		vector<int> dragon(n, 0);
		vector<int> knight(m, 0);

		for (int i = 0; i < n; i++) {
			cin >> dragon[i];
		}
		for (int i = 0; i < m; i++) {
			cin >> knight[i];
		}

		// 1. 第一層過濾：人數如果根本不夠，直接 doom
		if (m >= n) {

			sort(dragon.begin(), dragon.end());
			sort(knight.begin(), knight.end());

			int cost = 0;
			int d = 0;
			int k = 0;
			
			// 精簡的雙指標不回頭貪婪走訪
			for (int i = k; i < m; i++) {
				if (d == n) break;

				if (knight[i] >= dragon[d]) {
					k = i;
					cost += knight[i];
					d++;
				}
			}

			// 2. 第二層過濾：確認龍有沒有被「確實砍完」
			if (d == n) {
				cout << cost << endl;
			} else {
				cout << "Loowater is doomed!" << endl;
			}

		}
		else {
			cout << "Loowater is doomed!" << endl;
		}
	}
	return 0;
}
```
**Why it works:**

- 採用排好序的雙指標法，利用單層 `for` 迴圈搭配隨時更新的 `k = i`，使得時間複雜度穩定保持在 $O(n \log n + m \log m)$，免去了重疊搜尋的效能浪費。
- 在結尾增加了 `if (d == n)` 的防禦性檢查，完美補足了原本「人數夠但實力不足」的漏洞，確保程式在面對極端弱小騎士的測資時不會出錯。

## 6. Difference and Reflection

### Key Differences

| Item | Fail Code (最原本的程式碼) | Correct Code (最後 AC 的程式碼) |
|---|---|---|
| **Logic (核心邏輯)** | 採用巢狀雙重 `for` 迴圈，且內部進位/標記（`waste`）邏輯混亂，導致同一個騎士會重複砍不同隻龍。 | 改用優化的單層 `for` 迴圈搭配 `d`、`i` 雙指標。利用 `k = i` 讓騎士指標不回頭，完美實作「最便宜且能力夠的騎士去砍當前的龍」。 |
| **Edge Cases (邊界處理)** | 缺乏對騎士實力的最終判定。即使騎士人數大於龍（`m >= n`），但如果騎士能力太弱導致沒砍完，依然會印出錯誤的 `cost`。 | 在迴圈結束後加上 `if (d == n)` 的防禦判定。只有當龍的指標 `d` 確實達到 `n`（全滅）才輸出 `cost`，否則一律判定為失敗。 |
| **Output Handling (輸出)** | 題目並沒有要求印出 `Case X:` 格式，且原本在輸出後面漏掉了輸出數值，只印出空白 Case。 | 依題目規範，成功時直接輸出總金幣 `cost`，失敗或人數不足時則輸出 `Loowater is doomed!`。 |
| **Other (語法)** | 程式碼中包含多餘且錯置的大括號 `}`，導致編譯失敗（語法碎裂）。 | 結構完整，成功使用 `if (m >= n)` 進行第一層人數過濾，大括號皆正確對齊。 |

### Reflection

- **What mistake did you make?**
  最一開始寫這題時，思維卡在傳統的巢狀迴圈，想用標記陣列（`waste`）去記錄騎士有沒有被使用過，卻不小心把大括號和陣列判斷寫錯。此外，在實作後來的改良版時，漏掉了「雖然騎士人數夠（`m >= n`）、但如果實力太弱最後沒把龍砍完（`d < n`）」的這種能力不足的邊界狀況。

- **What did you learn from debugging this problem?**
  1. 我後來自己想到的 `d++` 搭配 `k = i` 的不回頭走訪法非常棒！這代表在雙方都排好序的前提下，**單層迴圈配雙指標**就可以完美取代複雜的雙重迴圈，而且時間複雜度更低、更安全。
  2. 就算在開頭加了 `if (m >= n)` 判斷人數，也必須在迴圈結束後檢查 `d == n`。因為「人數夠」不代表「實力夠」，寫題目時一定要分開考慮這兩種不同的失敗情境。

- **If you solve a similar problem again, what will you do better?**
  未來遇到類似的雙陣列配對優化題，我會延續這次自己寫出 `k = i` 記錄位置的優良流暢感，直接使用雙指標（Two Pointers）來寫。並且會在動筆前，先把「條件不滿足而失敗」的所有可能情況（如：人數不夠、能力不夠）在紙上列清楚，一次把防禦性的邊界條件補齊！