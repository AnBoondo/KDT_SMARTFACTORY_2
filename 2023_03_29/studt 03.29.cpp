#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    ofstream file("member.txt");

 
    int b, c, d;
    string a, e, f;

  
    cout << "1��° ȸ��" << endl;
    cin >> a >> b;
    cout << "2��° ȸ��" << endl;
    cin >> e >> c;
    cout << "3��° ȸ��" << endl;
    cin >> f >> d;

    
    if (file.is_open()) {
        file << a << " " << b << endl << e << " " << c << endl << f << " " << d << endl;
        file.close();
    }
    else {
        cerr << "������ ���� ���߽��ϴ�." << endl;
        return 1;
    }

    
    cin.ignore();

    cout << "---------------ȸ�� ��� ���� �б�--------------" << endl;
    
    ifstream read_file("member.txt");
    if (read_file.is_open()) {
        string line;
        while (getline(read_file, line)) {
            cout << line << endl;
        }
        read_file.close();
    }
    else {
        cerr << "������ ���� ���߽��ϴ�." << endl;
        return 1;
    }

    return 0;
}