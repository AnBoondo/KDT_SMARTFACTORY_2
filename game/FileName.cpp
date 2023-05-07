#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Weapon {
protected:
    int attackPower;
    int attackCount;
public:
    virtual void attack() = 0;
};

class Sword : public Weapon {
public:
    Sword() {
        attackPower = 5;
        attackCount = 3;
    }
    void attack() override {
        if (attackCount > 0) {
            cout << "���" << endl;
            attackCount--;
        }
        else {
            cout << "�� �̻� ����� �� �����ϴ�." << endl;
        }
    }
};

class Gun : public Weapon {
public:
    Gun() {
        attackPower = 10;
        attackCount = 1;
    }
    void attack() override {
        if (attackCount > 0) {
            cout << "�ѽ��" << endl;
            attackCount--;
        }
        else {
            cout << "�� �̻� ����� �� �����ϴ�." << endl;
        }
    }
};

class Horse {
public:
    void run() {
        cout << "���� �޸��ϴ�." << endl;
    }
};

class Character {
private:
    int hp;
    int level;
    vector<Weapon*> weapons;
public:
    Character() {
        hp = 100;
        level = 1;
    }
    void pickUpWeapon(Weapon* weapon) {
        weapons.push_back(weapon);
    }
    void attack(Character& enemy) {
        if (weapons.empty()) {
            cout << "������ �ִ� ���Ⱑ �����ϴ�." << endl;
            return;
        }
        int index = rand() % weapons.size(); // �������� ���� ����
        weapons[index]->attack();
        enemy.hp -= weapons[index]->attackPower;
        cout << "������ ü���� " << weapons[index]->attackPower << "��ŭ �����߽��ϴ�." << endl;
    }
};

int main() {
    Sword sword;
    Gun gun;
    Horse horse;

    Character player;
    Character enemy;

    player.pickUpWeapon(&sword);
    player.pickUpWeapon(&gun);

    player.attack(enemy);
    enemy.attack(player);

    return 0;
}