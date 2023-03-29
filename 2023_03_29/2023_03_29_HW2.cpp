#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
	string name, password;
	cout << "이름을 입력하세요 :";
	cin >> name;
	cout << endl;

	cout << "비밀번호를 입력하세요 :";
	cin >> password;
	cout << endl;

    string fileName, filePassword;
    ifstream inputFile("member.txt");
    while (inputFile >> fileName >> filePassword) {
        if (name == fileName && password == filePassword) {
            cout << "로그인 성공" << endl;
            int number;
            cout << "전화번호를 입력하세요" ;
            cin >> number;
            
            ofstream file("member_tel.txt");
            if (file.is_open()) {
                file << number << endl;
                string n;
                ifstream inputfile("member_tel.txt");
                
    while (inputfile >> n) {
                    if (name == n) {
                        cout << "전화번호 수정하기" << endl;
                        cin >> number;
                        file.close();
            }
           
                }
            }
            return 1;

        }

    }
    cout << "로그인 실패" << endl;
    inputFile.close();

    return 0;
}

	