// 12503.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <array>
using namespace std;


int main()
{
	
	int T = 0, n = 0, x = 0,total = 0;
	char S;
	while (cin >> T) {
		for (int i = 0; i < T; i++) {
			int step[101];
			cin >> n;
			int k = 0, s;

			for (int j = 0; j < n; j++) {
				cin >> S;

				if ("LEFT") {
					step[k] = -1;
					k++;
				}
				else if ("RIGHT") {
					step[k] = 1;
					k++;
				}
				else if ("SAME AS") {
					cin >> s;
					step[k] = step[s + 1];
					k++;

				}


			}
			for (int z = 0; z < k + 1; z++) {
				total += step[k];
			}
			cout << total;
		}
	}


}

