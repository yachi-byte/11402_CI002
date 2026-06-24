#include <iostream>
#include <queue>
#include <algorithm>
#include <fstream>

using namespace std;

ofstream fout("output.txt");//cout 改成 fout

int main()
{
    int n;
    queue <int> t;
    while (cin >> n && n != 0) {
        for (int i = 1; i <= n; i++)
            t.push(i);
        bool first = true;
        fout << "Discarded cards:";
        while (t.size() > 1) {

            if (!first) cout << ",";
            fout << " " << t.front();
            t.pop();
            t.push(t.front());

            t.pop();

            first = false;
        }
           
         
            fout << "\nRemaining card: " << t.front()<<endl;
            t.pop();
    }
    return 0;
}

