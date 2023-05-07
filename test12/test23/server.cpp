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
#define MAX_CLIENT 3

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

struct SOCKET_INFO {
    SOCKET sck;
    string user;
};

vector<SOCKET_INFO> sck_list;
SOCKET_INFO server_sock;
int client_count = 0;

void server_init();
void add_client();
void send_msg(const char* msg);
void recv_msg(int idx);
void del_client(int idx);

sql::mysql::MySQL_Driver* driver;
sql::Connection* con;
sql::PreparedStatement* pstmt;


void registerUser(string id, string userPassword, string nickname) {
    sql::Statement* stmt;
    try {
        sql::mysql::MySQL_Driver* driver;
        sql::Connection* con;
        sql::PreparedStatement* pstmt;

        const string server = "tcp://127.0.0.1:3306";
        const string username = "root";
        const string db_password = "rlaTl234!@";
       

        driver = sql::mysql::get_mysql_driver_instance();
        con = driver->connect(server, username, db_password);
        con->setSchema("project");

        // db 한글 저장을 위한 셋팅 
        stmt = con->createStatement();
        stmt->execute("set names euckr");
        if (stmt) { delete stmt; stmt = nullptr; }

        pstmt = con->prepareStatement("CREATE TABLE IF NOT EXISTS users (id VARCHAR(50), password VARCHAR(50), nickname VARCHAR(50));");
        pstmt->execute();
        //delete pstmt;

        pstmt = con->prepareStatement("INSERT INTO users (id, password, nickname) VALUES (?, ?, ?);");
        pstmt->setString(1, id);
        pstmt->setString(2, userPassword);
        pstmt->setString(3, nickname);
        pstmt->execute();

        delete pstmt;
        delete con;

        cout << "User registration complete." << endl;
    }
    catch (sql::SQLException& e) {
        cout << "Could not connect to server. Error message: " << e.what() << endl;
        exit(1);
    }
}

void login(string id, string userPassword, string nickname) {
    sql::Statement* stmt;
    try {
        sql::mysql::MySQL_Driver* driver;
        sql::Connection* con;
        sql::PreparedStatement* pstmt;
        sql::ResultSet* result;

        const string server = "tcp://127.0.0.1:3306";
        const string username = "root";
        const string db_password = "rlaTl234!@";


        driver = sql::mysql::get_mysql_driver_instance();
        con = driver->connect(server, username, db_password);
        con->setSchema("project");

        pstmt = con->prepareStatement("SELECT * FROM users WHERE id, password, nickname;");
        result = pstmt->executeQuery();
    }
        catch (sql::SQLException& e) {
            cout << "Could not connect to server. Error message: " << e.what() << endl;
            exit(1);
        }


    }

int main() {
    WSADATA wsa;
    int code = WSAStartup(MAKEWORD(2, 2), &wsa);
    if (!code) {
        server_init();
        std::thread th1[MAX_CLIENT];
        for (int i = 0; i < MAX_CLIENT; i++) {
            th1[i] = std::thread(add_client);
        }
        while (1) {
            string text, msg = "";
            std::getline(cin, text);
            const char* buf = text.c_str();
            msg = server_sock.user + " : " + buf;
            send_msg(msg.c_str());
        }
        for (int i = 0; i < MAX_CLIENT; i++) {
            th1[i].join();
        }
        closesocket(server_sock.sck);
    }
    else {
        cout << "프로그램 종료. (Error code: " << code << ")" << endl;
    }
    WSACleanup();
    return 0;
}

void server_init() {
    server_sock.sck = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    SOCKADDR_IN server_addr = {};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(7777);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    bind(server_sock.sck, (sockaddr*)&server_addr, sizeof(server_addr));
    listen(server_sock.sck, SOMAXCONN);
    server_sock.user = "서버";
    cout << "서버 On" << endl;
}

void add_client() {
    SOCKADDR_IN;
        sockaddr_in addr = {};
    int addrsize = sizeof(addr);
    char buf[MAX_SIZE] = { };
    ZeroMemory(&addr, addrsize);
    SOCKET_INFO new_client = {};
    new_client.sck = accept(server_sock.sck, (sockaddr*)&addr, &addrsize);
    recv(new_client.sck, buf, MAX_SIZE, 0);
    std::stringstream userinfo(buf);
    string id, password, nickname;
    userinfo >> id >> password >> nickname;
    new_client.user = nickname;
    registerUser(id, password, nickname);
    string msg = "[공지] " + new_client.user + " 님이 입장했습니다.";
    cout << msg << endl;
    sck_list.push_back(new_client);
    std::thread th(recv_msg, client_count);
    client_count++;
    cout << "[공지] 현재 접속자 수: " << client_count << "명" << endl;
    send_msg(msg.c_str());
    th.join();
}

void loginUser() {
    SOCKADDR_IN;
    sockaddr_in addr = {};
    int addrsize = sizeof(addr);
    char buf[MAX_SIZE] = { };
    ZeroMemory(&addr, addrsize);
    SOCKET_INFO new_client = {};
    new_client.sck = accept(server_sock.sck, (sockaddr*)&addr, &addrsize);
    recv(new_client.sck, buf, MAX_SIZE, 0);
    std::stringstream userinfo(buf);
    string id, password, nickname;
    userinfo >> id >> password >> nickname;
    new_client.user = nickname;
    login(id, password, nickname);
    string msg = "[공지] " + new_client.user + " 님이 입장했습니다.";
    cout << msg << endl;
    sck_list.push_back(new_client);
    std::thread th(recv_msg, client_count);
    client_count++;
    cout << "[공지] 현재 접속자 수: " << client_count << "명" << endl;
    send_msg(msg.c_str());
    th.join();
}

void send_msg(const char* msg) {
    for (int i = 0; i < client_count; i++) {
        send(sck_list[i].sck, msg, MAX_SIZE, 0);
    }
}

void recv_msg(int idx) {
    char buf[MAX_SIZE] = { };
    string msg = "";
    while (1) {
        ZeroMemory(&buf, MAX_SIZE);
        if (recv(sck_list[idx].sck, buf, MAX_SIZE, 0) > 0) {
            msg = sck_list[idx].user + " : " + buf;
            cout << msg << endl;
            send_msg(msg.c_str());
        }
        else {
            msg = "[공지] " + sck_list[idx].user + " 님이 퇴장했습니다.";
            cout << msg << endl;
            send_msg(msg.c_str());
            del_client(idx);
            return;
        }
    }
}

void del_client(int idx) {
    closesocket(sck_list[idx].sck);
    client_count--;
}