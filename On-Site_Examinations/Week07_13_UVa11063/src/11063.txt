#include <iostream>
#include<vector>
#include<array>
using namespace std;

int main()
{
    
    int N;
    int arr[101];
    int tmp;
    int sum = 0;
    int test = 0;
    while (EOF) {
        test++;
        while (cin >> N) {
            bool sequence = true;
            if (N < 2 || N >100) {
                sequence = false;
                break;
            }


            for (int i = 0; i < N; i++) {
                cin >> tmp;
                sum += tmp;
                if (i != 0) {
                    if (tmp <= arr[i - 1]) {
                        sequence = false;
                        break;
                    }
                    else if (tmp <= sum) {
                        sequence = false;
                        break;
                    }
                    break;
                }
                arr[i] = tmp;

            }
            if (sequence)
                cout << "case #" << test << ": It is a B2-Sequence." << endl;
            else
                cout << "case #" << test << ": It is not a B2-Sequence." << endl;
        }
    }
    
}
