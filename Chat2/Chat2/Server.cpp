
#pragma comment(lib, "ws2_32.lib") // 명시적으로 라이브러리를 호출하는 방법 중 하나.

#include <WinSock2.h> //winsock 헤더 사용중
#include <string>
#include <iostream>
#include <thread>
#include <sstream>
#include <vector>
#include "server.h"


#define MAX_SIZE 1024
#define MAX_CLIENT 4 // 최대 3명

using std::cout;
using std::cin;
using std::endl;
using std::string;

bool is_duplicate;
bool is_login;


struct SOCKET_INFO {
    SOCKET sck; // ctrl + 클릭 하면 헤더 속 SOCKET 코드를 찾아갈 수 있다, socket은 unsigned int pointer를 갖고 있구나 하고 예측할 수 있다.
    string user; // user : 사람의 이름
};

std::vector<SOCKET_INFO> sck_list; // 서버에 연결된 client 저장할 변수
SOCKET_INFO server_sock; // 서버 소켓의 정보를 저장할 변수
int client_count = 0;  //현재 접속하고 있는 클라이언트의 수 카운트.
string nickname;

void server_init(); // 서버용 소켓을 만드는 함수. ~ listen()
void add_client(); // accept 함수 실행되고 있을 예fh
void add_client_retry(SOCKET_INFO new_client, char* buf);
void send_msg(const char* msg); // send () 실행
void recv_msg(int idx); // recv() 실행
void del_client(int idx); // 클라이언트와의 연결을 끊을 때
void sql_signup(string id, string nickname, string password);
void sql_is_id_duplicate(string new_id);
void check_id_duplicate(string new_id);
void sql_connect();
void sql_disconnect();
void sql_login(string id, string pw);
void sql_message_input(string sender, string receiver, string msg);
void print_chat_history(string nickname);

// MySQL Connector/C++ 초기화
sql::mysql::MySQL_Driver* driver; // 추후 해제하지 않아도 Connector/C++가 자동으로 해제해 줌
sql::Connection* con;
sql::Statement* stmt;
sql::PreparedStatement* pstmt;
sql::ResultSet* result;

int main() {
    WSADATA wsa;
    int code = WSAStartup(MAKEWORD(2, 2), &wsa); 
    if (!code) {
        server_init(); // 서버측 소켓 활성화

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
        cout << "프로그램 종료. (Error code : " << code << ")"; 
    }

    WSACleanup();


    return 0;
}

void server_init() {
    server_sock.sck = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);  
    SOCKADDR_IN server_addr = {};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(2304); // ~~~~:7777
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY); //  127.0.0.1: ~~~~

    bind(server_sock.sck, (sockaddr*)&server_addr, sizeof(server_addr));
    listen(server_sock.sck, SOMAXCONN);
    server_sock.user = "서버";
    cout << "서버 On" << endl;
}

void add_client() {
    cout << "add_client" << endl;
    SOCKADDR_IN addr = {};
    int addrsize = sizeof(addr);
    char buf[MAX_SIZE] = { }; // 메시지 최대 길이 설정

    ZeroMemory(&addr, addrsize); //  addr 메모리를 0x00으로 초기화/addrsize = sizeof(addr), 

    SOCKET_INFO new_client = {};
    new_client.sck = accept(server_sock.sck, (sockaddr*)&addr, &addrsize);
            add_client_retry(new_client, buf);

}
void add_client_retry(SOCKET_INFO new_client, char* buf) {
    recv(new_client.sck, buf, MAX_SIZE, 0); 
    std::stringstream userinfo(buf);
    string id, pw;
    userinfo >> new_client.user >> id >> pw;

    if (new_client.user == "*login*") {
        sql_login(id, pw);
        if (is_login) {
            send(new_client.sck, "Success : 로그인을 성공했습니다.", MAX_SIZE, 0);
            new_client.user = nickname; 
            string msg = "[공지] " + new_client.user + " 님이 입장했습니다.";
            cout << msg << endl; 
            stmt = con->createStatement();
            stmt->execute("set names euckr");
            if (stmt) { delete stmt; stmt = nullptr; }
            print_chat_history(new_client.user);

            sck_list.push_back(new_client); 

            std::thread th(recv_msg, client_count);

            client_count++; 
            cout << "[공지] 현재 접속자 수 : " << client_count << "명" << endl;
            send_msg(msg.c_str());
            th.join(); 
        }
        else {
            send(new_client.sck, "Fail : 아이디 혹은 패스워드가 다릅니다.", MAX_SIZE, 0);
            cout << "Fail : 아이디 혹은 패스워드가 다릅니다." << endl;
            add_client_retry(new_client, buf);
        }
    }
    else {
        is_duplicate = false;
        sql_is_id_duplicate(id);
        if (!is_duplicate) {

            sql_signup(id, new_client.user, pw);
            send(new_client.sck, "Success : 회원가입에 성공했습니다.", MAX_SIZE, 0);
            string msg = "[공지] " + new_client.user + " 님이 입장했습니다.";
            cout << msg << endl;
            sck_list.push_back(new_client); 
            std::thread th(recv_msg, client_count); 
            client_count++; 
            cout << "[공지] 현재 접속자 수 : " << client_count << "명" << endl;
            send_msg(msg.c_str());
            th.join();
        }
        else {
            cout << "duplicated" << endl;
            send(new_client.sck, "Fail : 중복된 아이디가 있습니다.", MAX_SIZE, 0);
            add_client_retry(new_client, buf);
        }
    }
}

void send_msg(const char* msg) {
    for (int i = 0; i < client_count; i++) {
        send(sck_list[i].sck, msg, MAX_SIZE, 0);
    }

}
void send_msg(SOCKET sck, string msg) {
}

void recv_msg(int idx) {
    char buf[MAX_SIZE] = { };
    string msg = "";

    while (1) {
        ZeroMemory(&buf, MAX_SIZE); // buf 0으로 초기화
        if (recv(sck_list[idx].sck, buf, MAX_SIZE, 0) > 0) {
            std::stringstream sss(buf);
            string this_id, receiver, message, temp;
            sss >> this_id;
            sss >> message;
            if (message == "to:" or message == "TO:" or message == "to" or message == "TO") {
                sss >> receiver;
                getline(sss, message);
            }
            else {
                receiver = "*";
                std::stringstream ssss(buf);
                ssss >> this_id;
                getline(ssss, message);
            }
            cout << this_id << " " << receiver << " " << message << " " << endl;
            msg = sck_list[idx].user + " : " + message;
            cout << msg << endl;
            send_msg(msg.c_str());
            sql_message_input(this_id, receiver, message);
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
void sql_signup(string id, string nickname, string password) {
   sql_connect();
    con->setSchema("project_chat"); 
    stmt = con->createStatement();
    stmt->execute("set names euckr");
    if (stmt) { delete stmt; stmt = nullptr; }
    pstmt = con->prepareStatement("INSERT INTO user(id, nickname, password) VALUES(?,?,?)"); // INSERT
    pstmt->setString(1, id);
    pstmt->setString(2, nickname);
    pstmt->setString(3, password);
    pstmt->execute(); // 쿼리 실행
    sql_disconnect();
}
void sql_is_id_duplicate(string new_id) {
    sql_connect();
    stmt = con->createStatement();
    result = stmt->executeQuery("SELECT * FROM user WHERE id = '" + new_id + "'");
    delete stmt;
    while (result->next()) {
        cout << "중복검사에 걸림" << endl;
        is_duplicate = true;
        sql_disconnect();
    }

}

void sql_connect() {
    try {
        driver = sql::mysql::get_mysql_driver_instance();
        con = driver->connect(server, username, dbpassword); // MySQL 데이터베이스 연결 객체
    }
    catch (sql::SQLException& e) {
        cout << "Could not connect to server. Error message: " << e.what() << endl;
        exit(1);
    }
    con->setSchema("project_chat");
    stmt = con->createStatement();
    stmt->execute("set names euckr");
    if (stmt) { delete stmt; stmt = nullptr; }
}
void sql_disconnect() {
    if (pstmt != nullptr) {
        delete pstmt;
        pstmt = nullptr;
    }
    if (con != nullptr) {
        delete con;
        con = nullptr;
    }
}

void sql_login(string id, string pw) {
    sql_connect();
    is_login = false;
    pstmt = con->prepareStatement("SELECT * FROM user WHERE id = ? AND password = ?");
    pstmt->setString(1, id);
    pstmt->setString(2, pw);
    result = pstmt->executeQuery();

    while (result->next()) {
        cout << "로그인 성공!" << endl;
        pstmt = con->prepareStatement("SELECT nickname FROM user WHERE id = ? AND password = ?");
        pstmt->setString(1, id);
        pstmt->setString(2, pw);
        result = pstmt->executeQuery();
        while (result->next()) {
            nickname = result->getString(1);
            cout << nickname << endl;
            is_login = true;
        }
    }
    sql_disconnect();
}

void sql_message_input(string sender, string receiver, string message) {
    sql_connect();
    con->setSchema("project_chat");
    stmt = con->createStatement();
    stmt->execute("set names euckr");
   if (stmt) { delete stmt; stmt = nullptr; }
    pstmt = con->prepareStatement("INSERT INTO message(sender, receiver, message) VALUES(?,?,?);");

    pstmt->setString(1, sender);
    pstmt->setString(2, receiver);
    pstmt->setString(3, message);

    pstmt->execute(); 
    sql_disconnect();
}

void print_chat_history(string nickname) {
    try {
        driver = sql::mysql::get_mysql_driver_instance();
        con = driver->connect(server, username, dbpassword);
        con->setSchema("project_chat");
        sql::PreparedStatement* pstmt = con->prepareStatement("SELECT * FROM message");
        sql::ResultSet* res = pstmt->executeQuery();
        while (res->next()) {
            string sender = res->getString("sender");
            string message = res->getString("message");
            string time = res->getString("time");
            cout << "[" << time << "] " << sender << ": " << message << endl;
        }
        delete res;
        delete pstmt;
    }
    catch (sql::SQLException& e) {
        cout << "SQL Exception: " << e.what() << endl;
    }
    stmt = con->createStatement();
    stmt->execute("set names euckr");
    if (stmt) { delete stmt; stmt = nullptr; }
}