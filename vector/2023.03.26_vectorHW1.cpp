#include <iostream>
#include <vector>
using namespace std;

int main() {
    int x;
    int y;
    cout << "x�� �Է����ּ���" << endl;
    cin >> x;
    cout << "y�� �Է����ּ���" << endl;
    cin >> y;

    while (x <= 0 || y <= 0) { 
        cout << "x�� y�� �ٽ� �Է����ּ���" << endl;
        cout << "x�� �Է����ּ���" << endl;
        cin >> x;
        cout << "y�� �Է����ּ���" << endl;
        cin >> y;
    }

    
    vector<vector<int>> v(x, vector<int>(y));
    
    for (int i = 0; i < v.size(); i++) {
        for (int j = 0; j < v.at(i).size(); j++) {
            v[i][j] = i * y + j + 1;
        }


    }
    for (int i = 0; i < v.size(); i++) {
        for (int j = 0; j < v[i].size(); j++) {
            cout << v.at(i).at(j) << "      ";
        }
        cout << endl;
    }
    return 0;
}