// s1133314-UVa10783.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cmath>

using namespace std;
 

int main()
{
	int T;
	while (cin >> T) {

		int a = 0, b = 0;
		
		for (int i = 0; i < T;i++) {
	
			cin >> a >> b;
			
			int sum = 0;
			

			if (a == b) {
				if (a != 0 && a % 2 == 1) {
					cout << "Case " << i + 1 << ": " << a << endl;
				}
				else {
					sum == 0;
				}
					
			}

			//cin a < b
			else if (a < b) {
				while (a <= b) {
					if (a != 0 && a % 2 == 1) {  //a is odd

						sum += a;
						a += 2;

					}
					else {
						a++;
						sum += a;
						a += 2;
					}
				}
				
			}
			cout << "Case " << i+1 << ": " << sum << endl;

		}
	}
}
