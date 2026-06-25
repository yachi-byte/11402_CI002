# UVa 299 - Train Swapping

Use this template to review your coding performance for each problem. Write clearly and use your own words.

## 1. Problem Information

- **Platform:** UVa
- **Problem ID:** 299
- **Problem Title:** Train Swapping
- **Problem Link:** [UVa 299 - Train Swapping](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=4&page=show_problem&problem=235)
- **Source Code (on site)(AC):** [./src/299.cpp](./src/299.cpp)

## 2. Problem Statement in My Own Words

有一列火車由許多車廂組成，每個車廂都有一個特定的編號。現在這列火車的車廂順序是亂的，我們只能透過「交換相鄰的兩個車廂」這種操作，來將整列火車的車廂按照編號從小到大（升序）排好。題目要求計算出最少需要進行幾次相鄰交換，才能讓火車完全就位。

- **What is the input?**
  第一行輸入一個整數，代表總共有幾組測試資料（Test cases）。
  每組測試資料包含兩行：第一行是一個整數 $L$（$0 \le L \le 50$），代表火車的長度（車廂總數）；第二行包含 $L$ 個整數，代表目前火車車廂的亂序編號。
- **What is the expected output?**
  對於每組測試資料，輸出一行特定格式的字串：`Optimal train swapping takes X swaps.`，其中 `X` 代表最少需要的相鄰交換次數。
- **What are the main rules or constraints?**
  火車長度 $L$ 最大只有 50，數字範圍非常小，因此使用時間複雜度為 $O(L^2)$ 的泡沫排序法來模擬完全不會有超時（TLE）的問題。
- **What is the core task you must solve?**
  1. 正確控制雙重 `while` 迴圈以讀取測試組數與每組內部的火車長度。
  2. 實作泡沫排序法，並在發生相鄰兩數 `arr[j] > arr[j+1]` 需要 `swap` 時，讓計數器精準累加。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
這題說只能「交換相鄰的兩個車廂」，這完完全全就是**泡沫排序法（Bubble Sort）**的物理移動過程！泡沫排序每次都是比對隔壁的兩個數字，如果前面的比較大就跟後面的交換。因此只要直接實作泡沫排序，並在每次觸發 `swap` 時讓計數器 `count++` 即可。

### Final Strategy
1. 使用 `while (cin >> test)` 讀取總組數，並用內部指標 `n` 跑完所有組數。
2. 每組測資進來時，讀取車廂數量 `num`，並開闢一個大小為 51 的陣列 `arr`。
3. 用一個 `for` 迴圈把所有車廂編號讀入陣列中。
4. 撰寫雙重 `for` 迴圈實作泡沫排序：外層跑 `num` 次，內層邊界設為 `num - 1`，確保 `arr[j+1]` 絕對不會超出目前讀入的車廂範圍。
5. 如果 `arr[j] > arr[j+1]`，呼叫內建的 `swap(arr[j], arr[j+1])` 並執行 `count++`。
6. 排序完成後，依照題目要求的精確字串格式輸出結果。

## 4. Pseudocode

```text
開始
1. 讀入總測試組數 test
2. 初始化 n = 0
3. 當 n < test 時重複執行以下迴圈：
4.     讀入當前火車長度 num
5.     建立大小為 51 的整數陣列 arr
6.     FOR i from 0 to num-1:
           讀入車廂編號存入 arr[i]
7.     初始化交換計數器 count = 0
8.     FOR i from 0 to num-1:
           FOR j from 0 to num-2:
               如果 arr[j] > arr[j+1]：
                   交換 arr[j] 與 arr[j+1]
                   count 加 1
9.     輸出 "Optimal train swapping takes " + count + " swaps."
10.    n 加 1
結束

```
*** Correct Code
```cpp
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int test;
    
    // 讀取總組數
    while (cin >> test) {
        int t = test;
        int n = 0;
        
        // 依序處理每組火車測資
        while (n < t) {
            int num = 0;
            cin >> num;
            
            int arr[51]; // 陣列大小開 51 完美容納題目 L <= 50 的限制
            for (int i = 0; i < num; i++) {
                cin >> arr[i];
            }
            
            int count = 0;
            // 標準泡沫排序法，計算相鄰交換次數
            for (int i = 0; i < num; i++) {
                for (int j = 0; j < num - 1; j++) {
                    if (arr[j] > arr[j + 1]) {
                        swap(arr[j], arr[j + 1]);
                        count++; // 每次發生相鄰交換，計數器就加 1
                    }
                }
            }
            
            cout << "Optimal train swapping takes " << count << " swaps." << endl;
            n++;
        }
    }
    return 0;
}
```
**Why it works:**

- 泡沫排序法（Bubble Sort）在數學上的交換次數，恰好等於該數列的「逆序數對（Inversion Number）」，這與題目「只能交換相鄰車廂且求最少次數」的物理限制完美契合，因此這個貪婪的模擬就是不變的最佳解。
- 內層迴圈邊界控制在 `num - 1`，這保證了在進行 `arr[j+1]` 比對時，最高索引只會觸及 `num - 1`，絕對不會發生陣列越界存取垃圾資料的危險。
- 計數器 `count` 在每組測資小迴圈開始時都會被重新正確初始化為 `0`，保證了多組數據之間不會互相干擾。

## 6. Difference and Reflection

### Reflection

- **What mistake did you make?**
  這道題目我有發現是泡沫排序法的計數變型。原碼在實作上只有一個微小且不影響 AC 的小冗餘（在讀完 `num` 後寫了 `arr[num] = 0;`，這行在後續會被 `for` 讀入與排序完全覆蓋，且當 `num = 51` 時會有越界風險，不過題目限制 $L \le 50$，所以安全過關）。

- **What did you learn from debugging this problem?**
  1. 許多演算法題目會用故事（例如火車車廂、堆疊卡牌）來包裝。只要看到關鍵字如「只能交換相鄰的元素」，就要立刻在腦中聯想到**泡沫排序法（Bubble Sort）**與**逆序數對**的關係。
  2. 變數和陣列宣告在最內層的 `while` 迴圈內部，可以利用 C++ 的變數生命週期特性，在每輪自動重新配置，是一個很乾淨、不用手動清零陣列的聰明寫法。

- **If you solve a similar problem again, what will you do better?**
  未來如果遇到相同概念但資料量變得非常巨大（例如長度 $L \le 100000$）的逆序數對題目時，泡沫排序法的 $O(L^2)$ 就會超時。到時候我會改用**分治法（Divide and Conquer）的合併排序法（Merge Sort）**來在拆解合併的過程中順便計算逆序數，將時間複雜度優化到 $O(L \log L)$