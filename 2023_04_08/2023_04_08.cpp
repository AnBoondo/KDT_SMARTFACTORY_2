#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

int main(void) {

    string word = "hello";
    string word1 = "";
    int n = word.size();
    int number_words = 0;
    cout << word << endl;
    cout << "다음 단어를 입력하세요: " << word[n - 1];
    vector<string> words;

    srand(time(NULL));
    clock_t startTime = clock();

    while (1) {

        cin >> word1;
        int a = word1.size();
        cout << endl << "다음 단어를 입력하세요 :" << word1[a - 1];
        bool Exists = false;
        for (int i = 0; i < number_words; i++) {
            if (words[i] == word1) {
                Exists = true;
                break;
            }
        }
        if (Exists) {
            cout << "이미 입력한 단어입니다. 다시 입력하세요." << endl;
            continue;
        }
        words.push_back(word1);
        number_words++;

        clock_t endTime = clock();
        if ((endTime - startTime) / CLOCKS_PER_SEC >= 30) {
            cout << "시간 초과입니다." << endl;
            cout << "총 단어 개수 :" << number_words << endl;
            break;
        }
        word = word1;
    }
    return 0;
}
