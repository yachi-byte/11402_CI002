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
		
		vector<int> list(n, 0);
		cin >> m;
		vector<char> straw(m, '/0');
		

		for (int i = 0; i < m; i++) {
			cin >> straw[i];
		}

			//if (m % 3 != 0) answer += 1;
			int count = 0;
			bool is = false;
			int answer = 0;
			for (int i = 0; i < m; i++) {

				if (straw[i] == '.' && is == false) {
					answer += 1;
					is = true;
					count++;
				}
				else if (straw[i] == '.' && is == true)
					count++;
				else if (straw[i] == '#'&& count!=0 )
					count++;


				if (count == 3) {
					count = 0;
					is = false;
				}
				//else if(straw[i] == '#')
					//continue;

			}
			
			cout << "Case " << test + 1 << ": " << answer<< endl;
			test++;
			
		
	}
	
}

