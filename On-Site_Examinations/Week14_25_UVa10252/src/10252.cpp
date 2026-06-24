// 10252 //10041
#include <iostream>
#include <algorithm>
#include <vector>
#include <array>
#include <queue>
#include<sstream>

using namespace std;

int main()
{
    string s1,s2;
    int array[26];
    int a2[26];
    while (cin >> s1>>s2) {
        for (char c : s1) {
            for (int i = 0; i < 26; i++) {
                if (c == i + 'a') {
                    a2[i] = 1;
                    
                }
            }
        }
        for (char c : s2) {
            for (int i = 0; i < 26; i++) {
                if (c == i + 'a'&&(a2[i] = 1)) {
                    
                    array[i] += 1;
                }
            }
        }
        for (int i = 0; i < 26; i++) {
            if (array[i] != 0) cout << i + '0'<< endl;
        }
    }
    
}


