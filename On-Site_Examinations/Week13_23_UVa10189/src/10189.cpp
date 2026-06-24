#include <vector>
#include <iostream>
#include <string>
using namespace std;

int main()
{
    int m, n;
    int testcase = 0;
    
    // 定義 8 個方向的相對位移
    int dx[] = {-1, -1, -1,  0, 0,  1, 1, 1};
    int dy[] = {-1,  0,  1, -1, 1, -1, 0, 1};

    // 核心修正：將讀取動作放進 while 條件中，避免無窮迴圈
    while (cin >> m >> n && (m != 0 || n != 0)) {
        testcase++;
        
        // 題目要求的格式：除了第一組之外，每組 Case 之間要空一行
        if (testcase > 1) cout << endl;

        vector<vector<char>> map(m, vector<char>(n));
        vector<vector<int>> grid(m, vector<int>(n, 0));

        // 讀入地圖
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                cin >> map[i][j];
            }
        }

        // 核心計數邏輯
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (map[i][j] == '*') {
                    // 遇到地雷，直接對周圍 8 個方向進行探索
                    for (int k = 0; k < 8; k++) {
                        int nx = i + dx[k];
                        int ny = j + dy[k];

                        // 防禦性邊界檢查：只有在合理的格子內才加 1
                        if (nx >= 0 && nx < m && ny >= 0 && ny < n) {
                            grid[nx][ny]++;
                        }
                    }
                }
            }
        }

        // 輸出結果
        cout << "Field #" << testcase << ":" << endl;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (map[i][j] == '*') {
                    cout << '*';
                } else {
                    cout << grid[i][j];
                }
            }
            cout << endl;
        }
    }
    return 0;
}