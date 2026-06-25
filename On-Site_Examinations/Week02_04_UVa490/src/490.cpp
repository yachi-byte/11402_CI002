#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    vector<string> v;
    string s;
    int max_len = 0;

   
    while (getline(cin, s)) {
        v.push_back(s);
        if ((int)s.length() > max_len) {
            max_len = s.length();
        }
    }

    
    for (int j = 0; j < max_len; j++) {
        for (int i = (int)v.size() - 1; i >= 0; i--) {
            if (j < (int)v[i].length()) {
                cout << v[i][j];
            } else {
                cout << " "; // 補空格
            }
        }
        cout << endl;
    }
    return 0;
}