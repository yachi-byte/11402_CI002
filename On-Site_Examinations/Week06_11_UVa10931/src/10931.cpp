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