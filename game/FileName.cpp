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
            cout << "찌르기" << endl;
            attackCount--;
        }
        else {
            cout << "더 이상 사용할 수 없습니다." << endl;
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
            cout << "총쏘기" << endl;
            attackCount--;
        }
        else {
            cout << "더 이상 사용할 수 없습니다." << endl;
        }
    }
};

class Horse {
public:
    void run() {
        cout << "말이 달립니다." << endl;
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
            cout << "가지고 있는 무기가 없습니다." << endl;
            return;
        }
        int index = rand() % weapons.size(); // 무작위로 무기 선택
        weapons[index]->attack();
        enemy.hp -= weapons[index]->attackPower;
        cout << "상대방의 체력이 " << weapons[index]->attackPower << "만큼 감소했습니다." << endl;
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