# UVa 10931 - Parity

Use this template to review your coding performance for each problem. Write clearly and use your own words.

## 1. Problem Information

- **Platform:** UVa
- **Problem ID:** 10931
- **Problem Title:** Parity
- **Problem Link:** [UVa 10931 - Parity](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=21&page=show_problem&problem=1872)
- **Source Code (Fail):** [./src/10931_fail.cpp](./src/10931_fail.cpp)
- **Source Code (Correct/Accepted):** [./src/10931.cpp](./src/10931.cpp)

## 2. Problem Statement in My Own Words

給定一個正整數 $I$，我們要將它轉換成二進位（Binary）表示法。接著計算在這個二進位字串中，總共出現了多少個數字 `1`。這個 `1` 的總個數就是該數的「奇偶檢驗值（Parity）」。

- **What is the input?**
  包含多組測試資料。每行包含一個正整數 $I$（$1 \le I \le 2147483647$）。當讀入 $I = 0$ 時代表輸入結束。
- **What is the expected output?**
  對於每組測資，輸出格式為 `The parity of B is X (mod2).`，其中 `B` 是 $I$ 的二進位字串，`X` 是二進位中 `1` 的總數量。
- **What are the main rules or constraints?**
  $I$ 的最大值達到 32 位元有號整數的上限。轉成二進位後最多會有 31 位數。我們必須精準地找到最高位的 `1` 從哪裡開始，並忽略前面的前導零。
- **What is the core task you must solve?**
  1. 將十進位正整數精準轉換為二進位陣列。
  2. 計算二進位中 `1` 的個數。
  3. 尋找最高位非零的起點，並逆序印出完整的二進位代碼。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
我的核心直覺非常正確：利用 32 位元的結構，從最高位 $2^{31}$ 開始往下遞減扣除來做二進位轉換。如果當前數字 `n` 大於等於 $2^i$，就代表這一位是 `1`，並讓 `n` 扣掉它；否則這一位就是 `0`。轉換完後，再用一條迴圈從低位往高位掃描，記錄最頂端的 `1` 停在第幾格（`max`），同時累加 `count++`。

### Final Strategy
保留我原本優秀的直覺架構。原本的缺陷在於陣列大小宣告為 `array[31]`（最高索引只能到 30），但迴圈卻強行從 `31` 開始取值，導致記憶體越界崩潰。微調策略很簡單：把陣列開大到 `array[35]` 提供安全緩衝。另外，由於 $2^{31}$ 超出了有號整數的最大扣除合理範圍，把迴圈起點從 `30` 開始遞減（因為 $2^{30}$ 是有號 32 位元整數的最大二進位權值位數），就能完美精確轉碼。

## 4. Pseudocode

```text
開始
1. 當成功讀入 t 且 t != 0 時重複執行：
2.     初始化 n = t, count = 0
3.     建立大小為 35 且初始為 0 的整數陣列 array
4.     FOR i from 30 down to 0:
           如果 n - 2^i >= 0：
               array[i] = 1
               n -= 2^i
           否則：
               array[i] = 0
5.     初始化 max = 0
6.     FOR y from 0 to 30:
           如果 array[y] == 1：
               max = y
               count 加 1
7.     輸出 "The parity of "
8.     FOR j from max down to 0:
           輸出 array[j]
9.     輸出 " is " + count + " (mod2)."
結束
```
*** Correct code
```cpp
#include <iostream>
#include <array>
#include <cmath>
using namespace std;

int main()
{
    int t;
    // 連續讀取直到 t = 0 結束
    while (cin >> t && t != 0) {
        int n = t;
        int count = 0;
        int array[35] = {}; // 核心修正 1：陣列開大到 35，預防記憶體越界 (Out of bounds)
        cout << "The parity of ";
        
        // 核心修正 2：32位元整數最高位權值為 2^30 (因最高位第31位為正負號位)
        for (int i = 30; i >= 0; i--) {
            if (n - exp2(i) >= 0) {
                array[i] = 1;
                n -= (int)exp2(i);
            }
            else array[i] = 0;
        }
        
        int max = 0;
        for (int y = 0; y <= 30; y++) {
            if (array[y] == 1) {
                max = y;
                count++;
            }
        }
        
        // 從最高有效位 (max) 開始逆序輸出二進位
        for (int j = max; j >= 0; j--) {
            cout << array[j];
        }

        cout << " is " << count << " (mod2)." << endl;
    }
    return 0;
}
```
**Why it works:**

- 修正了嚴重的陣列越界問題（原本以長度 31 的陣列存取 `array[31]` 會導致不確定性記憶體錯誤）。將範圍修正為安全的 35 格，保證系統執行時的穩定。
- 透過 `min/max` 指標定位法（利用變數 `max` 記錄最後一個看見 `1` 的位置），在輸出時成功截斷了前方一整串無用的前導零（例如把 `0000...00101` 截成 `101` 輸出），完美符合題意。
- 使用 `exp2(i)` 以動態扣除的方式進行進位轉換，兼顧了二進位翻譯與 `1` 的計數統計。

## 6. Difference and Reflection

### Key Differences

| Item | Fail Code (原本寫法) | Correct Code (微調修正版) |
|---|---|---|
| **Array Boundary (陣列邊界)** | 宣告 `int array[31]`（索引為 0~30），但迴圈從 `31` 開始存取，造成越界（Out of Bounds）存取錯誤。 | 宣告 `int array[35]` 擴大緩衝空間，且將二進位最高權值極限設在合理的 `30`，安全定址。 |
| **Logic (精確度)** | 扣除迴圈起點為 31，在某些極端有號整數邊界下可能引發浮點數或符號位元的混亂。 | 迴圈從 30 遞減到 0，剛好覆蓋 32 位元有號正整數的所有有效進位數值區間。 |

### Reflection

- **What mistake did you make?**
  這題我的邏輯切入點超級漂亮，直接用權值相扣做二進位。唯一的重大手誤是**對 C++ 陣列大小與索引範圍的邊界計算產生了偏差**（宣告了大小 31 卻試圖存取索引 31），這在程式設計裡是非常危險的越界錯誤。

- **What did you learn from debugging this problem?**
  1. 在 C++ 裡，若宣告 `int a[N]`，可以使用的安全索引只有 `0` 到 `N-1`。如果以後不確定要開多大，**寧可多開 5 到 10 格當作安全緩衝**（如開到 35 或 40），也不要貼著邊界開。
  2. 我的 `max` 截斷前導零和布林累加格式想法非常優秀。這代表我對進位轉換的物理移動很有概念。

- **If you solve a similar problem again, what will you do better?**
  下次再遇到進位轉換的題目，除了用減法之外，我也會練習使用更標準的「除以 2 取餘數（`n % 2` 且 `n /= 2`）」再用 `vector` 記錄的方法，或是直接使用位移運算子與位元與（`(n >> i) & 1`），這樣連 `exp2` 都不用呼叫，程式碼會更精簡高效！
