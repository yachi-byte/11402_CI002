#include <iostream>
#include <string>

using namespace std;

int main() {
    char c;
    bool first = true;

    // 一個字元一個字元讀取
    while (cin.get(c)) {
        if (c == '"') {
            if (first) {
                cout << "``"; // 第一次遇到雙引號，換成兩個左單引號
            } else {
                cout << "''"; // 第二次遇到雙引號，換成兩個右單引號
            }
            first = !first;   
        } else {
            cout << c;
        }
    }
    return 0;
}