#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {

	ofstream member("member.txt");

	cout << "3명의 회원에 대한 이름, 비밀번호를 순차적으로 입력하세요.\n";

	for (int i = 0; i < 3; i++) {
		cout << i + 1 << "번째 회원 : ";

		string info;
		getline(cin, info);

		if (member.is_open()) member << info << endl;
	}

	member.close();

	ifstream member_r("member.txt");
	string line;

	if (member_r.is_open()) {
		while (getline(member_r, line)) {
			cout << line << endl;
		}
	}

	member_r.close();
}