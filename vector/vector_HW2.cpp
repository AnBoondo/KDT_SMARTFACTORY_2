#include <iostream>
#include<vector>
using namespace std;


int main()
{
    int n;
    int sum = 0;
    cout << "n �Է� ��: ";
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {

        cout << "���ڸ� �Է��ϼ��� (0: exit : )" << endl;
        cin >> v[i];
        //<< v.at(i) <<
        
        sum += v[i];
    }
    cout << (float)sum << endl;

}