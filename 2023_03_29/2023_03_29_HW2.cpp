#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
	string name, password;
	cout << "�̸��� �Է��ϼ��� :";
	cin >> name;
	cout << endl;

	cout << "��й�ȣ�� �Է��ϼ��� :";
	cin >> password;
	cout << endl;

    string fileName, filePassword;
    ifstream inputFile("member.txt");
    while (inputFile >> fileName >> filePassword) {
        if (name == fileName && password == filePassword) {
            cout << "�α��� ����" << endl;
            int number;
            cout << "��ȭ��ȣ�� �Է��ϼ���" ;
            cin >> number;
            
            ofstream file("member_tel.txt");
            if (file.is_open()) {
                file << number << endl;
                string n;
                ifstream inputfile("member_tel.txt");
                
    while (inputfile >> n) {
                    if (name == n) {
                        cout << "��ȭ��ȣ �����ϱ�" << endl;
                        cin >> number;
                        file.close();
            }
           
                }
            }
            return 1;

        }

    }
    cout << "�α��� ����" << endl;
    inputFile.close();

    return 0;
}

	