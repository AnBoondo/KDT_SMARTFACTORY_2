#include<iostream>
using namespace std;
class User {
private:
	char* name, * address, * phone, sex;
	int age;
	User* next;
public:
	User();
	~User();
	void SetName(char* name) { strcpy(this->name, name); };
	void SetAddr(char* address) { strcpy(this->address, address); };
	void SetPhone(char* phone) { strcpy(this->phone, phone); };
	void SetSex(char sex) { this->sex = sex; };
	void SetAge(int age) { this->age = age; };
	void SetNext(User* p) { next = p; };

	char* GetName() { return name; };
	char* GetAddr() { return address; };
	char* GetPhone() { return phone; };
	char GetSex() { return sex; };
	int GetAge() { return age; };
	User* GetNext() { return next; };
};
User::User()
{
	name = new char[20];
	address = new char[50];
	phone = new char[20];
	sex = NULL;
	age = 0;
}
User::~User()
{
	delete[]name;
	delete[]address;
	delete[]phone;
}
class MyList {
private:
	User* p;
	User* Current_data;
public:
	MyList();
	~MyList();
	void Add(User* pData);
	void Deletion(int age);
	void Search(int age);
	void Print();
	void Sort();
};
MyList::MyList()
{
	p = new User;
	p->SetNext(NULL);
	Current_data = p;
}
MyList::~MyList()
{
	delete[]p;
}
void MyList::Add(User* pData)
{
	char address[50];
	cout << "ADDRESS : ";
	cin >> address;
	pData->SetAddr(address);

	char name[20];
	cout << "NAME : ";
	cin >> name;
	pData->SetName(name);
	char phone[20];
	cout << "PHONE : ";
	cin >> phone;