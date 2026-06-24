# UVa 10189 - Minesweeper

Use this template to review your coding performance for each problem. Write clearly and use your own words.

## 1. Problem Information

- **Platform:** UVa
- **Problem ID:** 10189
- **Problem Title:** Minesweeper
- **Problem Link:** [UVa 10189 - Minesweeper](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=13&page=show_problem&problem=1130)
- **Source Code (Fail):** [./src/10189_fail.cpp](./src/10189_fail.cpp)
- **Source Code (Correct/Accepted):** [./src/10189.cpp](./src/10189.cpp)

## 2. Problem Statement in My Own Words

模擬踩地雷遊戲的地圖生成。給定一個充滿地雷（`*`）與安全區域（`.`）的網格地圖，我們要計算出所有安全區域格子周圍的「九宮格範圍內」到底藏有幾顆地雷，並將其數字標記在該格。

- **What is the input?**
  包含多組測試資料。每組開頭有兩個正整數 $m$ 與 $n$（$0 < m, n \le 100$），代表地圖的列數（Row）與行數（Column）。接下來 $m$ 行包含地圖字元。當 $m = 0, n = 0$ 時代表結束。
- **What is the expected output?**
  輸出處理後的網格地圖。地雷仍顯示 `*`，安全區域則顯示周圍的地雷總數。每組測資輸出前要加上 `Field #x:`，且每組測資的輸出之間要空一行。
- **What are the main rules or constraints?**
  位於地圖邊緣或角落的格子，其周圍格子不能超出邊界。每組測資之間的空行格式必須嚴格控管。
- **What is the core task you must solve?**
  1. 正確控制 `while` 迴圈在讀到 `0 0` 時跳出，不造成死迴圈。
  2. 當偵測到地雷時，安全地將其周圍 8 個方向的格子計數加 1，同時做好陣列邊界檢查。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
想說讀到地雷 `*` 時，就把周圍的格子都加 1。但原先試圖用極其複雜的 `if` 條件（例如 `i - 1 < 0`）去切分討論「左上角、右上角、四個邊緣」等狀況，導致程式碼變得非常冗長、不好除錯，且到處漏看條件。此外，舊寫法的 `while (m != 0 && n != 0)` 內部漏寫了重新讀入 $m$ 與 $n$ 的敘述，導致程式陷入死迴圈。

### Final Strategy
改用相對座標陣列（方向陣列）走訪與統一邊界防禦。定義 `dx[]` 和 `dy[]` 陣列代表 8 個方向，遇到地雷時直接跑一個 0 到 7 的迴圈。計算出新座標後，加上一個通用的安全判定 `if (nx >= 0 && nx < m && ny >= 0 && ny < n)`，就不需要分開討論角落，能用短短幾行優雅地處理好所有邊界狀況。

## 4. Pseudocode

```text
Start
1. 初始化 testcase = 0
2. 當成功連續讀入 m 和 n，且 m != 0 且 n != 0 時重複執行：
3.     testcase++
4.     如果 testcase > 1，輸出一個空行 (格式要求)
5.     宣告 m x n 的字元矩陣 map 與整數矩陣 grid (初始化為 0)
6.     讀入 m x n 的地圖字元存入 map
7.     巡邏地圖的每一個格子 (i, j)：
           如果 map[i][j] == '*'：
               針對 8 個方向 (k 從 0 到 7)：
                   nx = i + dx[k], ny = j + dy[k]
                   如果 (nx, ny) 沒有超出地圖邊界：
                       grid[nx][ny] 加 1
8.     輸出 "Field #x:"
9.     巡邏並輸出最終地圖結果
End
```
*** Correct Code
```cpp
#include <vector>
#include <iostream>
#include <string>
using namespace std;

int main()
{
    int m, n;
    int testcase = 0;
    
    // 定義 8 個方向的相對位移
    int dx[] = {-1, -1, -1,  0, 0,  1, 1, 1};
    int dy[] = {-1,  0,  1, -1, 1, -1, 0, 1};

    // 核心修正：將讀取動作放進 while 條件中，避免無窮迴圈
    while (cin >> m >> n && (m != 0 || n != 0)) {
        testcase++;
        
        // 題目要求的格式：除了第一組之外，每組 Case 之間要空一行
        if (testcase > 1) cout << endl;

        vector<vector<char>> map(m, vector<char>(n));
        vector<vector<int>> grid(m, vector<int>(n, 0));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                cin >> map[i][j];
            }
        }

        // 核心計數邏輯
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (map[i][j] == '*') {
                    for (int k = 0; k < 8; k++) {
                        int nx = i + dx[k];
                        int ny = j + dy[k];

                        // 統一的防禦性邊界檢查
                        if (nx >= 0 && nx < m && ny >= 0 && ny < n) {
                            grid[nx][ny]++;
                        }
                    }
                }
            }
        }

        // 輸出結果
        cout << "Field #" << testcase << ":" << endl;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (map[i][j] == '*') {
                    cout << '*';
                } else {
                    cout << grid[i][j];
                }
            }
            cout << endl;
        }
    }
    return 0;
}
```
**Why it works:**

- 使用了二維地圖題目的經典技巧——**方向陣列（`dx`, `dy`）**。這能把原本高達數十行、容易漏掉狀況的角落 `if-else` 比對，壓縮成一個簡單的 8 次迴圈，大幅降低寫錯邏輯的機率。
- 將 `cin >> m >> n` 放進 `while` 的控制條件中，使得程式能連續讀取直到遇上結束標誌 `0 0`，完美杜絕死迴圈。

## 6. Difference and Reflection

### Key Differences

| Item | Fail Code (原本寫法) | Correct Code (修正後寫法) |
|---|---|---|
| **Logic (核心邏輯)** | 試圖用手動列舉地雷周圍的所有角落邊緣組合（如 `i-1 < 0` 且 `j-1 < 0`），程式碼充斥大量繁瑣的巢狀 `if`，且漏掉很多邊緣配對（如左上/右上交叉的情形）。 | 引進 `dx[]`、`dy[]` 方向陣列。不分特殊地點，一律先算出目標座標，再由統一的 `if` 條件式做範圍過濾。 |
| **Edge Cases (測資格式)** | 沒有設計 Case 與 Case 之間的空白行控制。另外，`while` 迴圈內部沒有重新讀取指令，一入迴圈即卡死。 | `while(cin >> m >> n)` 保證正確換組，且透過 `if (testcase > 1) cout << endl;` 嚴格滿足題目的間隔空行規範。 |
| **Array Syntax (結構)** | 雖然正確開了 `grid` 與 `map`，但在特殊條件區（如 `j + 1 >= n` 內）忘記對 `grid` 進行數值更新。 | 邏輯一體化，不論地雷在中央還是角落，皆能透過單一計數區塊完成更新，無任何漏網之魚。 |

### Reflection

- **What mistake did you make?**
  這次踩了兩個大坑：第一是漏了在 `while` 內部更新輸入數值，導致本地端測試時瘋狂死迴圈；第二是把邊界防禦想得太複雜，試圖用純手寫 `if-else` 去窮舉地圖的四個角落和四條邊，結果越寫越亂。

- **What did you learn from debugging this problem?**
  1. 以後只要遇到二維矩陣需要走訪「周圍八個方向」或「上下左右四個方向」的題目，**絕對不要用手寫 `if-else` 去分開討論邊緣**。直接建立 `dx[]` 和 `dy[]` 陣列來跑迴圈，程式碼才會乾淨。
  2. 處理多組測資時，`while` 的條件一定要綁定 `cin` 讀取，才能在最後遇到 `0 0` 時漂亮地結束。
  3. UVa 的題目非常看重輸出格式（像是「每組測試資料間空一行」），這需要利用 `testcase > 1` 的小技巧來精準控制。

- **If you solve a similar problem again, what will you do better?**
  下次再看到二維網格走訪或踩地雷變型題，我會起手就開好方向陣列，並建立通用的 `nx, ny` 邊界檢查機制。在處理輸出時，也會先把空行的輸出位置想好，一次就把格式寫到位！
