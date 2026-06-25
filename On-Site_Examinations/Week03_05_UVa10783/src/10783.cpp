#include <iostream>
using namespace std;

int main()
{
    int T;
    if (cin >> T) {
        int a = 0, b = 0;
        
        for (int i = 0; i < T; i++) {
            cin >> a >> b;
            int sum = 0; // 每組測資開始時將 sum 歸零

            // 核心優化：如果起點是偶數，直接推進到第一個奇數
            if (a % 2 == 0) {
                a++;
            }

            // 此時 a 必定為奇數，直接每步加 2 穩定前進
            while (a <= b) {
                sum += a;
                a += 2;
            }
            
            // 統一在最外層印出一次，絕不重複
            cout << "Case " << i + 1 << ": " << sum << endl;
        }
    }
    return 0;
}