#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {

	ifstream member("member.txt");
	string name, pw, name_in, pw_in;

	cout << "이름을 입력하세요: ";
	cin >> name_in;

	cout << "비밀번호를 입력하세요: ";
	cin >> pw_in;

	bool is_login = false;

	if (member.is_open()) {
		while (member >> name >> pw) {
			if (name_in == name && pw_in == pw) {
				is_login = true;
				break;
			}
		}

		if (is_login) {
			cout << "로그인 성공\n";

			string num_in, num;

			cout << "전화번호를 입력하세요 : ";
			cin >> num_in;

			ifstream member_tel_r("member_tel.txt");

			bool is_modify = false;
			string member_tel_tmp = "";

			if (member_tel_r.is_open()) {

				while (member_tel_r >> name >> num) {
					string line = name + " ";
					if (name_in == name) {
						is_modify = true;
						line += num_in;
					}
					else {
						line += num;
					}
					member_tel_tmp += line + "\n";
				}
			}

			member_tel_r.close();


			ofstream member_tel_w;

			if (is_modify) {
				member_tel_w.open("member_tel.txt");
				member_tel_w << member_tel_tmp;
			}
			else {
				member_tel_w.open("member_tel.txt", ios::app);
				if (member_tel_w.is_open()) {
					member_tel_w << name_in << " " << num_in << endl;
				}
			}

			member_tel_w.close();
		}
		else cout << "로그인 실패\n";
	}
	else cout << "파일을 읽지 못하였습니다.\n";

	member.close();

}


// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
