#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h> // Winsock 헤더파일 include
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

    cout << "아이디를 입력해주세요: ";
    cin >> id;

    if (isUserExist(id)) {
        cout << "이미 존재하는 아이디입니다." << endl;
        return;
    }

    cout << "비밀번호를 입력해주세요: ";
    cin >> password1;

    cout << "사용할 닉네임 입력 >> ";
    cin >> my_nick;

    cout << "회원가입이 완료되었습니다." << endl;

    // MySQL Connector/C++ 초기화
    sql::mysql::MySQL_Driver* driver;
    sql::Connection* con;
    sql::PreparedStatement* pstmt;

    // MySQL 연결
    try {
        const string server = "tcp://127.0.0.1:3306"; // 데이터베이스 주소
        const string username = "root"; // 데이터베이스 사용자
        const string password = "rlaTl234!@"; // 데이터베이스 접속 비밀번호

        driver = sql::mysql::get_mysql_driver_instance();
        con = driver->connect(server, username, password); // MySQL 데이터베이스 연결 객체

        // 데이터베이스 선택
        con->setSchema("project");

        // 회원 정보를 저장할 테이블 생성
        pstmt = con->prepareStatement("CREATE TABLE IF NOT EXISTS users (id VARCHAR(50), password VARCHAR(50));");
        pstmt->execute();
        delete pstmt;

        // 회원 정보를 테이블에 저장
        pstmt = con->prepareStatement("INSERT INTO users (id, password) VALUES (?, ?);");
        pstmt->setString(1, id);
        pstmt->setString(2, password1);
        pstmt->execute();
        delete pstmt;

        // MySQL Connector/C++ 정리
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
            // 닉네임 : 메시지
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

    cout << "아이디를 입력해주세요: ";
    cin >> id;

    cout << "비밀번호를 입력해주세요: ";
    cin >> password1;

    if (isValidCredentials(id, password1)) {
        cout << "로그인 성공!" << endl;
        // 로그인 성공 후 채팅 프로그램으로 이동하는 로직을 추가하세요.
        // 예를 들어, chatProgram() 함수를 호출하여 채팅 프로그램을 실행할 수 있습니다.
    }
    else {
        cout << "아이디 또는 비밀번호가 잘못되었습니다." << endl;
    }
}

int main() {
    WSADATA wsa;
    int code = WSAStartup(MAKEWORD(2, 2), &wsa);
    if (!code) {
        cout << "이미 아이디가 있으시면 1, 회원가입을 원하시면 2번을 눌러주세요.";
        int choice;
        cin >> choice;
        if (choice == 1) {
            cout << "로그인을 해주세요." << endl;
            login();
        }
        else if (choice == 2) {
            cout << "회원가입 페이지로 이동합니다." << endl;
            registerUser();
        }
        else {
            cout << "잘못된 선택입니다." << endl;
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