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