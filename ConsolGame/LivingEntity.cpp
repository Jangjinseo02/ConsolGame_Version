#include "LivingEntity.h"
#include "Object.h"
#include "Npc.h"

LivingEntity::LivingEntity(std::string name, float hp, float attackDamage, float exp) : dsObject(name) {
	this->maxHp = hp;
	this->hp = hp;

	this->attackDamage = attackDamage;
	this->exp = exp;

	this->dead = false;
	
	this->maxinven = 5;
	this->money = 100;
}

//인벤 아이템 초기화
LivingEntity::~LivingEntity() {
	for (int i = 0; i < maxinven; i++) {
		if (isInventory[i]) {
			inventory[i] = NULL;
			isInventory[i] = false;
		}
	}
}

//생명체들은 아이템 획득
bool LivingEntity::Get(Object& obj) {

	int value = EmptyInventory();

	if (value) {
		inventory[value - 1] = &obj;
		isInventory[value - 1] = true;
		return true;
	}
	return false;
}

//피해를 입는다.
void LivingEntity::OnDamaged(float damage) {
	hp -= damage;

	if (hp <= 0) {
		hp = 0;
	}
	printf("%s의 체력이 감소하였습니다.\t %s의 현재 체력 : %.1f\n================================\n", ShowName().c_str(), ShowName().c_str(), hp);
}

//아이템 사용의 행동
void LivingEntity::Action(int key, LivingEntity& target) {

	printf("%s(이)가 행동합니다.\n", ShowName().c_str());
	if (isInventory[key]) {
		if (inventory[key]->Type() == 1)
			UseItem(key, this);
		else if (inventory[key]->Type() == 2 && &target != NULL)
			UseItem(key, &target);
		else
			printf("%s(이)가 행동에 실패하였습니다..\n================================\n", ShowName().c_str());
	}
	else
		printf("%s(이)가 행동에 실패하였습니다..\n================================\n", ShowName().c_str());

	//인벤토리 닫힘
	isOpen = false;
}

//아이템 사용 
void LivingEntity::UseItem(int key, LivingEntity *target)
{
	if (isInventory[key]) {
		inventory[key]->Use(*target);
		inventory[key] = NULL;
		isInventory[key] = false;
	}
	else
		printf("아이템이 존재하지 않습니다.\n================================\n");
}

//인벤토리 열기
void LivingEntity::OpenInventory()
{
	printf("================================\n%s의 인벤토리\n================================\n", ShowName().c_str());
	for (int i = 0; i < maxinven; i++) {
		if (isInventory[i]) {
			printf("%d번째 칸 : %s\n", i + 1, inventory[i]->ShowName().c_str());
		}
		else {
			printf("[빈 공간]\n");
		}
	}
	isOpen = true;
}

int LivingEntity::EmptyInventory() {
	for (int i = 0; i < maxinven; i++) {
		if (!isInventory[i]) {
			return i + 1;
		}
	}
	return 0;
}

int LivingEntity::ReturnLevel() { return level; }

//공격
void LivingEntity::Attack(LivingEntity& target) {
	printf("%s 가 공격합니다.\n", ShowName().c_str());
	target.OnDamaged(attackDamage);
}

//죽음에 관해서
bool LivingEntity::Dead() { return dead; }
bool LivingEntity::OpenInven() { return isOpen; }

//회복
void LivingEntity::Restore(float value) {
	hp += value;
	if (hp >= maxHp) {
		hp = maxHp;
	}
	printf("%s의 체력이 회복되었습니다.\t %s의 현재 체력 : %.2f\n================================\n", ShowName().c_str(), ShowName().c_str(), hp);
}

void LivingEntity::RestoreStamina(int value) {

}