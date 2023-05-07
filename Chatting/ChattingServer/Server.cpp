#pragma comment(lib, "ws2_32.lib") // 명시적으로 라이브러리를 호출하는 방법 중에 하나

#include <WinSock2.h>
#include <string>
#include <iostream>
#include <thread>
#include <vector>

#define MAX_SIZE 1024
#define MAX_CLIENT 3

using std::cout;
using std::cin;
using std::endl;
using std::string;

struct SOCKET_INFO {  // 구조체 정의
    SOCKET sck; // ctrl + 클릭,  usigned int pointer 형
    string user; // user : 사람의 이름
};

std::vector<SOCKET_INFO> sck_list; // 서버에 연결된 clients 정장할 변수
SOCKET_INFO server_sock; // 서브소켓의 정보를 저장할 변수
int client_count = 0; // 현재 접속된 클라이언트 수 카운트 용도

void server_init(); // 서버용 소켓을 만드는 함수 ~ listen ()
void add_client(); // accept 함수 실행되고 있을 예정
void send_msg(const char* msg); // send() 실행
void recv_msg(int idx); // recv() 실행
void del_client(int idx); // 클라이언트와의 연결을 끊을 때

int main() {
    WSADATA wsa;

    // Winsock를 초기화하는 함수. MAKEWORD(2, 2)는 Winsock의 2.2 버전을 사용하겠다는 의미.
    // 실행에 성공하면 0을, 실패하면 그 이외의 값을 반환.
    // 0을 반환했다는 것은 Winsock을 사용할 준비가 되었다는 의미.
    int code = WSAStartup(MAKEWORD(2, 2), &wsa);  // 성공하면 0, 실패하면 1

    if (!code) { 
        server_init();

        std::thread th1[MAX_CLIENT];  // 크기가 MAX_CLIENT(3)인 배열 생성 배열에 담길 자료형은 std::thread
        for (int i = 0; i < MAX_CLIENT; i++) {
            th1[i] = std::thread(add_client); // main함수가 종료되지 않도록 해준다.
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
            //클라이언트를 받을 수 있는 상태를 만들어 줌
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
    // 서버 소켓을 특정할 수 있는 int형 숫자를 담음. server_sock의 sck -> SOCKET_INFO
    SOCKADDR_IN server_addr = {};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(7777); // ~~~~~~~:7777
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY); //127.0.0.1:~~~~~~~~~

    bind(server_sock.sck, (sockaddr*)&server_addr, sizeof(server_addr));  // server_sock.sck, 주소를 할당하고 싶은 socket
    // server_addr의 자료형 SOCKADDR_IN sockaddr* 형으로 변환
    listen(server_sock.sck, SOMAXCONN); 

    server_sock.user = "server";

    cout << "Server On" << endl;
}

void add_client() {
    // 클라이언트와 서버가 연결에 성공하면 새로운 소켓을 하나 생성하게 되는데, 그 주소를 담을 변수
    // 그 주소를 담을 변수 => addr
    SOCKADDR_IN addr = {};
    int addrsize = sizeof(addr); 
    char buf[MAX_SIZE] = { }; // 메세지 최대 길이 설정

    ZeroMemory(&addr, addrsize); //addr 메모리를 0으로 초기화

    SOCKET_INFO new_client = {}; // scj, user : 클라이언트의 소켓 정보를 저장

    new_client.sck = accept(server_sock.sck, (sockaddr*)&addr, &addrsize);
    recv(new_client.sck, buf, MAX_SIZE, 0); // 클라이언트의 소켓 정보를 저장
    // 클라이언트 측에서 user 이름을 담아서 sen를 한거를 recv()로 받기 위해 사용한다.
    new_client.user = string(buf); // buf를 string형으로 변환해서 user에 저장.

    string msg = "[공지] " + new_client.user + " 님이 입장했습니다.";
    cout << msg << endl; // 서버 콘솔에 공지 찍음
    sck_list.push_back(new_client); // sck list에 추가함
    // [ {12345, "so" } ............. ]
    std::thread th(recv_msg, client_count); // main 함수가 끝나지 않기 위해 사용 
   // 방금 생성된 클라이언트가 앞으로도 계속 메세지를 받을 수 있도록 recv
    client_count++;
    cout << "[공지] 현재 접속자 수 : " << client_count << "명" << endl;
    send_msg(msg.c_str()); //누가 들어왔는지 공지 하기 위해서

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
