#pragma once
#include "LivingEntity.h"

class Monster :
    public LivingEntity
{
public:
    //지니고 있는 아이템
    Object* dropItem;
public:
    Monster(std::string name, float hp, float attackDamage, float exp, int money , int level, Object* object);
    ~Monster();

    //아이템 사용
    void UseItem(int key, LivingEntity* target);
    //데미지를 입는다.
    void OnDamaged(float damage);
    //경험치를 반환한다.
    float GetExp();

    //몬스터의 행동
    void Action(int key, LivingEntity& target);
    //지니고 있는 아이템을 반환한다.
    Object* DropItem();
};

