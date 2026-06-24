// 12405 //Scarecrow

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int main()
{
	int n,m;
	int test = 0;
	cin >> n;
	while (n--) {
		
		cin >> m;
		vector<char> straw(m, '\0');
		

		for (int i = 0; i < m; i++) {
			cin >> straw[i];
		}

			
			int answer = 0;
			for (int i = 0; i < m; ) {

				if (straw[i] == '.' ) {
					answer += 1;
					i+=3;
				}
				
				else if (straw[i] == '#' )
					i++;
			}
			
			cout << "Case " << test + 1 << ": " << answer<< endl;
			test++;
			
		
	}
	
}

