#pragma comment(lib, "ws2_32.lib")

#include <WinSock2.h> //Winsock 헤더파일 include. WSADATA 들어있음.ㄴ
#include <WS2tcpip.h>
#include <string>
#include <sstream>
#include <iostream>
#include <thread>

#define MAX_SIZE 1024

using std::cout;
using std::cin;
using std::endl;
using std::string;

SOCKET client_sock;
string my_nick;

int chat_recv() {
    char buf[MAX_SIZE] = { };
    string msg;

    while (1) {
        ZeroMemory(&buf, MAX_SIZE);
        if (recv(client_sock, buf, MAX_SIZE, 0) > 0) {
            msg = buf;
            std::stringstream ss(msg);  // 문자열을 스트림화
            string user;
            ss >> user; // 스트림을 통해, 문자열을 공백 분리해 변수에 할당
            if (user != my_nick) cout << buf << endl; // 내가 보낸 게 아닐 경우에만 출력하도록.
        }
        else {
            cout << "Server Off" << endl;
            return -1;
        }
    }
}

int main() {
    WSADATA wsa;

    // Winsock를 초기화하는 함수. MAKEWORD(2, 2)는 Winsock의 2.2 버전을 사용하겠다는 의미.
    // 실행에 성공하면 0을, 실패하면 그 이외의 값을 반환.
    // 0을 반환했다는 것은 Winsock을 사용할 준비가 되었다는 의미.
    int code = WSAStartup(MAKEWORD(2, 2), &wsa);

    if (!code) {
        cout << "사용할 닉네임 입력 >> ";
        cin >> my_nick;

        client_sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP); // 

        SOCKADDR_IN client_addr = {};
        client_addr.sin_family = AF_INET;
        client_addr.sin_port = htons(7777);
        InetPton(AF_INET, TEXT("127.0.0.1"), &client_addr.sin_addr);

        while (1) {
            if (!connect(client_sock, (SOCKADDR*)&client_addr, sizeof(client_addr))) {
                cout << "Server Connect" << endl;
                send(client_sock, my_nick.c_str(), my_nick.length(), 0);
                break;
            }
            cout << "Connecting..." << endl;
        }

        std::thread th2(chat_recv);

        while (1) {
            string text;
            std::getline(cin, text);
            const char* buffer = text.c_str(); // string형을 char* 타입으로 변환
            send(client_sock, buffer, strlen(buffer), 0);
        }
        th2.join();
        closesocket(client_sock);
    }

    WSACleanup();
    return 0;
}

// 서버는 listen까지 잘 실행되면 소켓 활성화 서버는 accept를 통해서 클라이언트의 요청을 받음. 새로운 소켓을 만들어서 1:1 연결(서버와 클라이언트를)
// 이때의 소켓 정보를 서버에 sck_list vector 모두 저장
// 클라이언트는 connect를 통해서 내가 연결하고자 하는 서버에 연결 요청을 보냄.(서버에서 새로 만든 소켓을 통해, 나와 서버가 1:1통신을 할 수 있는 상태가 됨)
// send / recv 서로 통신
// 서버에 접속해 있는 모든 클라이언트에게 한명의 클라이언트가 보낸 메시지를 전송해야함.
// 누군진 모르겠지만 특정 클라이언트가 메세지를 보내면, 서버는 서버에 연결되어 있는 모든 소켓 정보를(sck_list)를 이용해 for문을 돌면서 모든 클라이언트에게 send를 하게됨.

// 서버가 send 하는 순간은?
// 1. accept를 하는 순간 
// 2. 서버측 콘솔창에서 채팅을 입력했을 떄
// 3. 나갔을 때
// 4. 클라이언트가 보낸 메시지를 recv로 받았을 때

// 클라이언트가 send 하는 순간
// 1. 입장할 때 connect 하고 바로 한 번 실행. 왜? 내 닉네임을 알려주기 위해
// 2. 콘솔에 메시지를 입력하는 순간