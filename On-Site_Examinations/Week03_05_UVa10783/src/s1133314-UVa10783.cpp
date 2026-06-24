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

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
