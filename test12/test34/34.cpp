#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h> // Winsock ������� include
#include <WS2tcpip.h>
#include <string>
#include <sstream>
#include <iostream>
#include <thread>
#include <vector>
#include <mysql/jdbc.h>
#define MAX_SIZE 1024
using namespace std;

SOCKET client_sock;
string my_nick;
string id, password1;


struct User {
    string id;
    string password1;
};

vector<User> userDatabase;

bool isUserExist(const string& id) {
    for (const auto& user : userDatabase) {
        if (user.id == id) {
            return true;
        }
    }
    return false;
}

bool isValidCredentials(const string& id, const string& password) {
    for (const auto& user : userDatabase) {
        if (user.id == id && user.password1 == password) {
            return true;
        }
    }
    return false;
}

void registerUser() {
    string id, password1;

    cout << "���̵� �Է����ּ���: ";
    cin >> id;

    if (isUserExist(id)) {
        cout << "�̹� �����ϴ� ���̵��Դϴ�." << endl;
        return;
    }

    cout << "��й�ȣ�� �Է����ּ���: ";
    cin >> password1;

    cout << "����� �г��� �Է� >> ";
    cin >> my_nick;

    cout << "ȸ�������� �Ϸ�Ǿ����ϴ�." << endl;

    // MySQL Connector/C++ �ʱ�ȭ
    sql::mysql::MySQL_Driver* driver;
    sql::Connection* con;
    sql::PreparedStatement* pstmt;

    // MySQL ����
    try {
        const string server = "tcp://127.0.0.1:3306"; // �����ͺ��̽� �ּ�
        const string username = "root"; // �����ͺ��̽� �����
        const string password = "rlaTl234!@"; // �����ͺ��̽� ���� ��й�ȣ

        driver = sql::mysql::get_mysql_driver_instance();
        con = driver->connect(server, username, password); // MySQL �����ͺ��̽� ���� ��ü

        // �����ͺ��̽� ����
        con->setSchema("project");

        // ȸ�� ������ ������ ���̺� ����
        pstmt = con->prepareStatement("CREATE TABLE IF NOT EXISTS users (id VARCHAR(50), password VARCHAR(50));");
        pstmt->execute();
        delete pstmt;

        // ȸ�� ������ ���̺� ����
        pstmt = con->prepareStatement("INSERT INTO users (id, password) VALUES (?, ?);");
        pstmt->setString(1, id);
        pstmt->setString(2, password1);
        pstmt->execute();
        delete pstmt;

        // MySQL Connector/C++ ����
        delete con;
        cout << "User registration complete." << endl;
    }
    catch (sql::SQLException& e) {
        cout << "Could not connect to server. Error message: " << e.what() << endl;
        exit(1);
    }
}

int chat_recv() {
    char buf[MAX_SIZE] = {};
    string msg;
    while (1) {
        ZeroMemory(&buf, MAX_SIZE);
        if (recv(client_sock, buf, MAX_SIZE, 0) > 0) {
            msg = buf;
            // �г��� : �޽���
            std::stringstream ss(msg);
            string user;
            ss >> user;
            if (user != my_nick) cout << buf << endl;
        }
        else {
            cout << "Server Off" << endl;
            return -1;
        }
    }
}

void login() {
    string id, password1;

    cout << "���̵� �Է����ּ���: ";
    cin >> id;

    cout << "��й�ȣ�� �Է����ּ���: ";
    cin >> password1;

    if (isValidCredentials(id, password1)) {
        cout << "�α��� ����!" << endl;
        // �α��� ���� �� ä�� ���α׷����� �̵��ϴ� ������ �߰��ϼ���.
        // ���� ���, chatProgram() �Լ��� ȣ���Ͽ� ä�� ���α׷��� ������ �� �ֽ��ϴ�.
    }
    else {
        cout << "���̵� �Ǵ� ��й�ȣ�� �߸��Ǿ����ϴ�." << endl;
    }
}

int main() {
    WSADATA wsa;
    int code = WSAStartup(MAKEWORD(2, 2), &wsa);
    if (!code) {
        cout << "�̹� ���̵� �����ø� 1, ȸ�������� ���Ͻø� 2���� �����ּ���.";
        int choice;
        cin >> choice;
        if (choice == 1) {
            cout << "�α����� ���ּ���." << endl;
            login();
        }
        else if (choice == 2) {
            cout << "ȸ������ �������� �̵��մϴ�." << endl;
            registerUser();
        }
        else {
            cout << "�߸��� �����Դϴ�." << endl;
            return 0;
        }

        client_sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
        SOCKADDR_IN client_addr = {};
        client_addr.sin_family = AF_INET;
        client_addr.sin_port = htons(7777);
        InetPton(AF_INET, TEXT("127.0.0.1"), &client_addr.sin_addr);
        while (1) {
            if (!connect(client_sock, (SOCKADDR*)&client_addr, sizeof(client_addr))) {
                cout << "Server Connect" << endl;
                send(client_sock, (my_nick + ' ' + id + ' ' + password1).c_str(), (my_nick + ' ' + id + ' ' + password1).length(), 0);
                break;
            }
            cout << "Connecting..." << endl;
        }
        std::thread th2(chat_recv);
        while (1) {
            string text;
            std::getline(cin, text);
            const char* buffer = text.c_str();
            send(client_sock, buffer, strlen(buffer), 0);
        }
        th2.join();
        closesocket(client_sock);
    }
    WSACleanup();
    return 0;
}