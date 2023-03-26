#include <iostream>
#include <vector>
using namespace std;

int main() {
    int x;
    int y;
    cout << "x를 입력해주세요" << endl;
    cin >> x;
    cout << "y를 입력해주세요" << endl;
    cin >> y;

    while (x <= 0 || y <= 0) { 
        cout << "x와 y를 다시 입력해주세요" << endl;
        cout << "x를 입력해주세요" << endl;
        cin >> x;
        cout << "y를 입력해주세요" << endl;
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