#include <iostream>
#include <string>
#include <mysql/jdbc.h>

using std::cout;
using std::endl;
using std::string;

const string server = "tcp://127.0.0.1:3306"; // 데이터베이스 주소 (3306: MySQL 데이터베이스 기본 포트 번호)
const string username = "root"; // 데이터베이스 사용자
const string password = "rlaTl234!@"; // 데이터베이스 접속 비밀번호

int main()
{
    // MySQL Connector/C++ 초기화
    sql::mysql::MySQL_Driver* driver; // 추후 해제하지 않아도 Connector/C++가 자동으로 해제해 줌
    sql::Connection* con;
    sql::Statement* stmt;
    sql::PreparedStatement* pstmt;

    // MySQL 연결
    try {
        driver = sql::mysql::get_mysql_driver_instance();
        con = driver->connect(server, username, password); // MySQL 데이터베이스 연결 객체
    }
    catch (sql::SQLException& e) {
        cout << "Could not connect to server. Error message: " << e.what() << endl;
        exit(1);
    }

    // 데이터베이스 선택
    con->setSchema("kdt");
    
    // db 한글 저장을 위한 셋팅 
    stmt = con->createStatement();
    stmt->execute("set names euckr");
    if (stmt) { delete stmt; stmt = nullptr; }

    // stmt 객체를 사용해서 SQL 쿼리를 실행할 수 있다
    stmt = con->createStatement();
    stmt->execute("DROP TABLE IF EXISTS inventory"); // DROP
    cout << "Finished dropping table (if existed)" << endl;

    stmt->execute("CREATE TABLE inventory (id serial PRIMARY KEY, name VARCHAR(50), quantity INTEGER);"); // CREATE
    cout << "Finished creating table" << endl;
    delete stmt;

    // pstmt를 이용하면 입력 값을 나중에 지정할 수 있다.
    pstmt = con->prepareStatement("INSERT INTO inventory(name, quantity) VALUES(?,?)"); // INSERT

    pstmt->setString(1, "banana"); // 첫 번째 컬럼에 'banana' string 삽입
    pstmt->setInt(2, 150); // 두 번째 컬럼에 150 int 삽입
    pstmt->execute(); // 쿼리 실행
    cout << "One row inserted." << endl;

    pstmt->setString(1, "orange");
    pstmt->setInt(2, 154);
    pstmt->execute();
    cout << "One row inserted." << endl;

    pstmt->setString(1, "사과");
    pstmt->setInt(2, 100);
    pstmt->execute();
    cout << "One row inserted." << endl;

    // MySQL Connector/C++ 정리
    delete pstmt;
    delete con;

    return 0;
}