// 10252 //10041
#include <iostream>
#include <algorithm>
#include <vector>
#include <array>
#include <queue>

using namespace std;

int main()
{
    int n;
    while (cin >> n) {

    }
        for (int i = 0; i < n; i++) {
            vector<int> a(0);
            int c;
            int total = 0;
            while (cin >> c && (c != '\n')) {

                a.push_back(c);
                //for (int j = 0; j < a.size(); j++)  cout << a[j];
                sort(a.begin(), a.end());

                int length = a.size();
                int mid1, mid2;
                if (length % 2 == 0) {
                    mid1 = a[length / 2];
                    //mid2 = mid1;
                }
                else {
                    mid1 = a[length / 2];
                    //mid2 = a[(length / 2)-1];
                }

                for (int j = 0; j < length; j++) {
                    if (mid1 - a[j] < 0)
                        total += a[j] - mid1;
                    else total += mid1 - a[j];
                }
                //break;
                
            }
            cout << total << '\n';
            }
            
            
        }
       



