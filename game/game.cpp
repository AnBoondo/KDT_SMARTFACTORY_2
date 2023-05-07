#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 무기 클래스
class Weapon {
protected:
    int attackPower; // 공격력
    int attackCount; // 공격 가능 횟수

public:
    Weapon(int attackPower, int attackCount) : attackPower(attackPower), attackCount(attackCount) {}

    // 공격력 getter
    int getAttackPower() const {
        return attackPower;
    }

    // 공격 가능 횟수 getter
    int getAttackCount() const {
        return attackCount;
    }

    // 공격 가능 횟수 setter
    void setAttackCount(int count) {
        attackCount = count;
    }

    // 공격하기
    virtual void attack() = 0;
};

// 칼 클래스
class Knife : public Weapon {
public:
    Knife() : Weapon(5, 3) {}

    void attack() override {
        if (attackCount > 0) {
            cout << "찌르기!" << endl;
            attackCount--;
        }
        else {
            cout << "칼로 공격할 수 없습니다." << endl;
        }
    }
};

// 총 클래스
class Gun : public Weapon {
public:
    Gun() : Weapon(10, 1) {}

    void attack() override {
        if (attackCount > 0) {
            cout << "총쏘기!" << endl;
            attackCount--;
        }
        else {
            cout << "총으로 공격할 수 없습니다." << endl;
        }
    }
};

// 캐릭터 클래스
class Character {
private:
    int hp; // 체력
    int level; // 레벨
    vector<Weapon*> weapons; // 가지고 있는 무기들

public:
    Character(int hp, int level) : hp(hp), level(level) {}

    // 무기 줍기
    void pickUpWeapon(Weapon* weapon) {
        weapons.push_back(weapon);
    }

    // 공격하기
    void attack(Character* target) {
        if (weapons.empty()) {
            cout << "무기가 없습니다." << endl;
            return;
        }

        for (Weapon* weapon : weapons) {
            weapon->attack();
            target->reduceHp(weapon->getAttackPower());
        }
    }

    // 체력 감소
    void reduceHp(int damage) {
        hp -= damage;
        if (hp < 0) {
            hp = 0;
        }
    }
};

int main() {
    Knife knife;
    Gun gun;

    Character hero(100, 1);
    Character enemy(200, 2);

    hero.pickUpWeapon(&knife);
    hero.pickUpWeapon(&gun);

    hero.attack(&enemy);

    return 0;
}