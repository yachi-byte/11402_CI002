
#include <iostream>
#include <vector>
#include<algorithm>

using namespace std;

int main()
{
	int n, d, r;
	while (cin >> n >> d >> r && (n != 0 || d != 0 || r != 0)) {
		vector<int> morning (n, 0);
		vector<int> night (n, 0);

		int total_overpaid = 0;

		for (int i = 0; i < n; i++) {
			cin >> morning[i];
		}
		for (int j = 0; j < n; j++) {
			cin >> night[j];
		}
		sort(morning.begin(), morning.end());
		sort(night.begin(), night.end());

		
		for (int g = 0; g < n; g++) {
			
			int k = 0;
			k = (morning[g] + night[n-g-1]);
				
			if (k > d) k = k - d;
			else k = 0;
			total_overpaid += k;
			
		}

		total_overpaid*= r;
		cout << total_overpaid << endl;
	
	}
	return 0;
}

