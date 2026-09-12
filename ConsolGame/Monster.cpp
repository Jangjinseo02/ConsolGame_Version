#include "Monster.h"
#include <iostream>

Monster::Monster(std::string name, float hp, float attackDamage, float exp, int money, int level, Object* object) : LivingEntity(name, hp, attackDamage, exp) {
	dropItem = object;
	this->money = money;
	this->level = level;
}

Monster::~Monster() {
	dropItem = NULL;
}

void Monster::UseItem(int key, LivingEntity* target)
{
	LivingEntity::UseItem(key, target);
	dropItem = NULL;
}


void Monster::OnDamaged(float damage) {
	LivingEntity::OnDamaged(damage);

	if (hp <= 0) {
		printf("%s가 죽었습니다.\n===================================\n", ShowName().c_str());
		dead = true;
	}
}

float Monster::GetExp() {
	return this->exp;
}

void Monster::Action(int key, LivingEntity& target) {
	int b = rand() % 5;

	if (b == 2) {
		printf("몬스터가 인벤토리를 뒤집니다.\n===================================\n");
		LivingEntity::Action(key - 49, target);
	}
	else
		Attack(target);
}

Object* Monster::DropItem(/*dropitem*/) {
	return dropItem;
}