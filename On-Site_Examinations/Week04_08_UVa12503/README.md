# UVa 12503 - Robot Instructions

Use this template to review your coding performance for each problem. Write clearly and use your own words.

## 1. Problem Information

- **Platform:** UVa
- **Problem ID:** 12503
- **Problem Title:** Robot Instructions
- **Problem Link:** [UVa 12503 - Robot Instructions](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=3947)
- **Source Code (Fail):** [./src/12503_fail.cpp](./src/12503_fail.cpp)
- **Source Code (Correct/Accepted):** [./src/12503.cpp](./src/12503.cpp)

## 2. Problem Statement in My Own Words

有一個機器人一開始站在原點 0 的位置，我們可以對它下達 $n$ 個指令。指令有三種型態：
1. `LEFT`：向左移動一格（座標 $-1$）。
2. `RIGHT`：向右移動一格（座標 $+1$）。
3. `SAME AS i`：重複執行第 $i$ 次下達的那個指令。
請計算出執行完這 $n$ 個指令後，機器人最終會停在哪一個座標。

- **What is the input?**
  第一行有一個正整數 $T$，代表有幾組測試資料。
  每組測資的第一行是一個整數 $n$（$1 \le n \le 100$），代表指令的數量。接下來有 $n$ 行，每行代表一個指令。
- **What is the expected output?**
  對於每組測試資料，輸出一行，代表機器人最終停留的座標值。
- **What are the main rules or constraints?**
  `SAME AS i` 中的 $i$ 必定是先前已經出現過的有效指令編號，且編號是從 1 開始計算。指令中可能帶有空格（如 `SAME AS` 後面接數字），讀取時必須精確分流。
- **What is the core task you must solve?**
  1. 正確宣告字串結構以辨識 `LEFT`、`RIGHT` 或 `SAME`。
  2. 當遇到 `SAME` 時，安全地吃掉中間的文字 `AS`，並讀取後方的整數編號，完成 1-indexed 到 0-indexed 的轉換。
  3. 在每組測資開始前確實將加總器 `total` 重置清零。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
這題需要重複存取過去的歷史指令，最直覺的做法就是開一個陣列 `step`。如果是 `LEFT` 就存 `-1`，`RIGHT` 就存 `1`。遇到 `SAME AS i` 時，直接去抓 `step[i]` 的值過來拷貝。但原先誤將 `S` 宣告為 `char` 導致無法讀取完整單字，且 `if ("LEFT")` 語法錯誤導致條件永遠為真，加總時也發生了變數錯置與未清零的狀況。

### Final Strategy
1. 將讀取變數改為 `string S;`。
2. 巡邏 $n$ 次指令，每次先 `cin >> S;`。
3. 如果 `S == "LEFT"`，目前這步 `step[j] = -1`；如果 `S == "RIGHT"`，目前這步 `step[j] = 1`。
4. 如果 `S == "SAME"`，代表後面還接著 `AS` 和一個整數。此時再宣告一個垃圾字串 `string trash;` 呼叫 `cin >> trash;` 把 `AS` 吃掉，最後 `cin >> s;` 讀入目標步數。因為題目從 1 開始算，所以拷貝公式為 `step[j] = step[s - 1]`。
5. 每次做好當前這步後，直接用 `total += step[j]` 進行動態累加。
6. 每組 $n$ 次指令完全結束後，印出 `total` 並換行。

## 4. Pseudocode

```text
開始
1. 讀取總組數 T
2. FOR i from 0 to T-1:
3.     讀取指令數量 n
4.     初始化 total = 0
5.     建立大小為 105 的整數陣列 step
6.     FOR j from 0 to n-1:
           讀取字串 S
           如果 S 等於 "LEFT"：
               step[j] = -1
           否則如果 S 等於 "RIGHT"：
               step[j] = 1
           否則如果 S 等於 "SAME"：
               讀取字串 trash (吃掉 "AS")
               讀取整數 s
               step[j] = step[s - 1]
           
           total += step[j]  // 走完一步，立刻累加
7.     輸出 total 並換行
結束
```
***Correct Code
```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
    int T = 0;
    if (cin >> T) {
        for (int i = 0; i < T; i++) {
            int n = 0;
            cin >> n;
            
            vector<int> step(n); // 動態開闢大小為 n 的陣列，安全防守
            int total = 0;       // 核心修正 1：total 必須在每組 Case 開始時清零重置

            for (int j = 0; j < n; j++) {
                string S;        // 核心修正 2：改用 string 才能正確儲存單字指令
                cin >> S;

                if (S == "LEFT") { // 核心修正 3：修正字串比較語法
                    step[j] = -1;
                }
                else if (S == "RIGHT") {
                    step[j] = 1;
                }
                else if (S == "SAME") {
                    string trash;
                    cin >> trash; // 核心修正 4：把多餘的單字 "AS" 從輸入緩衝區吃掉
                    
                    int s;
                    cin >> s;
                    step[j] = step[s - 1]; // 核心修正 5：將 1-indexed 轉為 0-indexed 的 [s-1]
                }
                
                // 核心修正 6：一邊做一邊直接累加目前的位移步數
                total += step[j];
            }
            cout << total << endl;
        }
    }
    return 0;
}
```
**Why it works:**

- 修正了 `string` 比較的條件語句。`S == "LEFT"` 能精確觸發相對應的移動分支，解決了原本字串字面值在 `if` 內永遠為真的邏輯死角。
- 設計了緩衝區防禦機制。透過 `cin >> trash` 順利抽離了夾在中間的字串 `"AS"`，使得後續的 `cin >> s` 可以精確讀到整數編號，避免了輸入流卡死崩潰。
- 修正了歷史查表的索引位移。因為陣列是從 `0` 開始紀錄，而題目指令是從 `1` 開始編號，改用 `step[s - 1]` 達成了完美的映射比對。

## 6. Difference and Reflection

### Key Differences

| Item | Fail Code (原本寫法) | Correct Code (修正後寫法) |
|---|---|---|
| **Data Type (字串)** | 宣告 `char S;` 且在 `if` 內寫 `if ("LEFT")`，這會因為指標非空導致永遠執行第一個分支，後面完全去路。 | 改用 `string S;` 並用標準的 `==` 進行字串內容比對，分支分流精確無誤。 |
| **Input Buffer (緩衝區)** | 遇到 `SAME AS 1` 時，試圖在讀完 `SAME` 後直接用 `cin >> s` 讀取整數，這會因為撞上字串 `"AS"` 導致讀取流當場卡死。 | 用一個 `trash` 字串將 `"AS"` 讀走清空，確保整數 `s` 可以被安全乾淨地讀入。 |
| **Index Mapping (查表)** | 使用 `step[s + 1]`，方向完全相反，會讀取到尚未定義的未來垃圾記憶體資料。 | 改用 `step[s - 1]`，精準抓回過去第 `s` 步所記錄下的移動軌跡。 |
| **Initialization (重置)** | `total` 宣告在最外層且沒有在迴圈內清零，導致 Case 1 的答案會直接疊加到 Case 2，數據嚴重污染。 | 將 `total = 0;` 移入 `T` 迴圈內部，保證每組測試資料在起跑時都是乾淨的 `0` 座標。 |

### Reflection

- **What mistake did you make?**
  這題我犯了幾個標準的語法細節錯誤：第一是把 `char` 和 `string` 搞混，導致沒辦法讀取一整個單字；第二是不知道在 C++ 裡直接把引號字串放進 `if("LEFT")` 會被當成永遠為真；第三是漏了處理 `SAME` 和數字中間夾著的 `"AS"`，導致 `cin` 讀取流直接壞掉。

- **What did you learn from debugging this problem?**
  1. 遇到含有空格或多個單字的複雜指令（如 `SAME AS 5`）時，要像剝洋蔥一樣，用 `cin >>` 順序把不要的字串（雜訊）讀走，才能順利拿到後面的關鍵數據。
  2. 在 C++ 裡，千萬不能直接寫 `if ("字串")`，一定要用變數去進行 `==` 比較。
  3. 處理多組 Case 題型，**「累加變數（如 `total`）一定要在每組迴圈開頭重新歸零」**，這是拿到 AC 的基本防守紀律。

- **If you solve a similar problem again, what will you do better?**
  未來遇到類似的指令模擬、歷史查表題目，我會第一時間確立好 0-indexed 與 1-indexed 的減一對齊關係。在寫輸入的時候，會先在紙上畫出輸入格式的單字順序，用一對一的 `cin` 把格式雜訊過濾乾淨，一次把輸入流與變數重置完成