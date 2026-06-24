
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
// #include <stack>

using namespace std;
int main()
{
	int t;
	cin >> t;
	//cin.ignore();
	int count = 1;
	char k1 ;
	char k2 ;

	for (int i = 0; i < t; i++) {
		
		cin >> k1>>k2;
		cin.clear();
		
		//cout << k1 << k2;
		//getline(cin, k);
		int n;
		
		// cout << k;
		cin >> n;
		
		vector <vector<long long int>> v2(n, vector<long long int>(n));

		
		for (int h = 0; h < n; h++) {
			for (int d = 0; d < n; d++) {
				cin >> v2[h][d];
			}
		}
		/*vector<int> v2(n);
		for (int h = 0; h < n; h++) { cin >> v2[h]; }*/

		bool sym = true;
		for (int g = 0; g < n; g++) {
			for (int b = 0; b < n; b++) {

				if (v2[g][b] <0)
					sym = false;
				if (v2[g][b] != v2[n - 1 - g][n - 1 - b])
					sym = false;
			
			}
		}
		cout << "Test #" << i + 1 << ": ";
		if (sym) {
			cout << "Symmetric." << endl; 
		}
		else
			cout << "Non-symmetric." << endl;
	
	}

   
	return 0;
}
