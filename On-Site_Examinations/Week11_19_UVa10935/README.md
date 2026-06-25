# UVa 10935 - Throwing cards away I

Use this template to review your coding performance for each problem. Write clearly and use your own words.

## 1. Problem Information

- **Platform:** UVa
- **Problem ID:** 10935
- **Problem Title:** Throwing cards away I
- **Problem Link:** [UVa 10935 - Throwing cards away I](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=21&page=show_problem&problem=1876)
- **Source Code (on site)(AC):** [./src/10935.cpp](./src/10935.cpp)

## 2. Problem Statement in My Own Words

桌上有編號 1 到 $n$ 的一疊牌，從上到下依序排列。我們重複執行以下操作，直到整疊牌只剩下最後一張：
1. 丟棄最上面（最前面）的第一張牌。
2. 把接著暴露在最上面的那張牌，移到這疊牌的最下面（最後面）。
我們要依序記錄被丟棄的卡牌順序，並找出最後留下的那一張牌。

- **What is the input?**
  包含多組測試資料。每行包含一個整數 $n$（$0 \le n \le 50$），代表卡牌的數量。當 $n = 0$ 時代表輸入結束。
- **What is the expected output?**
  對於每組測資，輸出兩行：
  第一行印出丟棄的卡牌順序，格式為 `Discarded cards: 1, 3, ...`。
  第二行印出最後留下的牌，格式為 `Remaining card: X`。
- **What are the main rules or constraints?**
  操作必須嚴格遵循「丟一張、翻一張到後面」的先進先出（FIFO）順序。當 $n = 1$ 時，因為一開始就只剩一張牌，所以沒有任何牌會被丟棄，此時 `Discarded cards:` 後面不能有任何數字。
- **What is the core task you must solve?**
  1. 利用 C++ Standard Library 的 `queue` 來模擬卡牌在前後移動的物理過程。
  2. 嚴格控管 `Discarded cards:` 後面的逗號與空格輸出格式（特別是第一項與最後一項的邊界）。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
這題的卡牌操作非常有「先進先出」的特性：總是從最前面拿牌出來丟，或者從最前面拿牌塞到最後面。這跟資料結構裡的 **Queue（佇列）** 完全契合。因此可以直接用 `std::queue` 來模擬這個遊戲。

### Final Strategy
1. 使用 `queue<int> t`，利用一個 `for` 迴圈把 1 到 $n$ 的數字通通 `push` 進去。
2. 只要 `t.size() > 1`（代表牌堆裡還剩超過一張牌），就執行迴圈：
   * 用布林值 `first` 判斷是不是第一筆輸出的丟棄牌。如果不是第一筆，先印出 `,`。
   * 印出一個空格加上目前最前面的元素 `t.front()`，然後將其 `pop`（丟棄）。
   * 把目前暴露在最前面的新卡牌 `t.front()` 加到佇列尾端（`t.push(...)`），接著再把原本在頭部的這張牌 `pop` 掉。
3. 當迴圈結束（`t.size() == 1`），此時佇列裡剩下的最後那張牌就是答案，印出 `Remaining card: ` 之後將其清除，為下一組測資做準備。

## 4. Pseudocode

```text
開始
1. 當成功讀入 n 且 n != 0 時，重複執行以下步驟：
2.     將 1 到 n 的整數依序推進佇列 t 中
3.     初始化布林變數 first = true
4.     輸出 "Discarded cards:"
5.     當 佇列 t 的大小 > 1 時執行迴圈：
           如果 first 為 false：
               輸出 ","
           輸出 " " 以及 佇列前端元素 t.front()
           將 佇列前端元素彈出 (丟棄)
           
           將此時新的佇列前端元素推進佇列尾端 (放到最底下)
           將該前端元素彈出
           將 first 設為 false
6.     輸出換行與 "Remaining card: " 以及佇列中最後一個元素 t.front()
7.     將最後一個元素彈出，清空佇列
結束
```
***Correct code
```cpp
#include <iostream>
#include <queue>
#include <algorithm>
#include <fstream>

using namespace std;

int main()
{
    int n;
    queue <int> t;
    // 連續讀取多組測資，直到 n = 0 結束
    while (cin >> n && n != 0) {
        for (int i = 1; i <= n; i++)
            t.push(i);
            
        bool first = true;
        cout << "Discarded cards:";
        
        // 只要剩餘牌數大於 1，就繼續模擬
        while (t.size() > 1) {

            if (!first) cout << ",";
            cout << " " << t.front();
            t.front();
            t.pop(); // 丟棄最上面的牌
            
            t.push(t.front()); // 把下一張牌拿放到最下面
            t.pop(); // 將原本放到後面的那張舊牌頂從前面移除

            first = false;
        }
           
        cout << "\nRemaining card: " << t.front() << endl;
        t.pop(); // 彈出最後一張牌，清空佇列以利下一輪使用
    }
    return 0;
}
```
**Why it works:**

- 完美應用了 `std::queue` 的 `front()`, `pop()`, `push()` 組合技。`t.push(t.front())` 接著 `t.pop()` 的連續動作，在計算機記憶體中完美且高效地模擬了「卡牌抽到底部」的物理行為。
- 利用 `bool first = true;` 開關成功阻止了第一個丟棄元素前方印出多餘逗號的問題。同時，當 $n=1$ 時，`while` 迴圈根本不會進去，程式會直接正確印出 `Discarded cards:\nRemaining card: 1`，精準過濾掉邊界死角。

## 6. Difference and Reflection

### Reflection

- **What mistake did you make?**
  這道題目我的邏輯非常清晰，無論是資料結構的選用（`queue`）還是模擬的步驟都一次到位。唯一在實作時需要特別小心的是，當迴圈結束後，一定要記得對佇列執行最後一次 `t.pop()` 把它徹底清空。如果不清空，上一組測資剩下來的底牌會直接殘留在佇列裡，污染到下一組輸入的資料。

- **What did you learn from debugging this problem?**
  1. 逗號分隔列表（Comma-separated list）的輸出是程式設計競賽中最常出現的格式陷阱。利用一個布林值 `first` 或者是檢查佇列大小來決定「何時該補上逗號」，是一個非常優雅且不易出錯的萬用模板。
  2. 處理多組測試資料（While loops 讀取）時，**維持資料結構的「純潔與重置」是防守的重中之重**。在每輪測資結束時（或是開頭）確保全域/重複使用的容器是完全乾淨的，可以省下大量通靈除錯的時間。

- **If you solve a similar problem again, what will you do better?**
  未來如果遇到類似需要頻繁在頭尾進行資料操作的題目，我除了使用 `std::queue` 之外，也可以視情況考慮使用 `std::deque`（雙端佇列），它支援雙向的 `push` 與 `pop`，在某些更複雜的卡牌翻轉題型中，能提供更強大且直覺的程式碼表現