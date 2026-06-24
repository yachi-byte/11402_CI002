# UVa 900 - Brick Wall Patterns

Use this template to review your coding performance for each problem. Write clearly and use your own words.

## 1. Problem Information

- **Platform:** UVa 
- **Problem ID:** 900
- **Problem Title:** Brick Wall Patterns
- **Problem Link:** [UVa900](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=11&page=show_problem&problem=841)
- **Source Code (on site)(AC):** [.cpp](./src/900.cpp)

## 2. Problem Statement in My Own Words

觀察到是由前兩項相加

- What is the input?
    輸入包含多組testcase。每行有一個正整數 n（$1 \le n \le 50$），代表磚牆的長度。當輸入 n = 0 時結束。
- What is the expected output?
- What are the main rules or constraints?
    排列組合的數字成長速度很快，會超出 32 位元整數的範圍
- What is the core task you must solve?
    算出組合數
## 3. Thinking Logic and Solution Strategy

Explain how you thought about the problem and how you decided on your final approach.

### Initial Thoughts

- What was your first idea?
    規律跟費氏數列一樣

### Final Strategy

- What method did you finally use?
- Why does this method work?
- What edge cases did you consider?
    n = 50 帶來的溢位問題：程式碼中使用了 long long 陣列來安全地儲存大數。

## 4. Pseudocode

Write the main steps of your solution before showing the actual code.

```text
START
1. Initialize an array 'dp' of size 51 with 0
2. Set base cases: dp[0] = 1, dp[1] = 1
3. FOR i from 2 to 50:
       dp[i] = dp[i-1] + dp[i-2]
4. WHILE read n AND n is not 0:
       PRINT dp[n]
END
```
### Correct Code

```cpp
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
```

**Why it works:**

- 採用 vector<long long> 建表，避免了費氏數列第 50 項在 32 位元整數下會溢位的問題。
- 在進入 while 讀取輸入之前就已經把 1 到 50 的答案全部算好，面對多組測資時只需要直接查表輸出

## 6. Difference and Reflection

### Reflection

- What mistake did you make?
    開始沒注意到 n=50 的數值大小，使用 int 導致 WA
- What did you learn from debugging this problem?
    先估算最大範圍的輸出值會不會超過 int 的極限
- If you solve a similar problem again, what will you do better?
