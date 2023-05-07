#pragma comment(lib, "ws2_32.lib") // ��������� ���̺귯���� ȣ���ϴ� ��� �߿� �ϳ�

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

struct SOCKET_INFO {  // ����ü ����
    SOCKET sck; // ctrl + Ŭ��,  usigned int pointer ��
    string user; // user : ����� �̸�
};

std::vector<SOCKET_INFO> sck_list; // ������ ����� clients ������ ����
SOCKET_INFO server_sock; // ��������� ������ ������ ����
int client_count = 0; // ���� ���ӵ� Ŭ���̾�Ʈ �� ī��Ʈ �뵵

void server_init(); // ������ ������ ����� �Լ� ~ listen ()
void add_client(); // accept �Լ� ����ǰ� ���� ����
void send_msg(const char* msg); // send() ����
void recv_msg(int idx); // recv() ����
void del_client(int idx); // Ŭ���̾�Ʈ���� ������ ���� ��

int main() {
    WSADATA wsa;

    // Winsock�� �ʱ�ȭ�ϴ� �Լ�. MAKEWORD(2, 2)�� Winsock�� 2.2 ������ ����ϰڴٴ� �ǹ�.
    // ���࿡ �����ϸ� 0��, �����ϸ� �� �̿��� ���� ��ȯ.
    // 0�� ��ȯ�ߴٴ� ���� Winsock�� ����� �غ� �Ǿ��ٴ� �ǹ�.
    int code = WSAStartup(MAKEWORD(2, 2), &wsa);  // �����ϸ� 0, �����ϸ� 1

    if (!code) { 
        server_init();

        std::thread th1[MAX_CLIENT];  // ũ�Ⱑ MAX_CLIENT(3)�� �迭 ���� �迭�� ��� �ڷ����� std::thread
        for (int i = 0; i < MAX_CLIENT; i++) {
            th1[i] = std::thread(add_client); // main�Լ��� ������� �ʵ��� ���ش�.
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
            //Ŭ���̾�Ʈ�� ���� �� �ִ� ���¸� ����� ��
        }

        closesocket(server_sock.sck);
    }
    else {
        cout << "���α׷� ����. (Error code : " << code << ")";
    }

    WSACleanup();

    return 0;
}

void server_init() {
    server_sock.sck = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    // ���� ������ Ư���� �� �ִ� int�� ���ڸ� ����. server_sock�� sck -> SOCKET_INFO
    SOCKADDR_IN server_addr = {};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(7777); // ~~~~~~~:7777
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY); //127.0.0.1:~~~~~~~~~

    bind(server_sock.sck, (sockaddr*)&server_addr, sizeof(server_addr));  // server_sock.sck, �ּҸ� �Ҵ��ϰ� ���� socket
    // server_addr�� �ڷ��� SOCKADDR_IN sockaddr* ������ ��ȯ
    listen(server_sock.sck, SOMAXCONN); 

    server_sock.user = "server";

    cout << "Server On" << endl;
}

void add_client() {
    // Ŭ���̾�Ʈ�� ������ ���ῡ �����ϸ� ���ο� ������ �ϳ� �����ϰ� �Ǵµ�, �� �ּҸ� ���� ����
    // �� �ּҸ� ���� ���� => addr
    SOCKADDR_IN addr = {};
    int addrsize = sizeof(addr); 
    char buf[MAX_SIZE] = { }; // �޼��� �ִ� ���� ����

    ZeroMemory(&addr, addrsize); //addr �޸𸮸� 0���� �ʱ�ȭ

    SOCKET_INFO new_client = {}; // scj, user : Ŭ���̾�Ʈ�� ���� ������ ����

    new_client.sck = accept(server_sock.sck, (sockaddr*)&addr, &addrsize);
    recv(new_client.sck, buf, MAX_SIZE, 0); // Ŭ���̾�Ʈ�� ���� ������ ����
    // Ŭ���̾�Ʈ ������ user �̸��� ��Ƽ� sen�� �ѰŸ� recv()�� �ޱ� ���� ����Ѵ�.
    new_client.user = string(buf); // buf�� string������ ��ȯ�ؼ� user�� ����.

    string msg = "[����] " + new_client.user + " ���� �����߽��ϴ�.";
    cout << msg << endl; // ���� �ֿܼ� ���� ����
    sck_list.push_back(new_client); // sck list�� �߰���
    // [ {12345, "so" } ............. ]
    std::thread th(recv_msg, client_count); // main �Լ��� ������ �ʱ� ���� ��� 
   // ��� ������ Ŭ���̾�Ʈ�� �����ε� ��� �޼����� ���� �� �ֵ��� recv
    client_count++;
    cout << "[����] ���� ������ �� : " << client_count << "��" << endl;
    send_msg(msg.c_str()); //���� ���Դ��� ���� �ϱ� ���ؼ�

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
            msg = "[����] " + sck_list[idx].user + " ���� �����߽��ϴ�.";
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
