#include <iostream>
#include<vector>
#include<array>
using namespace std;

int main()
{
    int N, Q;
    int num;
    int count = 0;
    int answer;
    vector<int> v;
    int arr[100];
    int sort[100];
    while (cin >> N >> Q && N != 0 && Q != 0) {
        
        for (int i = 0; i < N; i++) {
            cin >> num;

            if (num < v[i])
                auto pos = v.begin();
                v.insert(num,i);
        }
        
        cin >> answer;
    }
        

    
}
