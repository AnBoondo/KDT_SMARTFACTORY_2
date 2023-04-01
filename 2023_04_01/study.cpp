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
		cout << "tv дт" << endl;
	}
	void turnOff() {
		cout << "tv ╡Ш" << endl;
	}
};

class Radio : public RemoteControl {
public:
	void turnOn() {
		cout << "radio дт" << endl;
	}
	void turnOff() {
		cout << "radio ╡Ш" << endl;
	}
};

int main() {


	return 0;
}