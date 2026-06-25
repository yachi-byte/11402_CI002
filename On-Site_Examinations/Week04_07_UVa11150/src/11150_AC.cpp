#include <iostream>

using namespace std;

int main()
{
    int N;
    // 標準多組測資連續讀取
    while (cin >> N) {
        int total = N; 
        int empty = N; 
        
        // 開始進行標準的 3 換 1 循環模擬
        while (empty >= 3) {
            int new_cola = empty / 3;
            total += new_cola;
            empty = new_cola + (empty % 3);
        }
        
        // 核心修正（隱藏特殊邊界）：
        // 如果最後剩下 2 個空瓶，可以借 1 個湊成 3 個換新可樂
        // 喝完後產生 1 個空瓶，剛好拿去還給朋友
        if (empty == 2) {
            total += 1;
        }
        
        cout << total << endl;
    }
    return 0;
}