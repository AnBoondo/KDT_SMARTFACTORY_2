#include <iostream>
#include <string>
#include <mysql/jdbc.h>

using std::cout;
using std::endl;
using std::string;

const string server = "tcp://127.0.0.1:3306"; // �����ͺ��̽� �ּ� (3306: MySQL �����ͺ��̽� �⺻ ��Ʈ ��ȣ)
const string username = "root"; // �����ͺ��̽� �����
const string password = "rlaTl234!@"; // �����ͺ��̽� ���� ��й�ȣ

int main()
{
    // MySQL Connector/C++ �ʱ�ȭ
    sql::mysql::MySQL_Driver* driver; // ���� �������� �ʾƵ� Connector/C++�� �ڵ����� ������ ��
    sql::Connection* con;
    sql::Statement* stmt;
    sql::PreparedStatement* pstmt;
    sql::ResultSet* result;


    // MySQL ����
    try {
        driver = sql::mysql::get_mysql_driver_instance();
        con = driver->connect(server, username, password); // MySQL �����ͺ��̽� ���� ��ü
    }
    catch (sql::SQLException& e) {
        cout << "Could not connect to server. Error message: " << e.what() << endl;
        exit(1);
    }

    // �����ͺ��̽� ����
    con->setSchema("kdt");

    // db �ѱ� ������ ���� ���� 
    stmt = con->createStatement();
    stmt->execute("set names euckr");
    if (stmt) { delete stmt; stmt = nullptr; }

    // stmt ��ü�� ����ؼ� SQL ������ ������ �� �ִ�
    stmt = con->createStatement();
    stmt->execute("DROP TABLE IF EXISTS inventory"); // DROP
    cout << "Finished dropping table (if existed)" << endl;

    stmt->execute("CREATE TABLE inventory (id serial PRIMARY KEY, name VARCHAR(50), quantity INTEGER);"); // CREATE
    cout << "Finished creating table" << endl;
    delete stmt;

    // pstmt�� �̿��ϸ� �Է� ���� ���߿� ������ �� �ִ�.
    pstmt = con->prepareStatement("INSERT INTO inventory(name, quantity) VALUES(?,?)"); // INSERT

    pstmt->setString(1, "banana"); // ù ��° �÷��� 'banana' string ����
    pstmt->setInt(2, 150); // �� ��° �÷��� 150 int ����
    pstmt->execute(); // ���� ����
    cout << "One row inserted." << endl;

    pstmt->setString(1, "orange");
    pstmt->setInt(2, 154);
    pstmt->execute();
    cout << "One row inserted." << endl;

    pstmt->setString(1, "���");
    pstmt->setInt(2, 100);
    pstmt->execute();
    cout << "One row inserted." << endl;

    pstmt = con->prepareStatement("SELECT * FROM inventory;");
    result = pstmt->executeQuery();

    while (result->next())
        printf("Reading from table=(%d, %s, %d)\n", result->getInt(1), result->getString(2).c_str(), result->getInt(3));

    pstmt = con->prepareStatement("DELETE FROM inventory WHERE name = ?");
    pstmt->setString(1, "orange");
    result = pstmt->executeQuery();
    printf("Row deleted\n");

    // MySQL Connector/C++ ����
    delete result;
    delete pstmt;
    delete con;
    system("pause");
    return 0;
}

using namespace std;
SOCKET client_sock;
string nickname;
string id, password;
sql::mysql::MySQL_Driver* driver; // MySQL ����̹� ��ü
sql::Connection* con; // MySQL ���� ��ü

int chat_recv() {
    char buf[MAX_SIZE] = {};
    string msg;
    while (1) {
        ZeroMemory(&buf, MAX_SIZE);
        if (recv(client_sock, buf, MAX_SIZE, 0) > 0) {
            msg = buf;
            stringstream ss(msg);
            string user;
            ss >> user;
            if (user != nickname) cout << buf << endl;
        }
        else {
            cout << "Server Off" << endl;
            return -1;
        }
    }
}

struct User {
    string id;
    string password;
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

void registerUser() {
    cout << "���̵� �Է����ּ���: ";
    cin >> id;

    if (isUserExist(id)) {
        cout << "�̹� �����ϴ� ���̵��Դϴ�." << endl;
        return;
    }

    cout << "��й�ȣ�� �Է����ּ���: ";
    cin >> password;

    cout << "����� �г��� �Է� >> ";
    cin >> nickname;

    // MySQL ���� �����Ͽ� ����� ������ �����ͺ��̽��� ����
    try {
        sql::Statement* stmt = con->createStatement();
        string sql = "INSERT INTO users (id, password, nickname) VALUES ('" + id + "', '" + password + "', '" + nickname + "')";
        stmt->execute(sql);
        delete stmt;

        userDatabase.push_back({ id, password });
        cout << "ȸ�������� �Ϸ�Ǿ����ϴ�." << endl;
        Sleep(3000);
    }
    catch (sql::SQLException& e) {
        cout << "ȸ������ �� ������ �߻��߽��ϴ�: " << e.what() << endl;
    }
}