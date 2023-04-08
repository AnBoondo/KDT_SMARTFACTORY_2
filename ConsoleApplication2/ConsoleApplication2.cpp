#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class calculator {
protected:
    int num1, num2;
public:
    calculator(int n1, int n2) : num1(n1), num2(n2) {}
    virtual int calculate() = 0;
};

class add : public calculator {
public:
    add(int n1, int n2) : calculator(n1, n2) {}
    virtual int calculate() {
        return num1 + num2;
    }
};

class sub : public calculator {
public:
    sub(int n1, int n2) : calculator(n1, n2) {}
    virtual int calculate() {
        return num1 - num2;
    }
};

class mul : public calculator {
public:
    mul(int n1, int n2) : calculator(n1, n2) {}
    virtual int calculate() {
        return num1 * num2;
    }
};

class Div : public calculator {
public:
    Div(int n1, int n2) : calculator(n1, n2) {}
    virtual int calculate() {
        return num1 / num2;
    }
};

int main() {
    int num1 = 0, num2 = 0;
    char c;
    string input = "AC";
    int result = 0;

    while (true) {
        if (input == "EXIT") break;
        else if (input == "AC") {
            cout << "첫번째 수를 입력하세요: ";
            cin >> num1;
        }
        else if (input == "Y") {
            num1 = result;
        }

        cout << "연산자를 입력하세요(+,-,*,/): ";
        cin >> c;

        cout << "두번째 수를 입력하세요: ";
        cin >> num2;

        calculator* cal = 0;
        switch (c) {
        case '+':
            cal = new add(num1, num2);
            break;
        case '-':
            cal = new sub(num1, num2);
            break;
        case '*':
            cal = new mul(num1, num2);
            break;
        case '/':
            cal = new Div(num1, num2);
            break;
        }
        result = cal->calculate();
        delete cal;

        cout << "결과 :" << result << endl;
        cout << "AC를 입력하면 초기화, Y를 입력하면 계속 계산, EXIT는 종료: ";
        cin >> input;
    }
    return 0;
}