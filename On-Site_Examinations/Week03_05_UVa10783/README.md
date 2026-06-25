# UVa 10783 - Odd Sum

Use this template to review your coding performance for each problem. Write clearly and use your own words.

## 1. Problem Information

- **Platform:** UVa
- **Problem ID:** 10783
- **Problem Title:** Odd Sum
- **Problem Link:** [UVa 10783 - Odd Sum](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=19&page=show_problem&problem=1724)
- **Source Code (Fail):** [./src/10783_fail.cpp](./src/10783_fail.cpp)
- **Source Code (Correct/Accepted):** [./src/10783.cpp](./src/10783.cpp)

## 2. Problem Statement in My Own Words

給定一個整數區間 $[a, b]$，我們要計算並輸出這個閉區間內所有「奇數」的加總和。

- **What is the input?**
  第一行包含一個正整數 $T$，代表測試資料的組數。
  接下來每組測資包含兩行：第一行是一個整數 $a$，第二行是一個整數 $b$（$0 \le a \le b \le 100$）。
- **What is the expected output?**
  對於每組測試資料，輸出一行，格式為 `Case X: Y`，其中 `X` 是從 1 開始計算的測試編號，`Y` 是該區間內所有奇數的總和。
- **What are the main rules or constraints?**
  區間起點 $a$ 必定小於或等於終點 $b$。區間包含了 $a$ 和 $b$ 本身。
- **What is the core task you must solve?**
  1. 正確利用 `for` 迴圈處理 $T$ 組獨立測資，並精準控制計數器 `i + 1` 的輸出。
  2. 順利判斷起點 $a$ 的奇偶性，並穩定向後遞增，直到超出 $b$ 的範圍。
  3. 確保單一組測資的輸出格式唯一，不發生重複列印。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
想說可以用一個 `while (a <= b)` 迴圈讓起點 `a` 逐步往終點 `b` 靠攏。如果 `a` 遇到了奇數就加進 `sum`。但原本在處裡偶數調整時，同時寫了 `a++` 和 `a += 2`，這會破壞 `while` 的單步前進邏輯，導致數字重複累加甚至跳過邊界變成死迴圈。而且把 `a == b` 獨立出來討論反而導致外層重複輸出。

### Final Strategy
最安全也最乾淨的策略是：**不要在迴圈內部同時做兩種步進動作**。
1. 每組測資讀入 `a` 與 `b` 後，先將 `sum = 0`。
2. 只要區間起點 `a` 是偶數（`a % 2 == 0`），我們就主動讓 `a++`。這樣做可以**強制讓起點 `a` 變成這個區間內的「第一個奇數」**。
3. 接下來，我們只需要跑一個非常乾淨的 `while (a <= b)` 迴圈。因為此時 `a` 必定是奇數，所以每次我們可以直接 `sum += a;`，接著雷打不動地執行 `a += 2;`。
4. 當 `a > b` 跳出迴圈時，`sum` 就一定是精確的解答。不管 `a` 原本是否等於 `b`，這個邏輯都能完美通用，不需要使用繁雜的 `if (a == b)` 分支，自然杜絕了重複輸出的問題。

## 4. Pseudocode

```text
開始
1. 讀取測試組數 T
2. FOR i from 0 to T-1:
3.     讀取區間起點 a 與終點 b
4.     初始化 sum = 0
5.     如果 a 是偶數 (a % 2 == 0)：
           a 加 1 (將起點修正為區間內第一個奇數)
6.     當 a <= b 時重複執行以下迴圈：
           sum += a
           a += 2
7.     輸出 "Case " + (i + 1) + ": " + sum
結束
```
***Correct Code
```cpp
#include <iostream>
using namespace std;

int main()
{
    int T;
    if (cin >> T) {
        int a = 0, b = 0;
        
        for (int i = 0; i < T; i++) {
            cin >> a >> b;
            int sum = 0; // 每組測資開始時將 sum 歸零

            // 核心優化：如果起點是偶數，直接推進到第一個奇數
            if (a % 2 == 0) {
                a++;
            }

            // 此時 a 必定為奇數，直接每步加 2 穩定前進
            while (a <= b) {
                sum += a;
                a += 2;
            }
            
            // 統一在最外層印出一次，絕不重複
            cout << "Case " << i + 1 << ": " << sum << endl;
        }
    }
    return 0;
}
```
**Why it works:**

- 引入了「起點預調整（Pre-alignment）」機制。在進入迴圈前透過 `if (a % 2 == 0) a++;` 將起點強制校準為奇數，成功將後續的 `while` 迴圈化繁為簡，免去了在迴圈內反覆判斷奇偶性的效能消耗。
- 移除了冗餘的 `if (a == b)` 獨立分支，將所有邊界狀況（包含 $a=b$ 且皆為奇數、$a=b$ 且皆為偶數）一體化納入 `while (a <= b)` 的控制範圍內，程式碼架構變得非常健全。
- 確保了 `sum` 的宣告範圍完全隸屬於 `for` 迴圈內部，達成了多組測資間的自我初始化。

## 6. Difference and Reflection

### Key Differences

| Item | Fail Code (原本寫法) | Correct Code (修正後寫法) |
|---|---|---|
| **Loop Control (迴圈控制)** | 在 `else` 分支裡同時執行 `a++` 與 `a += 2`，導致 `a` 在單次迭代中暴增 3，極易跳過終點 `b` 造成死迴圈，或引發重複加總。 | 在進入迴圈前一次性將偶數 `a` 變成奇數。進入迴圈後只執行單一且穩定的 `a += 2`，步進邏輯安全清晰。 |
| **Branch Logic (分支)** | 手動拆分 `if (a == b)` 與 `else if (a < b)`，不僅邏輯重疊，還因為在 `a==b` 內部與最外層重複寫了 `cout` 導致單組 Case 會連印兩次。 | 取消對等號的獨立討論，不論大小關係一律由 `while (a <= b)` 進行通用的區間防守，輸出指令唯一。 |
| **Syntax (語法)** | 誤將賦值語法寫成比較運算子 `sum == 0;`，無法發揮實質的重置作用。 | 改回標準賦值語法 `int sum = 0;`。 |

### Reflection

- **What mistake did you make?**
  這次主要犯了兩個坑：第一是在 `while` 迴圈內部的分支裡同時做了 `a++` 和 `a += 2`，這會把迴圈的步進變數搞得很混亂，容易出現死迴圈或重複累加；第二是試圖去窮舉 `a == b` 的特殊情況，結果在大括號的配置上沒分配好，造成同一行結果被印了兩次。

- **What did you learn from debugging this problem?**
  1. 寫 `while` 迴圈時，**步進變數（例如 `a`）在每次循環中前進的幅度最好是固定且單一的**。如果在同一個分支裡一下加 1 一下又加 2，很容易會跳過迴圈的終止條件。
  2. 很多時候，與其在迴圈裡面寫滿複雜的 `if-else` 去判斷各種狀況，不如在**進入迴圈前先用一個簡單的 `if` 把資料微調好**（例如把偶數直接變奇數）。資料對齊了，後面的迴圈就會變得超級好寫。
  3. 寫完程式碼後要檢查所有的輸出語句（`cout`），確認各個分支之間不會發生「你印一次、外層又幫你印一次」的重複列印慘劇。

- **If you solve a similar problem again, what will you do better?**
  未來如果再遇到這種區間連續數值運算的題目，我會先思考能不能在進入迴圈前做數值的預處理（校準起點或終點）。並且會在動筆前，先手算一組極端測資（例如 $a=b=2$ 或 $a=b=3$），看看自己的迴圈會不會卡死