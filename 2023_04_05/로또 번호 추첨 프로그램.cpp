#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;


int main()
{
	int lotto[6];
	int i, j;
	srand(time(NULL));



	for ( i = 0; i < 6; i++) {
		int num = rand();
		lotto[i] = num % 45 + 1;		
		for (j = 0; j < i; j++) {
			if (lotto[i] == lotto[j]) {
				i--;					
			}
		}
		for (int i = 0; i < 6; i++) {
			
	}
		cout << lotto[i] << "  ";
	}
	return 0;
}