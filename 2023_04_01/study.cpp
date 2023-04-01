#include <iostream>

using std::string;
using std::cout;
using std::cin;
using std::endl;

// control
class RemoteControl {
public:
	virtual void turnOn() = 0;
	virtual void turnOff() = 0;
};

class TV : public RemoteControl {
public:
	void turnOn() {
		cout << "tv ��" << endl;
	}
	void turnOff() {
		cout << "tv ��" << endl;
	}
};

class Radio : public RemoteControl {
public:
	void turnOn() {
		cout << "radio ��" << endl;
	}
	void turnOff() {
		cout << "radio ��" << endl;
	}
};

int main() {


	return 0;
}