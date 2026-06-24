#include <vector>
#include <iostream>
#include <string>
using namespace std;


int main()
{
    int m, n;
    int testcase = 0;
    cin >> m >> n;
    
    while (m != 0 && n != 0) {
        
        vector<vector<int>> grid(m, vector<int>(n, 0));
        vector<vector<char>> map (m, vector<char>(n, 0));
        string cc;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                cin >> map [i][j];
            }
        }
        //*****
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (map[i][j] == '*') {
                    
                    if(i - 1 < 0) {
                        if (j - 1 < 0) {
                            for (int k = i; k <= i + 1; k++) {
                                for (int t = j; t <= j+1; t++) {
                                    grid[k][t] += 1;
                                }
                            }
                        }
                        else {
                            if (j + 1 >= n) {
                                for (int k = i; k <= i + 1; k++) {
                                    for (int t = j - 1; t <= j; t++) {
                                        grid[k][t] += 1;
                                    }
                                }
                            }
                        }
                    }
                    if (i + 1 >= m) {
                        if (j - 1 < 0) {
                            for (int k = i-1; k <= i; k++) {
                                for (int t = j; t <= j + 1; t++) {
                                    grid[k][t] += 1;
                                }
                            }
                        }
                        else {
                            if (j + 1 >= n) {
                                for (int k = i - 1; k <= i; k++) {
                                    for (int t = j - 1; t <= j; t++) {
                                        grid[k][t] += 1;
                                    }
                                }
                            }
                        }
                    }
                    if (i - 1 >= 0 && i + 1 < m ) {
                        for (int k = i - 1; k <= i + 1; k++) {
                            for (int t = j - 1; t <= j+1; t++) {
                                grid[k][t] += 1;
                            }
                        }
                    }
                    
                    
                }
            }
        }

        //*****
        testcase++;
        cout << "Field #" << testcase << ":"<<endl;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (map[i][j] == '*') {
                    cout << '*';
                }
                else cout << grid[i][j];
            }
            cout << endl;
        }
        

    }
}

