# UVa 10252 - Common Permutation

Use this template to review your coding performance for each problem. Write clearly and use your own words.

## 1. Problem Information

- **Platform:** UVa
- **Problem ID:** 10252
- **Problem Title:** Common Permutation
- **Problem Link:** [UVa 10252 - Common Permutation](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=14&page=show_problem&problem=1193)
- **Source Code (Fail):** [10252_fail.cpp](./src/10252_fail.cpp)
- **Source Code (Correct/Accepted):** [10252.cpp](./src/10252.cpp)

## 2. Problem Statement in My Own Words

給定兩個由小寫字母組成的字串 $s1$ 和 $s2$，要找出一個最長的字串 $x$，使得 $x$ 經過排列後可以同時是 $s1$ 和 $s2$ 的子序列（Subsequence）。如果有伸展出多個符合條件的字串，輸出必須依照字母順序（`a` 到 `z`）排列。

- **What is the input?**
  包含多組測試資料。每組測資共有兩行，第一行是字串 $s1$，第二行是字串 $s2$。字串可能為空行。
- **What is the expected output?**
  對於每組測資，輸出符合條件且依字母升序排序的小寫字母字串 $x$。如果兩字串完全沒有共同字母，則輸出一行空白。
- **What are the main rules or constraints?**
  字串長度最多可達 1000 個字元。最關鍵的坑點在於**輸入字串可能是空行**，如果沒有處理好空行讀取，會直接導致後續資料錯位。
- **What is the core task you must solve?**
  1. 正確讀取可能包含空行的整行資料。
  2. 計算兩個字串中各個小寫字母出現的**交集次數**（也就是兩邊出現次數的較小值）。
  3. 依 `a` 到 `z` 的順序印出對應數量的公共字母。

## 3. Thinking Logic and Solution Strategy

Explain how you thought about the problem and how you decided on your final approach.

### Initial Thoughts

- **What was your first idea?**
  想要用兩個陣列來記錄 $s1$ 有出現哪些字母，然後在遇到 $s2$ 有相同字母時進行累加。
- **What difficulty did you notice at the beginning?**
  原先使用 `cin >> s1 >> s2` 讀取，這會自動忽略換行與空格，導致當遇到題目有空字串的測資時，讀取順序會整組壞掉。此外，原本在判斷字母時用了很多層 `for` 迴圈去比對 `c == i + 'a'`，效率很低，且進位與賦值運算子 `&& (a2[i] = 1)` 寫錯，造成頻率無法精準統計。

### Final Strategy

- **What method did you finally use?**
  **字母頻率統計計數法（Counting Alphabet Frequencies）與 `getline` 讀取**。
- **Why does this method work?**
  改用 `getline(cin, s1)` 可以一行一行讀取，即使遇到空行也能正確存入空字串。同時，建立兩個大小為 26 的 `int` 陣列，直接利用 ASCII 碼 `c - 'a'` 當作陣列的 Index 來累加字母出現次數，時間複雜度直接降到線性的 $O(length)$。最後再用 `min(count1[i], count2[i])` 取得兩字串共同擁有的該字母最大數量。
- **What edge cases did you consider?**
  * **字串為空（空行）**：藉由 `getline` 完美保證能正確印出換行，而不會卡死或錯位。
  * **非小寫字母字元**：加上了 `if(c >= 'a' && c <= 'z')` 限制，排除可能混入的非小寫字母雜訊。

## 4. Pseudocode

Write the main steps of your solution before showing the actual code.

```text
Start
1. 當利用 getline 成功成對讀入字串 s1 與 s2 時，重複執行：
2.     建立兩個大小為 26 且初始值皆為 0 的頻率統計陣列 count1 與 count2
3.     針對 s1 中的每個字元 c：
           如果 c 是小寫字母： count1[c - 'a'] 加 1
4.     針對 s2 中的每個字元 c：
           如果 c 是小寫字母： count2[c - 'a'] 加 1
5.     從 i = 0 到 25（代表 a 到 z）：
           計算共同出現次數限制 common = min(count1[i], count2[i])
           執行 common 次迴圈：
               輸出對應的字母 (char)(i + 'a')
6.     輸出換行符號
End
```
### Correct Code
```cpp
// 2.// 10252 
#include <iostream>
#include <algorithm>
#include <vector>
#include <array>
#include <queue>
#include<sstream>
#include <string>

using namespace std;

int main()
{
	string s1, s2;

	// 核心修正：利用 getline 正確處理可能為空的輸入行
	while (getline(cin, s1) && getline(cin, s2)) {
		int count1[26] = { 0 }; // 統計 s1 字母頻率，並在每輪重新清零
		int count2[26] = { 0 }; // 統計 s2 字母頻率

		for (char c : s1) {
			if(c >= 'a' && c <= 'z') count1[c - 'a']++;
		}
		for (char c : s2) {
			if (c >= 'a' && c <= 'z') count2[c - 'a']++;
		}
        
		// 依序檢查 a-z，天生符合題目要求的升序輸出
		for (int i = 0; i < 26; i++) {
			int common = min(count1[i], count2[i]); // 關鍵：取兩者出現次數的最小值
			for (int j = 0; j < common; j++) {
				cout << (char)(i + 'a');
			}
		}
		cout << endl;
	}
	return 0;
}
```
**Why it works:**

- 使用 `getline()` 來控制迴圈條件，遇到空行時字串長度會讀取為 0，接著在統計迴圈中不會做任何累加，最後 `common` 為 0 且正確印出 `endl` 空白行，完美符合題目邊界。
- 拋棄了原本的巢狀多層 `for` 迴圈比對，利用 `c - 'a'` 直接以 $O(1)$ 速度定址，大幅提升效能。透過 `min()` 函式則精準處理了字母「重複出現多次」時的正確交集數量。

## 6. Difference and Reflection

### Key Differences

| Item | Fail Code (第一版) | Correct Code (第二版) |
|---|---|---|
| **Logic (核心邏輯)** | 試圖用 `a2` 當布林標記，並在第二行重複比對，但因為條件句中誤將 `==` 寫成 `=` 賦值（`a2[i] = 1`），導致計數失控，且無法處理單一字母重複出現的狀況。 | 採用兩個獨立的計數陣列。利用 `min(count1[i], count2[i])` 來獲取該字母在兩字串中重複出現的最小交集次數。 |
| **Edge Cases (邊界處理)** | 使用 `cin >> s1 >> s2`。當遇到測資輸入為空字串或空行時，會直接跳過並與下一筆數據配對，導致整組測資順序大崩潰。 | 改用 `while(getline(cin, s1) && getline(cin, s2))`，一行一行嚴格讀取，即便遇到空行也能安全處理。 |
| **Output Handling (輸出)** | 輸出時誤寫為 `cout << i + '0'`（這會印出錯誤的 ASCII 數字），且每個字元都用了 `endl` 換行，不符合題目連續不換行輸出的要求。 | 正確使用強制轉型 `(char)(i + 'a')` 還原字母，並且在印完所有共同字元後，才在最外層輸出一個 `cout << endl;`。 |
| **Other (初始化)** | `array` 與 `a2` 宣告在 `while` 迴圈外部，導致上一組測試資料的殘留數值會不斷疊加到下一組測資，造成嚴重錯誤。 | 統計陣列宣告在 `while` 內部，每輪迴圈進來時都會自動初始化為全 `0`，測資與測資之間互不干涉。 |

### Reflection

- **What mistake did you make?**
  最一開始寫的時候，犯了 C++ 初學者常踩的坑：在 `if` 條件式裡把「比較運算子 `==`」誤寫成「賦值運算子 `=`」（`a2[i] = 1`）。而且沒有注意到陣列要在每輪重新初始化清零，導致數值不斷累加。

- **What did you learn from debugging this problem?**
  1. 字串題目如果提到「小寫字母組成」、「依字母順序輸出」，用一個大小 26 的 `int` 陣列並以 `c - 'a'` 作為索引，絕對是最直覺、最快也最不容易寫錯的王道作法。
  2. UVa 許多題目都藏有「空行/空字串」的測資魔鬼。只要輸入可能包含空格或空行，就要立刻把 `cin >>` 換成 `getline(cin, str)`。
  3. 要找出兩個字串中某個字元同時出現的次數，核心數學邏輯就是取兩邊各自出現次數的最小者（`min`）。

- **If you solve a similar problem again, what will you do better?**
  以後遇到要統計字元頻率的題目，我會第一時間開出 `count[26] = {0}` 的計數陣列，並確保將其宣告在 `while` 讀取迴圈內部以利自動清零。在處理字串輸入時，也會先觀察是否有空行可能，提早決定是否使用 `getline`。