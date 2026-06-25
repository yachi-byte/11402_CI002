// 11150.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

int main()
{
    int N = 0;

    while (cin >> N) {
        int empty = 0, total = 0;

       /**/ total += N;
        while (N > 0) {
            total += N / 3;
            if (N % 3 == 2)
                total += 1;
            N /= 3;
            
        }
        /*
        total += N;
        while (N > 0) {
            total += N / 3;
            empty = N / 3 + N % 3;
            if (empty % 3 == 2)
                total += 1;
            N /= 3;

        }*/
        cout << total;
    }
/*
       
        if (N == 0) cout << 0;

        total += N;
        if (N % 3 == 2)
            empty += 1;
            empty = N / 3 ;
        while (N / 3 >= 1 && N % 3 == 0) {
            total += N / 3;
            N -= 3;
        }
        total += empty;
   
        cout << total;
   }*/
}