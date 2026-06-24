# UVa 12405 - Scarecrow

Use this template to review your coding performance for each problem. Write clearly and use your own words.

## 1. Problem Information

- **Platform:** UVa 
- **Problem ID:** 12405
- **Problem Title:** Scarecrow
- **Problem Link:** https://onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=3836
- **Source Code (Fail):** [src/your-file-name.cpp](./src/your-file-name.cpp)
- **Source Code (Correct/Accepted):** [src/your-file-name.cpp](./src/your-file-name.cpp)

## 2. Problem Statement in My Own Words
```text
稻草人可以守護3個土地，'.'代表需要守護的，'#'代表不需要的，找到最小需要多少稻草人。
```


## 3. Thinking Logic and Solution Strategy

```text
> 看到'.'就增加一個count，不判斷後面的2個。看到'#'就跳過
```

### Final Strategy

- What method did you finally use?
    - 我使用了狀態模擬法。透過設定一個 count 計數器來記錄這隻稻草人目前管了幾格（只要在管轄範圍內，不論遇到 '.' 還是 '#' 都算一格），並用布林變數 is 來記錄當前土地是不是在稻草人的保護範圍內。當 count 數滿 3 格之後，就把稻草人的保護範圍重設，等待下一次遇到新的 '.'。
- Why does this method work?
    - 個方法可以一步步檢查每一格。當遇到第一個沒有被保護的 '.' 時，強制啟動一個為期 3 格的「保護罩」，並讓 answer += 1。在保護罩持續的 3 格內，不管遇到什麼地形都直接納入計數，直到 3 格結束後關閉保護罩，繼續尋找下一個需要保護的點。
- What edge cases did you consider?
    - 考慮到了當 '#' 出現在保護罩內部時，它也必須佔用稻草人的 3 格保護額度之一（例如：'.#.' 只需要一隻稻草人），因此在條件式中加入了 else if (straw[i] == '#' && count != 0) 讓計數器能夠正確累加。

## 4. Pseudocode

Write the main steps of your solution before showing the actual code.

```text
START
1. 讀取測試資料總組數 N。
2. 使用 while (n--) 迴圈進入每組測資，並讀取農地長度 M。
3. 宣告變數 count = 0, is = false, answer = 0。
4. 使用 for 迴圈逐一檢查農地的每一格：
   - 如果遇到 '.' 且不在保護內：answer 加 1，開啟保護 (is = true)，count 累加。
   - 如果遇到 '.' 且在保護內：count 累加。
   - 如果遇到 '#' 且保護已開啟：count 累加。
   - 當 count 滿 3 格時：將 count 歸零，關閉保護 (is = false)。
5. 輸出 "Case X: 稻草人數量"。
END
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
	cin >> n;
	while (n--) {
		
		cin >> m;
		vector<char> straw(m, '\0');
		
		for (int i = 0; i < m; i++) {
			cin >> straw[i];
		}

		int count = 0;
		bool is = false;
		int answer = 0;
		for (int i = 0; i < m; i++) {

			if (straw[i] == '.' && is == false) {
				answer += 1;
				is = true;
				count++;
			}
			else if (straw[i] == '.' && is == true)
				count++;
			else if (straw[i] == '#' && count != 0)
				count++;

			if (count == 3) {
				count = 0;
				is = false;
			}
		}
		
		cout << "Case " << test + 1 << ": " << answer << endl;
		test++;
	}
	return 0;
}
```

**Why it works:**

- 程式碼模擬了「當下是否處於保護狀態」的邏輯。只要遇到需要守護的點，就開啟 3 格的週期計數，滿 3 格就重設。
- 成功利用了額外的 test 變數在 while (n--) 正在遞減時，依然能從小到大正確累加並印出正確的 Case 題號。


## 6. Difference and Reflection


### Reflection

- What mistake did you make?
    - 一開始想法寫得比較複雜，為了在 for 迴圈中每一格都按順序檢查，我開了過多的狀態變數（如 count 與 is）在 if-else 裡面互相交織，導致邏輯容易混亂。此外，最外層使用了 while (n--)，因為 n 的值在進入迴圈時會一邊被偷偷扣減，造成我在處理輸出 Case X 的時候，花了非常多心思在避免重複與數字錯亂的問題。
- What did you learn from debugging this problem?
    - 學到了在 for (int i = 0; i < m; i++) 可以不要寫最右邊的 i++ ，這樣在發現 '.' 的當下讓指標移動i += 3 跳過接下來的 3 格。這樣原本程式碼中負責數滿 3 格的 count、負責記錄保護狀態的 is、以及處理 '#' 的複雜 if-else，全部都可以精簡掉。
- If you solve a similar problem again, what will you do better?
    - 下次採用指標跳格法 (如 i += 3) 的聰明版本。
