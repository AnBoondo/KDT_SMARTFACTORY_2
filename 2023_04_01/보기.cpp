class Snack {
protected:
    string money;
    string name;
    string factory_name;
public:
    virtual void snack_status() {

    }
};

class Candy :public Snack {
    string taste;
public:
    Candy(string money, string name, string factory_name, string taste) {
        this->money = money;
        this->name = name;
        this->factory_name = factory_name;
        this->taste = taste;
    }
    void snack_status() {
        cout << "종류: 사탕" << endl;
        cout << "가격: " << money << endl;
        cout << "과자명: " << name << endl;
        cout << "맛: " << taste << endl;
        cout << "제조사: " << factory_name << endl;
    }

};

class Chocolate :public Snack {
    string design;
public:
    Chocolate(string money, string name, string factory_name, string design) {
        this->money = money;
        this->name = name;
        this->factory_name = factory_name;
        this->design = design;
    }
    void snack_status() {
        cout << "종류: 초콜릿" << endl;
        cout << "가격: " << money << endl;
        cout << "과자명: " << name << endl;
        cout << "모양: " << design << endl;
        cout << "제조사: " << factory_name << endl;
    }

};


int main() {
    Snack* snackBasket[4] = { new Candy("900", "청포도","짱구 주식회사", "청포도 모양"),
       new Candy("800","돌사탕","맹구 주식회사","설탕맛"),
       new Chocolate("3500", "석기시대","맹구 주식회사", "돌멩이 모양"),
       new Chocolate("2800","초코비","짱구 주식회사","민초맛")
    };

    for (int i = 0; i < 4; i++) {
        snackBasket[i]->snack_status();
        cout << "--------------------\n";
    }

    for (int j = 0; j < 4; j++) {
        delete snackBasket[j];
    }
}