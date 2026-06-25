#include <iostream>
#include <algorithm>

using namespace std;

// 計算單一數字的 3n + 1 循環長度
int get_cycle_length(long long n) {
    int length = 1;
    while (n != 1) {
        if (n % 2 == 1) {
            n = 3 * n + 1;
        } else {
            n /= 2;
        }
        length++;
    }
    return length;
}

int main() {
    int i, j;
    // 連續讀取多組邊界區間
    while (cin >> i >> j) {
        cout << i << " " << j << " ";
        
        // 陷阱防守：輸入的 i 有可能大於 j，必須先找出真正的上下界
        int start = min(i, j);
        int end = max(i, j);
        
        int max_cycle = 0;
        for (int k = start; k <= end; k++) {
            int current_cycle = get_cycle_length(k);
            if (current_cycle > max_cycle) {
                max_cycle = current_cycle;
            }
        }
        cout << max_cycle << endl;
    }
    return 0;
}