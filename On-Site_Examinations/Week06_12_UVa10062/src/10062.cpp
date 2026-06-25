#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// 建立結構體，方便同時綁定與處理兩種不同的排序權重
struct CharFreq {
    int ascii_id;
    int count;
};

// 核心自訂排序邏輯：次數升序 (由小到大)，次數相同時 ASCII 降序 (由大到小)
bool compareFreq(const CharFreq& a, const CharFreq& b) {
    if (a.count != b.count) {
        return a.count < b.count; 
    }
    return a.ascii_id > b.ascii_id; 
}

int main()
{
    string t;
    bool first_case = true;

    // 一行一行讀取，包含安全處理空格
    while (getline(cin, t)) {
        // 題目要求的格式：每組資料輸出之間要空一行
        if (!first_case) {
            cout << endl;
        }
        first_case = false;

        // 核心修正 1：陣列必須宣告在 while 內部，確保每組新字串進來時都會自動清零重置
        int counts[128] = {0};

        // 統計字元頻率
        for (char c : t) {
            counts[(int)c]++;
        }

        vector<CharFreq> list;
        // 核心修正 2：將有出現過的小兵打包放入 vector 準備進行自訂交叉排序
        for (int i = 0; i < 128; i++) {
            if (counts[i] > 0) {
                CharFreq temp = {i, counts[i]};
                list.push_back(temp);
            }
        }

        // 執行雙重權重排序
        sort(list.begin(), list.end(), compareFreq);

        // 輸出排好序的完美結果
        for (const auto& item : list) {
            cout << item.ascii_id << " " << item.count << endl;
        }
    }
    return 0;
}