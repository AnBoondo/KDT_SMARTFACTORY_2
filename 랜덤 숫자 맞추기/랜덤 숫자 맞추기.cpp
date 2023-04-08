#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;


int main()
{
    int computer[6];
    int user[6];
    int cnt = 0;

    srand(time(NULL));

    for (int i = 0; i < 6; i++) {
        int num = rand();
        computer[i] = num % 25 + 1;
        for (int j = 0; j < i; j++) {
            if (computer[i] == computer[j]) {
                i--;
                break;
            }
        }
    }

    cout << "1부터 25까지의 숫자 중 중복 없이 6개를 입력하세요." << endl;
    for (int i = 0; i < 6; i++) {
        cout << i + 1 << "번째 숫자: ";
        cin >> user[i];
    }


    for (int i = 0; i < 6; i++) {
        if (find(computer, computer + 6, user[i]) != computer + 6) {
            cnt++;
        }
    }


    cout << "컴퓨터가 뽑은 숫자: ";
    for (int i = 0; i < 6; i++) {
        cout << computer[i] << " ";
    }
    cout << endl;

    cout << "맞춘 숫자 개수: " << cnt << endl;

    switch (cnt) {
    case 0:
        cout << "7등" << endl;
        break;
    case 1:
        cout << "6등" << endl;
        break;
    case 2:
        cout << "5등" << endl;
        break;
    case 3:
        cout << "4등" << endl;
        break;
    case 4:
        cout << "3등" << endl;
        break;
    case 5:
        cout << "2등" << endl;
        break;
    case 6:
        cout << "1등" << endl;
        break;
    default:
        break;
    }
    return 0;
}