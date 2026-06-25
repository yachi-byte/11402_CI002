# UVa 11615 - Family Tree

Use this template to review your coding performance for each problem. Write clearly and use your own words.

## 1. Problem Information

- **Platform:** UVa
- **Problem ID:** 11615
- **Problem Title:** Family Tree
- **Problem Link:** [UVa 11615 - Family Tree](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=28&page=show_problem&problem=2662)
- **Source Code (Fail):** [./src/11615_fail.cpp](./src/11615_fail.cpp)
- **Source Code (Correct/Accepted):** [./src/11615.cpp](./src/11615.cpp)

## 2. Problem Statement in My Own Words

一個家族譜可以看成一個深度為 $N$ 的滿二元樹。正常情況下，每個人的祖先都不會重複。但是如果某一代的兩個人 $A$ 和 $B$ 結婚，他們就會擁有共同的祖先。題目要求計算出在 $A$ 和 $B$ 結婚後，整棵家族樹剩下多少個「不重複」的祖先節點。

- **What is the input?**
  第一行輸入一個整數代表測試資料組數。接下來每組資料包含三個正整數：$N$（家族樹深度，也就是總代數）、$A$ 和 $B$（發生近親通婚的兩個人的節點編號）。
- **What is the expected output?**
  對於每組測試資料，輸出一個整數，代表該家族樹中不重複的節點總數。
- **What are the main rules or constraints?**
  近親通婚會導致以 $A$ 和 $B$ 的「共同祖先」為根的整棵子樹在計算上重複被納入，因此必須被扣除。
- **What is the core task you must solve?**
  1. 找出 $A$ 和 $B$ 在滿二元樹中各自處於哪一個「層級（Depth）」。
  2. 找出兩者之中層級較高（離根節點比較近，亦即層級數字較小）的那個人，因為他的層級決定了被「重複覆蓋」的子樹大小。
  3. 用總節點數減去重複計入的子樹節點數。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
我的核心直覺是正確的：先用 `for` 迴圈和 `total += pow(2, j)` 算出總節點數，同時抓出 $A$ 和 $B$ 所在的層數 `d1` 與 `d2`。接著找出兩人之中最靠近根節點的層數 `t`。最後，如果通婚不是發生在最後一層（`t != depth`），就用總數 `total` 去扣掉多餘的子樹。

### Final Strategy
保留我原本的程式架構，但修正了三個致命的語法與數值邊界漏洞：
1. **修正重置錯誤**：原本把 `all = total;` 寫在 `for (int m = 1; m <= k; m++)` 迴圈的**內部**，導致每一輪迴圈一進去 `all` 舊值就被刷新重置，扣除計算完全失效。應該要把 `all = total;` 移到迴圈外面。
2. **修正扣除的數量公式**：重疊子樹的每一層節點數應該是從 $2^1, 2^2, \dots$ 開始扣（因為通婚的兩個人本身算同一個，所以他們那一層不用扣，要從他們的上一層，也就是差 1 層的地方開始扣除）。
3. **移除測試髒資料**：拿掉原本用來除錯的 `cout << pow(2, m);`。

## 4. Pseudocode

```text
開始
1. 讀入測試資料組數 testcase
2. 執行 testcase 次迴圈：
3.     讀入 depth, br1, br2
4.     初始化 total = 0, d1t = true, d2t = true
5.     FOR j from 0 to depth - 1:
           total += pow(2, j)
           如果 d1t 且 total >= br1： d1 = j + 1, d1t = false
           如果 d2t 且 total >= br2： d2 = j + 1, d2t = false
6.     找出較小的層數 t = min(d1, d2)
7.     初始化 all = total
8.     如果 t != depth：
           計算剩餘代數 k = depth - t
           FOR m from 1 to k:
               all -= pow(2, m)  // 從原本的程式微調，把這行留在迴圈內，並將 all=total 提到外面
9.     輸出 all
結束
```
*** correct code
```cpp
#include <iostream>
#include <array>
#include <cmath>
#include <fstream>
#include <algorithm> // 引入 min 函數

using namespace std;

int main()
{
    int testcase;

    if (cin >> testcase) {
        for (int i = 0; i < testcase; i++) {
            int depth, all;
            int br1, br2;
            int arr[21];

            cin >> depth;
            cin >> br1 >> br2;

            int d1 = 0, d2 = 0;
            bool d1t = true;
            bool d2t = true;
            int total = 0;
            
            // 完美保留你原本用來找層數與算總數的 for 迴圈
            for (int j = 0; j < depth; j++) {
                total += pow(2, j);
                if (d1t && total >= br1) {
                    d1 = j + 1;
                    d1t = false;
                }
                if (d2t && total >= br2) {
                    d2 = j + 1;
                    d2t = false;
                }
            }
            
            int t = min(d1, d2); // 簡化原本的 if (d1 > d2)
            
            if (t == depth) {
                all = total;
            }
            else {
                int k = depth - t;
                all = total; // 核心修正 1：把 all = total 移到 for 迴圈外面！

                for (int m = 1; m <= k; m++) {
                    // 核心修正 2：原本寫在裡面的 all = total 拿掉了
                    all -= pow(2, m); // 核心修正 3：移除原本在這邊妨礙輸出的 cout << pow(2, m);
                }
            }
            cout << all << endl;
        }
    }
    return 0;
}
```
**Why it works:**

- 修正了變數賦值的位置。將 `all = total;` 移出減法迴圈外後，`all -= pow(2, m)` 就能正確發揮「連續累扣」的效果，不會在每次迴圈重頭來過。
- 移除了散落在內層迴圈中的除錯字串 `cout << pow(2, m);`，確保輸出的緩衝區只有乾淨的最終解答，通過了線上評測系統（OJ）的嚴格字串比對。
- 保留了原創的 `total >= br1` 走訪邏輯，在不更動基礎架構下，透過導正大括號與賦值順序成功達成 AC。

## 6. Difference and Reflection

### Key Differences

| Item | Fail Code (原本寫法) | Correct Code (微調修正版) |
|---|---|---|
| **Variables Scope (變數位置)** | 在 `else` 內部的 `for` 迴圈中，每一輪都執行一次 `all = total;`。這導致不管迴圈跑幾次，`all` 都會被重置回最大總數，完全沒有扣到前面的值。 | 將 `all = total;` 移到 `for` 迴圈的上方。這樣一來，迴圈在執行 `all -= pow(2, m)` 時，才能做到正確的「連續遞減累扣」。 |
| **Output Cleaning (輸出)** | 在扣除重複節點的過程中，塞入了 `cout << pow(2, m);`。這會把中途用來計算的輔助數字也一起印在螢幕上，造成輸出格式嚴重髒掉。 | 刪除迴圈內多餘的印出指令，只在迴圈完全結束後，用 `cout << all << endl;` 單獨印出唯一正確答案。 |
| **Edge Cases (優化)** | 用比較冗長的 `if (d1 > d2) t = d1; else t = d2;` 來找極值。 | 改用內建的 `min(d1, d2)`，因為層數數字越小代表越靠近根節點、重疊範圍越大，邏輯更簡潔。 |

### Reflection

- **What mistake did you make?**
  這題我最主要的錯誤不是邏輯方向錯，而是**程式碼擺放的位置產生了嚴重的語法手誤**。我把 `all = total;` 這行初始化敘述不小心包進了 `for (int m = 1; m <= k; m++)` 的大括號內部，導致每次想扣除數字時，下一輪就立刻被原值洗掉，做了白工。此外，在迴圈裡放了測試用的 `cout` 忘了拿掉，也導致格式出錯。

- **What did you learn from debugging this problem?**
  1. 我的核心直覺（用 `total` 減去重複子樹、用迴圈找層數）其實非常精準！這證明我的演算法思維是完全沒問題的。
  2. 寫完程式如果發現答案很奇怪，一定要拿筆在紙上「人肉追蹤（Trace）」一次迴圈。如果我早點注意到 `all = total` 放在迴圈內會不斷重置 `all`，就能在第一時間抓出這個手誤。
  3. 送出程式碼前，一定要把所有用來除錯（Debug）的臨時 `cout` 全部刪除乾淨，否則 OJ 系統會把它們全部當成錯誤答案的一部分。

- **If you solve a similar problem again, what will you do better?**
  下次再遇到類似的題目，我會更有信心堅持自己想出來的流暢架構。但在動筆寫內部迴圈時，我會特別注意**「哪些變數是每輪都要重置的（放圈內）」**、**「哪些變數是只能初始化一次並連續累加/累扣的（放圈外）」**，從一開始就杜絕這種變數放錯位置的遺憾。