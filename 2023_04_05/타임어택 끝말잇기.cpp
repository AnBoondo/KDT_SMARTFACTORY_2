#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

int main(void) {
    clock_t startTime = clock();
    string word = "hello";
    string word1 = "";
    int n = word.size();
    int number_words = 0;
    cout << word << endl;
    cout << "���� �ܾ �Է��ϼ���: " << word[n - 1] ;
    vector<string> words; 

    while (1) {
        cin >> word1;
        int a = word1.size();
        cout << endl << "���� �ܾ �Է��ϼ��� :" << word1[a - 1];
        bool alreadyExists = false;
        for (int i = 0; i < number_words; i++) {
            if (words[i] == word1) {
                alreadyExists = true;
                break;
            }
        }
        if (alreadyExists) {
            cout << "�̹� �Է��� �ܾ��Դϴ�. �ٽ� �Է��ϼ���." << endl;
            continue;
        }
        clock_t endTime = clock();
        if ((endTime - startTime) / CLOCKS_PER_SEC == 30) {
            cout << "�ð� �ʰ��Դϴ�." << endl;
            break;
        }
        word = word1; 
    }
    return 0;
}