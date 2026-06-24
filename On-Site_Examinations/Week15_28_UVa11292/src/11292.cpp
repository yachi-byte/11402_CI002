// 11292 
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int main()
{
	int n, m;
	int test = 0;

	while (cin >> n >> m && n != 0 && m != 0) {
		vector<int> dragon(n, 0);
		vector<int> knight(m, 0);


		for (int i = 0; i < n; i++) {
			cin >> dragon[i];
		}
		for (int i = 0; i < m; i++) {
			cin >> knight[i];
		}

		//knight >= dragon
		if (m >= n) {

			sort(dragon.begin(), dragon.end());
			sort(knight.begin(), knight.end());

			int cost = 0;
			int d = 0;
			int k = 0;
			for (int i = k; i < m; i++) {
				// 
				if (d == n)
					break;

				if (knight[i] >= dragon[d]) {
					k = i;
					cost += knight[i];
					d++;
				}
			}

			if (d == n) {
				cout << cost << endl;
			}
			else {
				cout << "Loowater is doomed!" << endl;
			}
		}
		else {
			cout << "Loowater is doomed!" << endl;
		}
	}
	return 0;
}




