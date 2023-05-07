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
string nickname;
string id, password;

const string server = "tcp://127.0.0.1:3306";
const string username = "root";
const string db_password = "rlaTl234!@";

bool isServerConnected = false; // ���� ���� ���¸� ��Ÿ���� ����

int chat_recv() {
    char buf[MAX_SIZE] = {};
    string msg;
    while (isServerConnected) {
        ZeroMemory(&buf, MAX_SIZE);
        if (recv(client_sock, buf, MAX_SIZE, 0) > 0) {
            msg = buf;
            std::stringstream ss(msg);
            string user;
            ss >> user;
            if (user != nickname)
                cout << buf << endl;
        }
        else {
            cout << "�������� ������ ���������ϴ�." << endl;
            break;
        }
    }

    return 0;
}

struct User {
    string id;
    string password;
};

vector<User> userDatabase;  // ȸ�� ������ ������ �����ͺ��̽�

bool isUserExist(const string& id) {
    sql::mysql::MySQL_Driver* driver;
    sql::Connection* con;
    sql::PreparedStatement* pstmt;
    sql::ResultSet* result;

    try {
        driver = sql::mysql::get_mysql_driver_instance();
        con = driver->connect(server, username, db_password);
        con->setSchema("project");

        pstmt = con->prepareStatement("SELECT * FROM users WHERE id = ?");
        pstmt->setString(1, id);
        result = pstmt->executeQuery();

        bool exists = result->next();

        delete result;
        delete pstmt;
        delete con;

        return exists;
    }
    catch (sql::SQLException& e) {
        return false;
    }
}

void registerUser() {
    cout << "���̵� �Է����ּ���: ";
    cin >> id;

    while (isUserExist(id)) {
        cout << "�̹� �����ϴ� ���̵��Դϴ�. �ٸ� ���̵� �Է����ּ���." << endl;
        cout << "���̵� �Է����ּ���: ";
        cin >> id;
    }

    cout << "��й�ȣ�� �Է����ּ���: ";
    cin >> password;

    cout << "����� �г��� �Է�: ";
    cin >> nickname;

    cout << "ȸ�������� �Ϸ�Ǿ����ϴ�." << endl;
    Sleep(3000);
}

bool isValidCredentials(const string& id, const string& password) {
    sql::mysql::MySQL_Driver* driver;
    sql::Connection* con;
    sql::PreparedStatement* pstmt;
    sql::ResultSet* result;

    try {
        driver = sql::mysql::get_mysql_driver_instance();
        con = driver->connect(server, username, db_password);
        con->setSchema("project");

        pstmt = con->prepareStatement("SELECT * FROM users WHERE id = ? AND password = ?");
        pstmt->setString(1, id);
        pstmt->setString(2, password);
        result = pstmt->executeQuery();

        bool isValid = result->next();

        delete result;
        delete pstmt;
        delete con;

        return isValid;
    }
    catch (sql::SQLException& e) {
        return false;
    }
}

void login() {
    const int maxAttempts = 3;
    int attempt = 0;

    while (attempt < maxAttempts) {
        cout << "���̵� �Է����ּ���: ";
        cin >> id;

        cout << "��й�ȣ�� �Է����ּ���: ";
        cin >> password;

        if (isValidCredentials(id, password)) {
            cout << "�α��� ����!" << endl;
            nickname = id;

            // Connect to the server
            client_sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
            SOCKADDR_IN client_addr = {};
            client_addr.sin_family = AF_INET;
            client_addr.sin_port = htons(7777);
            InetPton(AF_INET, TEXT("127.0.0.1"), &client_addr.sin_addr);

            while (1) {
                if (!connect(client_sock, (SOCKADDR*)&client_addr, sizeof(client_addr))) {
                    cout << "Server Connect" << endl;
                    break;
                }
                cout << "Connecting..." << endl;
            }

            isServerConnected = true;
            thread th2(chat_recv);

            while (isServerConnected) {
                string text;
                std::getline(cin, text);
                const char* buffer = text.c_str();
                send(client_sock, buffer, strlen(buffer), 0);
            }

            isServerConnected = false;
            th2.join();

            closesocket(client_sock);
            return; // �α��� ���� ��, �Լ� ����
        }
        else {
            cout << "���̵� �Ǵ� ��й�ȣ�� �߸��Ǿ����ϴ�." << endl;
            attempt++;
        }
    }

    cout << "�α��� �õ� Ƚ�� �ʰ�. ���α׷��� �����մϴ�." << endl;
    exit(0); // �α���
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
            login();
        }
        else {
            cout << "�߸��� �����Դϴ�." << endl;
            return 0;
        }

        while (1) {
            client_sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
            SOCKADDR_IN client_addr = {};
            client_addr.sin_family = AF_INET;
            client_addr.sin_port = htons(7777);
            InetPton(AF_INET, TEXT("127.0.0.1"), &client_addr.sin_addr);
            while (1) {
                if (!connect(client_sock, (SOCKADDR*)&client_addr, sizeof(client_addr))) {
                    cout << "Server Connect" << endl;
                    send(client_sock, (id + ' ' + password + ' ' + nickname).c_str(), (id + ' ' + password + ' ' + nickname).length(), 0);
                    break;
                }
                cout << "Connecting..." << endl;
            }

            isServerConnected = true;
            thread th2(chat_recv);

            while (isServerConnected) {
                string text;
                std::getline(cin, text);
                const char* buffer = text.c_str();
                send(client_sock, buffer, strlen(buffer), 0);
            }

            isServerConnected = false;
            th2.join();

            closesocket(client_sock);
        }
    }

    WSACleanup();
    return 0;
}