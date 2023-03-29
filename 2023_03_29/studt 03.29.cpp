#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    ofstream file("member.txt");

 
    int b, c, d;
    string a, e, f;

  
    cout << "1번째 회원" << endl;
    cin >> a >> b;
    cout << "2번째 회원" << endl;
    cin >> e >> c;
    cout << "3번째 회원" << endl;
    cin >> f >> d;

    
    if (file.is_open()) {
        file << a << " " << b << endl << e << " " << c << endl << f << " " << d << endl;
        file.close();
    }
    else {
        cerr << "파일을 열지 못했습니다." << endl;
        return 1;
    }

    
    cin.ignore();

    cout << "---------------회원 명부 파일 읽기--------------" << endl;
    
    ifstream read_file("member.txt");
    if (read_file.is_open()) {
        string line;
        while (getline(read_file, line)) {
            cout << line << endl;
        }
        read_file.close();
    }
    else {
        cerr << "파일을 열지 못했습니다." << endl;
        return 1;
    }

    return 0;
}