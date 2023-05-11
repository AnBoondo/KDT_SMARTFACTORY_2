#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h> 
#include <string>
#include <iostream>
#include <thread>
#include <sstream>
#include <vector>
#include "server.h"


#define MAX_SIZE 1024
#define MAX_CLIENT 10

using std::cout;
using std::cin;
using std::endl;
using std::string;

bool is_duplicate;
bool is_login;


struct SOCKET_INFO {
    SOCKET sck;
    string user;
    string id;
};

std::vector<SOCKET_INFO> sck_list; 
SOCKET_INFO server_sock; 
int client_count = 0;  
string nickname;

void server_init();
void add_client();
void add_client_authentication(SOCKET_INFO new_client, char* buf);
void send_msg(const char* msg);
void send_history(string user_id, SOCKET_INFO new_client);
void recv_msg(int idx);
void del_client(int idx);
void sql_signup(string id, string nickname, string password);
void sql_check_if_id_exists(string new_id);
void sql_connect();
void sql_disconnect();
string sql_login(string id, string pw);
void sql_message_input(string sender, string receiver, string msg);

sql::mysql::MySQL_Driver* driver; 
sql::Connection* con;
sql::Statement* stmt;
sql::PreparedStatement* pstmt;
sql::ResultSet* result;

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
            string is_command, command;
            std::getline(cin, text);
            const char* buf = text.c_str();
            std::stringstream serverstream(buf);
            serverstream >> is_command;
            if (is_command == "admin") {
                serverstream >> command;
                if (command == "ban") {
                    string ban_who;
                    serverstream >> ban_who;
                    for (int i = 0; i < MAX_CLIENT; i++) {
                        if (sck_list[i].id == ban_who) {
                            send(sck_list[i].sck, ("서버 :" +sck_list[i].user + " 너 밴").c_str(), MAX_SIZE, 0);
                            del_client(i);
                        }
                    }
                }
                else if (command == "whisper") {
                    string whisper_who;
                    serverstream >> whisper_who;
                    for (int i = 0; i < MAX_CLIENT; i++) {
                        if (sck_list[i].id == whisper_who) {
                            string message;
                            std::getline(serverstream, message);
                            message.erase(message.begin());
                            send(sck_list[i].sck, ("서버 :" + message).c_str(), MAX_SIZE, 0);
              
                        }
                    }
                    }
                else if (command == "decrease") {}
            }
            else{ msg = server_sock.user + " : " + buf;
                send_msg(msg.c_str());}
               

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
    0;
}

void server_init() {
    server_sock.sck = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);  
    SOCKADDR_IN server_addr = {};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(2304); 
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY); 
    bind(server_sock.sck, (sockaddr*)&server_addr, sizeof(server_addr));
    listen(server_sock.sck, SOMAXCONN);
    server_sock.user = "서버";
    cout << "서버 On" << endl;
}

void add_client() {
    SOCKADDR_IN addr = {};
    int addrsize = sizeof(addr);
    char buf[MAX_SIZE] = { };

    ZeroMemory(&addr, addrsize);
    SOCKET_INFO new_client = {};
    new_client.sck = accept(server_sock.sck, (sockaddr*)&addr, &addrsize);

    while (1) {
        add_client_authentication(new_client, buf);
        if (is_login || !is_duplicate) {
            break;
        }
        closesocket(new_client.sck);
        new_client.sck = accept(server_sock.sck, (sockaddr*)&addr, &addrsize);
    }
}

void add_client_authentication(SOCKET_INFO new_client, char* buf) {
    recv(new_client.sck, buf, MAX_SIZE, 0);
    std::stringstream userinfo(buf);
    string id, pw, temp;
    userinfo >> new_client.user >> id >> pw;
    new_client.id = id;
    if (new_client.user == "*login*") {
        temp = sql_login(id, pw);
        if (is_login) {
            nickname = temp;
            send(new_client.sck, ("Success " + nickname + " 로그인을 성공했습니다.").c_str(), MAX_SIZE, 0);
            send_history(id, new_client);
            new_client.user = nickname;
            string msg = "[공지] " + new_client.user + " 님이 입장했습니다.";
            cout << msg << endl;
            sck_list.emplace_back(new_client);
            std::thread th(recv_msg, client_count);
            client_count++;
            cout << "[공지] 현재 접속자 수 : " << client_count << "명" << endl;
            send_msg(msg.c_str());
            th.join();

        }
        else {
            send(new_client.sck, "Fail : 아이디 혹은 패스워드가 다릅니다.", MAX_SIZE, 0);
            cout << "Fail : 아이디 혹은 패스워드가 다릅니다." << endl;
        }
    }
    else {
        is_duplicate = false;
        sql_check_if_id_exists(id);
        if (!is_duplicate) {
            sql_signup(id, new_client.user, pw);
            send(new_client.sck, "Success : 회원가입에 성공했습니다.", MAX_SIZE, 0);
            string msg = "[공지] " + new_client.user + " 님이 입장했습니다.";
            cout << msg << endl; 

            sck_list.emplace_back(new_client);
            std::thread th(recv_msg, client_count); 
            client_count++; 
            cout << "[공지] 현재 접속자 수 : " << client_count << "명" << endl;
            send_msg(msg.c_str());
            th.join(); 
        }
        else {
            cout << "duplicated" << endl;
            send(new_client.sck, "Fail : 중복된 아이디가 있습니다.", MAX_SIZE, 0);
            add_client_authentication(new_client, buf);
        }
    }
}

void send_msg(const char* msg) {
    for (const auto& client : sck_list) {
        send(client.sck, msg, MAX_SIZE, 0);
    }
}

void recv_msg(int idx) {
    char buf[MAX_SIZE] = { };
    string msg = "";
    while (1) {
        ZeroMemory(&buf, MAX_SIZE);
        if (recv(sck_list[idx].sck, buf, MAX_SIZE, 0) > 0) {
            std::stringstream sss(buf);
            string this_id, is_whisper, receiver, message;
            sss >> this_id;
            sss >> is_whisper;
            sss >> receiver;
            std::getline(sss, message);
            message.erase(message.begin());
            msg = sck_list[idx].user + " : " + message;
            cout << msg << endl;

            if (is_whisper == "Y") {
                for (int i = 0; i < MAX_CLIENT; i++) {
                    if (sck_list[i].id == receiver) {
                        send(sck_list[i].sck, msg.c_str(), MAX_SIZE, 0);
                        break;
                    }
                }
            }
            else {
                send_msg(msg.c_str());
            }

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


void send_history(string user_id, SOCKET_INFO new_client) {
    try {
        driver = sql::mysql::get_mysql_driver_instance();
        con = driver->connect(server, username, dbpassword);
        con->setSchema("project_chat");
        stmt = con->createStatement();
        stmt->execute("set names euckr");
        sql::PreparedStatement* pstmt = con->prepareStatement("SELECT * FROM message WHERE (sender = ? OR receiver = ?) OR (receiver = '*')");
        pstmt->setString(1, user_id);
        pstmt->setString(2, user_id);
        sql::ResultSet* res = pstmt->executeQuery();
        while (res->next()) {
            string message = res->getString("message");
            string time = res->getString("time");
            string sender = res->getString("sender");
            string green = "\x1B[32m"; 
            string yellow = "\x1B[33m"; 
            string blue = "\x1B[34m"; 
            string magenta = "\x1B[35m"; 
            string cyan = "\x1B[36m";
            string bold = "\x1B[1m";
            string reset = "\x1B[0m"; 
            string output = "[" + yellow + time + reset + "] " +
                "[" + green + sender + reset + "] " +
                bold + reset + ": " + message;
            send(new_client.sck, output.c_str(), MAX_SIZE, 0);
        }
        delete res;
        delete pstmt;
    }
    catch (sql::SQLException& e) {
        cout << "SQL Exception: " << e.what() << endl;
    }
    if (stmt) { delete stmt; stmt = nullptr; }
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
    pstmt = con->prepareStatement("INSERT INTO user(id, nickname, password) VALUES(?,?,?)"); 
    pstmt->setString(1, id);
    pstmt->setString(2, nickname);
    pstmt->setString(3, password);
    pstmt->execute(); 
    sql_disconnect();

}
void sql_check_if_id_exists(string new_id) {
    sql_connect();
    stmt = con->createStatement();
    result = stmt->executeQuery("SELECT * FROM user WHERE id = '" + new_id + "'");
    delete stmt;
    while (result->next()) {
        cout << "중복검사에 걸림" << endl;
        is_duplicate = true;
    }
    sql_disconnect();
}
void sql_connect() {
    try {
        driver = sql::mysql::get_mysql_driver_instance();
        con = driver->connect(server, username, dbpassword); 
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

string sql_login(string id, string pw) {
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
            is_login = true;
            return nickname;
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