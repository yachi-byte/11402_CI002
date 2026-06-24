// 12405 


#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int main()
{
	int n, m;
	int test = 0;

	while (cin >> n>>m && n!=0 && m!=0) {
		vector<int> dragon(n, 0);
		vector<int> knight (m, 0);
		

		for (int i = 0; i < n; i++) {
			cin >> dragon[i];
		}
		for (int i = 0; i < m; i++) {
			cin >> knight[i];
		}

		sort(dragon.begin(), dragon.end());
		sort(knight.begin(), knight.end());
		
		int cost = 0;
		vector<int> waste(m, 0);

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				 
				if (knight[j] >= dragon[i] && waste[j] != 0) {
					
					cost += knight[j];
					break;
				}
					
				}
			}
		}

		

		cout << "Case " << test + 1 << ": " << endl;
		test++;


	}



