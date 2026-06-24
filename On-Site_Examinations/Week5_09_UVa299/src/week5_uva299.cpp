#include <iostream>
using namespace std;


int main() {
	int test;
	int a, b;
	
	while (cin >> test) {
		int t = test;
		int n = 0;
		while (n < t) {
			int num = 0;
			
			cin >> num;
			int arr[51];
			arr[num] = 0;
			for (int i = 0; i < num; i++) {
				cin >> arr[i];

			}
			int count = 0;
			for (int i = 0; i < num; i++) {
				for (int j = 0; j < num-1 ; j++) {

					if (arr[j] > arr[j+1]) {
						swap(arr[j], arr[j+1]);

						count++;						
					}
					else continue;				
				}
			}
			cout << "Optimal train swapping takes " << count << " swaps."<<endl;
			n++;
		}
		


		}
	return 0;
	}

