# UVa 11063 - B2-Sequence

Use this template to review your coding performance for each problem. Write clearly and use your own words.

## 1. Problem Information

- **Platform:** UVa
- **Problem ID:** 11063
- **Problem Title:** B2-Sequence
- **Problem Link:** [UVa 11063 - B2-Sequence](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=22&page=show_problem&problem=2004)
- **Source Code (Fail):** [./src/11063_fail.cpp](./src/11063_fail.cpp)
- **Source Code (Correct/Accepted):** [./src/11063.cpp](./src/11063.cpp)

## 2. Problem Statement in My Own Words

給定一個包含 $N$ 個正整數的數列，我們要檢查它是不是一個 B2-Sequence。符合 B2-Sequence 必須同時滿足兩個條件：
1. 數列必須是嚴格遞增的，即 $1 \le B_1 < B_2 < B_3 < \dots < B_N$。
2. 數列中任意兩個數字相加的和（包含自己加自己，$B_i + B_j$ 且 $i \le j$）必須全部都是獨一無二的，不能有任何重複的總和出現。

- **What is the input?**
  包含多組測試資料。每組測資第一行是一個整數 $N$（$2 \le N \le 100$）。接下來一行包含 $N$ 個正整數。讀到檔案結束（EOF）為止。
- **What is the expected output?**
  每組測資輸出一行。格式為 `Case #x: It is a B2-Sequence.` 或 `Case #x: It is not a B2-Sequence.`。**特別注意：每組 case 輸出完後，後面都要緊接著印一個空白行（換行）**。
- **What are the main rules or constraints?**
  數字最大可能到 10000，因此兩數之和最大可能達到 20000。我們可以用一個大小為 20001 的布林陣列來記錄每個總和是否出現過。
- **What is the core task you must solve?**
  1. 正確用 `while (cin >> N)` 控制多組測資讀取與 Case 編號。
  2. 檢查輸入是否嚴格遞增且所有數字 $\ge 1$。
  3. 雙重迴圈枚舉所有 $B_i + B_j$ 的兩數之和組合，並用記數表格判斷是否有重複。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
想說可以透過一個陣列把數字存起來，然後一邊讀入一邊檢查當前的數字有沒有大於前一個數字。但原先誤以為是要檢查數字有沒有大於前面的累加總和 `sum`，且外層的 `while (EOF)` 語法結構錯置，加上內層錯誤的 `break` 導致數列根本沒讀完就跳出了。

### Final Strategy
1. 將多組測資控制改為最標準的 `while (cin >> N)`，並在每輪開始前將布林開關 `sequence` 設為 `true`。
2. 先用一個 `for` 迴圈把當前這一組的 $N$ 個數字全部讀進陣列 `arr` 中，同時在讀取時順便檢查兩件事：數字是否小於 1？是否有小於等於前一個數字？若有，直接標記 `sequence = false`。
3. 如果前面的遞增檢查過關，接著使用雙重 `for` 迴圈枚舉所有的兩數之和。外層 `i` 從 0 到 $N-1$，內層 `j` 從 `i` 開始到 $N-1$（代表 $i \le j$）。
4. 計算 `sum_val = arr[i] + arr[j]`，並檢查 `has_sum[sum_val]` 是否已經為 `true`。如果是，代表這個總和重複出現了，標記 `sequence = false` 並跳出。若沒出現過，則將其標記為 `true`。
5. 最終依格式輸出，並注意每組 Case 結束後都要多輸出一行 `cout << endl;` 空行。

## 4. Pseudocode

```text
開始
1. 初始化 testcase = 0
2. 當成功讀入 N 時執行迴圈：
3.     testcase++
4.     建立大小為 N 的陣列 arr，與大小為 20005 且初始為 false 的布林陣列 has_sum
5.     設定 sequence = true
6.     FOR i from 0 to N-1:
           讀入 arr[i]
           如果 arr[i] < 1 或者是 (i > 0 且 arr[i] <= arr[i-1])：
               sequence = false
7.     如果 sequence 仍為 true：
           FOR i from 0 to N-1:
               FOR j from i to N-1:
                   sum_val = arr[i] + arr[j]
                   如果 list[sum_val] 已經是 true：
                       sequence = false
                       跳出內層迴圈
                   否則：
                       list[sum_val] = true
8.     如果 sequence 為 true：
           輸出 "Case #x: It is a B2-Sequence."
       否則：
           輸出 "Case #x: It is not a B2-Sequence."
9.     輸出一個額外的換行 (題意格式要求)
結束
```
*** Correct Code
```cpp
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int N;
    int test = 0;
    
    // 核心修正 1：將讀取放進 while 條件，正確控制多組測資與變數重置
    while (cin >> N) {
        test++;
        vector<int> arr(N);
        bool sequence = true;

        // 先把所有數字安全地讀完，並檢查是否嚴格遞增
        for (int i = 0; i < N; i++) {
            cin >> arr[i];
            if (arr[i] < 1) {
                sequence = false;
            }
            if (i > 0 && arr[i] <= arr[i - 1]) {
                sequence = false;
            }
        }

        // 核心修正 2：利用布林陣列，枚舉任意兩數之和 (i <= j) 是否重複
        if (sequence) {
            vector<bool> has_sum(20005, false);
            for (int i = 0; i < N; i++) {
                for (int j = i; j < N; j++) {
                    int sum_val = arr[i] + arr[j];
                    if (has_sum[sum_val]) {
                        sequence = false;
                        break;
                    }
                    has_sum[sum_val] = true;
                }
                if (!sequence) break;
            }
        }

        // 輸出結果
        if (sequence)
            cout << "Case #" << test << ": It is a B2-Sequence." << endl;
        else
            cout << "Case #" << test << ": It is not a B2-Sequence." << endl;
            
        // 核心修正 3：題目要求每組 Case 結束後都要多列印一個空行
        cout << endl;
    }
    return 0;
}
```
**Why it works:**

- 將資料輸入與規律檢查徹底拆分。先用單層迴圈把測資完整讀進 Vector，避免了原本讀到一半就 `break` 導致後續輸入殘留、汙染到下一組 Case 的嚴重錯誤。
- 準確運用了「查表法（布林陣列）」。因為數字最大為 10000，兩數相加最大不超過 20000，開一個大小為 20005 的 `vector<bool>` 可以在 $O(1)$ 的極致速度下完成「總和不重複」的防守判定。
- 補齊了題目最陰險的格式規範——「每組 Case 後都要多印一行空行」，確保送出後不會拿到 Presentation Error (PE)。

## 6. Difference and Reflection

### Key Differences

| Item | Fail Code (原本寫法) | Correct Code (修正後寫法) |
|---|---|---|
| **Logic (核心邏輯)** | 誤以為 B2-Sequence 是看當前數字有沒有大於前面的總和 `sum`，且在內層條件句塞入無條件的 `break;`，導致數列只讀了兩格就被迫中斷。 | 明確執行「任意兩數之和不重複」的核心定義，利用雙重 `for` 迴圈與 `has_sum` 標記表，精準抓出重複的加總值。 |
| **Edge Cases (邊界)** | `while (EOF)` 是不合法的 C++ 迴圈控制結構，會導致編譯錯誤或死迴圈。 | 改用標準的 `while (cin >> N)`，能優雅且安全地讀取直到檔案結尾。 |
| **Output Format** | `cout` 字串中寫的是小寫的 `case #`（題目要求字首大寫 `Case #`），且漏掉了每組 Case 結束後必須補上的空白行。 | 修正為精確的 `Case #` 字串，並在每組測資結尾補上 `cout << endl;`，完全符合 OJ 系統的字串嚴格比對。 |

### Reflection

- **What mistake did you make?**
  這次主要是在題意的理解上產生了偏差，把「任意兩數之和不能重複」誤記成了「當前數字與前面總和的比較」。另外在語法細節上，外層寫了錯誤的 `while(EOF)`，並且在 `if (i != 0)` 內放錯了 `break` 的位置，導致程式在剛讀到第二個數字時就整組自我中斷。

- **What did you learn from debugging this problem?**
  1. 寫題目的時候，如果需要對一個數列進行「任選兩個數字做某種運算並比較」的操作，**千萬不能在只讀入當前數字的單層迴圈裡直接做完**。標準且安全的起手式一定是「先用迴圈把所有數字全部讀進陣列」，接著再開雙重迴圈去做對位比對。
  2. B2-Sequence 的定義非常經典。當數值範圍不大時（和 $\le 20000$），開一個布林表格來做「查表防重」，是時間複雜度最低、也最不容易寫爛的萬用解法。

- **If you solve a similar problem again, what will you do better?**
  下次再看到這類陣列內部的配對組合題，我會先在筆記本上把它的數學定義式（例如 $B_i + B_j$ 重複性）寫下來，據此決定是否要開雙重迴圈。在處理多組測資時，也會更加謹慎地檢查 Case 之間的換行格式，不讓 Presentation Error 這種小地方扣到分數。