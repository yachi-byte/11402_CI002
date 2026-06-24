// 10252 
#include <iostream>
#include <algorithm>
#include <vector>
#include <array>
#include <queue>
#include<sstream>
#include <string>

using namespace std;

int main()
{
    string s1, s2;
    //int array[26];
    //int a2[26];
    //while (cin >> s1 >> s2) {
    while (getline(cin, s1) && getline(cin, s2)) {
        int count1[26] = { 0 }; // 統計 s1 字母頻率
        int count2[26] = { 0 };

        for (char c : s1) {
            /*for (int i = 0; i < 26; i++) {
                if (c == i + 'a') {
                    a2[i] = 1;

                }
            }*/
            if(c >= 'a' && c <= 'z') count1[c - 'a']++;
        }
        for (char c : s2) {
            if (c >= 'a' && c <= 'z') count2[c - 'a']++;
        }
        for (int i = 0; i < 26; i++) {
            //if (array[i] != 0) cout << i + '0' << endl;
            int common = min(count1[i], count2[i]);
            for (int j = 0; j < common; j++) {
                cout << (char)(i + 'a');
            }
        }
        cout << endl;
    }
    return 0;
}


