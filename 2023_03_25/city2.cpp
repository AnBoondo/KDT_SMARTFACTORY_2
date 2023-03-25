#include <iostream>

using namespace std;

string size = "";
string arr[5];

void userInput()
{
    cout << "나라이름" << endl;
    for (int i = 0; i < 5; i++)
    {
        cin >> arr[i];
    }
}

void print()
{
    cout << "나라이름:" << endl;
    for (int i = 0; i < 5; i++)
        cout << arr[i] << " ";
    cout << endl;
}

int main()
{
    userInput();
    print();
    return 0;
}