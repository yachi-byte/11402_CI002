# UVa 10062 - Tell me the frequencies!

Use this template to review your coding performance for each problem. Write clearly and use your own words.

## 1. Problem Information

- **Platform:** UVa
- **Problem ID:** 10062
- **Problem Title:** Tell me the frequencies!
- **Problem Link:** [UVa 10062 - Tell me the frequencies!](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=12&page=show_problem&problem=1003)
- **Source Code (Fail):** [./src/10062_fail.cpp](./src/10062_fail.cpp)
- **Source Code (Correct/Accepted):** [./src/10062.cpp](./src/10062.cpp)

## 2. Problem Statement in My Own Words

讀入一行文字，統計這行文字中各個 ASCII 字元（包含空格、字母、標點符號等）出現的次數。最後將有出現的字元按照特定規則排序後輸出它的 ASCII 編碼與出現頻率。

- **What is the input?**
  包含多組測試資料。每組測資為一行包含各種字元的字串（長度不超過 1000）。讀到檔案結束（EOF）為止。
- **What is the expected output?**
  對於每組字串，依序輸出有出現的字元之「ASCII 碼值」與「出現次數」。**每組測試資料的輸出之間要空一行**。
- **What are the main rules or constraints?**
  排序規則非常特殊且嚴格（雙重不對稱排序）：
  1. 優先按照**「出現次數」由小到大（升序）**排序。
  2. 若出現次數不幸相同，則改按**「ASCII 碼的值」由大到小（降序）**排序。
- **What is the core task you must solve?**
  1. 使用 `getline` 讀取完整包含空格的一整行字串。
  2. 在每輪迴圈中重置計數器，精準統計 ASCII 0 到 127 的頻率。
  3. 實作自訂排序結構（`struct` 搭配 `sort` 比較運算子）來滿足雙重條件。
  4. 嚴格控制多組 Case 之間的空白行格式。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
一開始想說可以用一個大小為 128 的整數陣列來統計每個字元出現的次數。但原本的程式碼還沒寫完，不僅把統計陣列宣告在 `while` 迴圈外部導致測資互相汙染，且內層只印出了索引值 `i`。最重要的是，原先完全漏掉了這題需要「次數升序、ASCII降序」的複雜排序機制。

### Final Strategy
1. 為了能同時對「ASCII 碼」和「次數」做不對稱排序，建立一個結構體 `struct CharFreq`，裡面儲存 `ascii_id` 與 `count`。
2. 寫一個自訂的比較函式 `compareFreq`：
   * 如果 `a.count != b.count`，回傳 `a.count < b.count`（次數小的排前面）。
   * 如果次數相等，回傳 `a.ascii_id > b.ascii_id`（ASCII 碼大的排前面）。
3. 使用 `while (getline(cin, t))` 讀取，並在**迴圈內部**開闢一個計數陣列，走訪字串將字元轉成 ASCII 碼作為 Index 進行累加（`counts[(int)c]++`）。
4. 統計完後，把所有「次數大於 0」的字元打包成結構體丟進 `vector`，呼叫 `std::sort` 進行自訂排序。
5. 控制格式：利用 `first` 布林開關，除了第一組測資外，之後每組輸出前都先印一個 `cout << endl;`。

## 4. Pseudocode

```text
開始
1. 初始化 first_case = true
2. 當利用 getline 成功讀入整行字串 t 時執行迴圈：
3.     如果 first_case 為 false 輸出一個空行，否則將 first_case 設為 false
4.     建立一個大小為 128 且初始為 0 的計數陣列 counts
5.     FOR 每個在字串 t 中的字元 c:
           counts[(int)c] 加 1
6.     建立一個儲存 CharFreq 結構體的動態陣列 list
7.     FOR i from 0 to 127:
           如果 counts[i] > 0：
               將 {ascii_id: i, count: counts[i]} 放進 list
8.     呼叫 sort(list.begin(), list.end(), 自訂比較規則)
           自訂規則：次數小的優先；若次數同則 ASCII 大的優先
9.     FOR 每個在 list 中的元素 item:
           輸出 item.ascii_id 與 item.count
結束
```
***correct code
```cpp
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// 建立結構體，方便同時綁定與處理兩種不同的排序權重
struct CharFreq {
    int ascii_id;
    int count;
};

// 核心自訂排序邏輯：次數升序 (由小到大)，次數相同時 ASCII 降序 (由大到小)
bool compareFreq(const CharFreq& a, const CharFreq& b) {
    if (a.count != b.count) {
        return a.count < b.count; 
    }
    return a.ascii_id > b.ascii_id; 
}

int main()
{
    string t;
    bool first_case = true;

    // 一行一行讀取，包含安全處理空格
    while (getline(cin, t)) {
        // 題目要求的格式：每組資料輸出之間要空一行
        if (!first_case) {
            cout << endl;
        }
        first_case = false;

        // 核心修正 1：陣列必須宣告在 while 內部，確保每組新字串進來時都會自動清零重置
        int counts[128] = {0};

        // 統計字元頻率
        for (char c : t) {
            counts[(int)c]++;
        }

        vector<CharFreq> list;
        // 核心修正 2：將有出現過的小兵打包放入 vector 準備進行自訂交叉排序
        for (int i = 0; i < 128; i++) {
            if (counts[i] > 0) {
                CharFreq temp = {i, counts[i]};
                list.push_back(temp);
            }
        }

        // 執行雙重權重排序
        sort(list.begin(), list.end(), compareFreq);

        // 輸出排好序的完美結果
        for (const auto& item : list) {
            cout << item.ascii_id << " " << item.count << endl;
        }
    }
    return 0;
}
```
**Why it works:**

- 引入了 `struct` 與 `compareFreq` 自訂比較函式，完美馴服了題目極其刁鑽的「次數升序、ASCII 降序」雙重不對稱排序要求。
- 將 `counts` 統計陣列內縮到 `while(getline)` 內部宣告。這使得每遇到一條新字串，陣列就會被強制刷新清零，徹底根除了多組測資殘留舊數據互相干涉的悲劇。
- 使用 `if (!first_case) cout << endl;` 的滾動式換行技巧，精準符合了 OJ 系統要求的「Case 之間有空行、但最後一組 Case 結尾不得多出空行」的嚴格格式。

## 6. Difference and Reflection

### Key Differences

| Item | Fail Code (原本未完成程式碼) | Correct Code (修正後 AC 程式碼) |
|---|---|---|
| **Variables Scope (生命週期)** | 將 `array[128]` 宣告在 `while` 外部，上一組字串算出來的殘留次數會直接累加到下一組，導致數據嚴重污染。 | 統計陣列宣告在 `while` 迴圈內，每筆新測資讀入時皆保證是乾淨的全 `0` 狀態。 |
| **Logic (排序機制)** | 完全沒有設計排序機制，只試圖用單層 `for` 迴圈依 ASCII 順序印出，完全忽略了題目「次數第一、ASCII第二」的規定。 | 建立 `CharFreq` 結構體與自訂 `sort` 比較規則，精準落實「次數小排前、次數同則 ASCII 大排前」的雙重權重分配。 |
| **Output Handling (格式)** | 迴圈內誤寫為 `cout << i;` 且完全沒有控管測資與測資之間的換行空行。 | 修正為印出 `ascii_id` 與空格與 `count`，並利用 `first_case` 布林變數完美控制測資間的留白格式。 |

### Reflection

- **What mistake did you make?**
  這題我在實作時遺漏了幾個關鍵的大架構：首先是把用來統計的陣列放錯了位置（放在 `while` 外面沒清零）；其次是沒有仔細看清題目隱藏的排序陷阱，誤以為直接照 ASCII 碼順序印出即可，導致程式邏輯大幅度地未完成。

- **What did you learn from debugging this problem?**
  1. 只要題目規定「多組字串連續讀取」，任何用來統計、累加的變數或陣列，**一律要宣告在 `while` 迴圈的內部**，或者在迴圈開頭手動 `clear()` 或清零。
  2. 遇到像這種「優先看Ａ排序，Ａ相同時看Ｂ排序，且方向還一正一反」的複雜排序要求，**在 C++ 裡最頂級也最不容易寫爛的解法，就是直接宣告一個 `struct`（結構體），並在裡面寫自訂比較函式丟給 `std::sort`**。這樣不僅思緒最清晰，程式碼也會非常有條理。

- **If you solve a similar problem again, what will you do better?**
  未來遇到字元頻率統計題，我不會再粗心地直接用 `for` 迴圈從小到大盲目印出。我會先在題目紙上把「排序的優先權重（Primary/Secondary key）」圈起來。如果需要多重排序，起手式就是開 `struct` 配 `vector` 與 `std::sort`，一次把資料結構與防禦格式架設完善