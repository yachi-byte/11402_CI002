#include <iostream>
#include<string>
#include<vector>
#include<array>
using namespace std;

int main()
{
    int c;
    string t;
   //cin.ignore();
    
    
    int array[128] = {};

    while (getline(cin,t)) {
        int num = 0;
        
        for (int i = 0; i < t.length(); i++) {
            cout << i;
            /*num = i - '0';
            cout << num;
            array[num] += 1;*/
            
        }
        for (int j = 0; j < 128; j++) {
            if (array[j] >= 1)
                cout << j << array[j];
            

        }
        
        //cout << abs('A'-0);
    }
    return 0;

    

}
