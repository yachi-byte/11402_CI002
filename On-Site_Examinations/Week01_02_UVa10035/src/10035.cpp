#include <iostream>

using namespace std;

int main() {
    long long a, b;
    
    // 讀入兩個數字，直到兩者皆為 0 結束
    while (cin >> a >> b && (a != 0 || b != 0)) {
        int carry = 0;
        int carry_count = 0;

        while (a > 0 || b > 0) {
            // 取出目前最低位的兩個數字，並加上上一次的進位
            int sum = (a % 10) + (b % 10) + carry;
            
            if (sum >= 10) {
                carry = 1;     // 發生進位
                carry_count++; // 進位次數加 1
            } else {
                carry = 0;     // 未發生進位
            }
            
            a /= 10; // 移向下一位
            b /= 10;
        }

        
        if (carry_count == 0) {
            cout << "No carry operation." << endl;
        } else if (carry_count == 1) {
            cout << "1 carry operation." << endl;
        } else {
            cout << carry_count << " carry operations." << endl;
        }
    }
    return 0;
}