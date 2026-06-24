//410
#include <iostream>
#include <vector>
#include<algorithm>
#include<format>
#include <utility>

using namespace std;

int main()
{
	int c,s;
	int test = 0;
	while (cin >> c >> s ) {
		vector<int> contain (s, 0);
		vector<int> set_s(s, 0);
		vector<int> C2(s, 0);

		//auto p1 = make_pair(0, make_pair (contain,C2));
		auto p1 = make_pair(contain, 0);
		int t = 0;
		auto p2 = make_pair(contain, t);

		float imbalance = 0;
		int all = 0;
		for (int i = 0; i < s; i++) {
			cin >> contain [i];
			cin >> set_s[i];
			all += contain[i];
		}
		float average = all / s;
		sort(set_s.begin(), set_s.end());

		for (int g = 0; g < s; g++) {
			float k = 0;
			k = (set_s[g] + set_s[s - g - 1]);
			if (k < average) imbalance += average - k;
			else imbalance += k - average;

		}

		for (int g = 0; g < s; g++) {
			int index = 0;
			if (p1.second == 0) {
				for (int f = 0; f < s; f++) {
					if (contain[g] == set_s[f]) {
						index = f;
						break;
					}
				}
			}
			p1.second
			(set_s[g] + set_s[s - g - 1]);
		}

		
		cout <<"Set #" << ++test << endl;
		int v = 0;
		for (int k = 0; k < c; k++) {
			cout << k << ": ";
			//odd會有單獨的輸出，而且是按照cin的先後輸出(不是按照大小
			for (int z = 0; z < s; z++) {
				if(contain)
			}
				
			if (s / 2 != 0) {//odd

			}
			else {//even

			}
			if (v  < s) {
				cout << set_s[v] << " " << set_s[s-v-1] << endl;
				v ++;
			}
			else cout << endl;
	
		}
		cout << "IMBALANCE = " << imbalance <<endl;

	}
	return 0;
}

