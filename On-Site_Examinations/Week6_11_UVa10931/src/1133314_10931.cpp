#include <iostream>
#include<array>
#include<cmath>
using namespace std;

int main()
{
    int t;
    while (cin >> t &&t!=0) {
        int n = t;
        int count = 0;
        int array[31] = {};
        cout << "The parity of ";
        

            for (int i = 31; i >= 0; i--) {
                if (n - exp2(i) >= 0) {
                    array[i] = 1;
                    n -= exp2(i);
                }
                else array[i] = 0;
            }
            int max = 0;
            for (int y = 0; y <= 31; y++) {
                if (array[y] == 1) {
                    max = y;
                    count++;
                }

            }
            for (int j = max; j >= 0; j--) {
                cout << array[j];
            }

            cout << " is " << count << " (mod2)." << endl;
        
       

        

        
    
    }
    return 0;
}
