#include <iostream>
#include<vector>
using namespace std;


int main()
{
    int n;
    int sum = 0;
    cout << "n 입력 값: ";
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {

        cout << "숫자를 입력하세요 (0: exit : )" << endl;
        cin >> v[i];
        //<< v.at(i) <<
        
        sum += v[i];
    }
    cout << (float)sum << endl;

}