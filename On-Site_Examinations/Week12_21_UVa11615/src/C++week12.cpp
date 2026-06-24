#include <iostream>
#include <array>
#include <cmath>
#include<fstream>
//11615 679

using namespace std;

int main()
{
    int testcase;

    
    while (cin >> testcase) {
        for (int i = 0; i < testcase; i++) {
            int depth, all;
            int br1, br2;
            int arr[21];

            cin >> depth;
            cin>> br1 >> br2;
            /*
            if (depth < 4 || depth>20) {
                break;
            }*/
            
            

            int d1, d2;
            bool d1t = true;
            bool d2t = true;
            int total = 0;
            for (int j = 0; j < depth; j++) {
                total += pow(2, j);
                if (d1t && total >= br1) {
                    d1 = j+1;
                    d1t = false;
                }
                if (d2t && total >= br2) {
                    d2 = j+1;
                    d2t = false;
                }
            }
            int t = 0;
            if (d1 > d2) t = d1;
            else t = d2;
            //if br2在最後一層 total-2
            if (t == depth)
                all = total;
            //else all = total -(depth-d2=k) 2^1~2^k
            else {
                int k = depth - t;
                
                for (int m = 1; m <= k; m++) {
                    all = total;
                    
                    all-= pow(2, m);
                    cout << pow(2, m);
                }
            }
            cout << all << endl;
            

        }
  
    }
    return 0;
}

