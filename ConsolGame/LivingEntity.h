#pragma once
#include "dsObject.h"

class Object;
class Npc;

class LivingEntity : public dsObject
{
protected:
	//std::string name;
	int level;
	int money;

	float maxHp;
	float hp;
	
	float attackDamage;
	float exp;
	
	bool dead;

	Object* inventory[5]; //
	bool isInventory[5] = { false };
	bool isOpen = false;
	int maxinven;
public:

	LivingEntity(std::string name, float hp, float attackDamage, float exp);
	virtual ~LivingEntity();

	//아이템을 얻는다.
	virtual bool Get(Object& obj);
	//모든 생명체는 공격 당한다.
	virtual void OnDamaged(float damage);
	//아이템 사용 행동
	virtual void Action(int key, LivingEntity& target);
	//실제 아이템 사용
	virtual void UseItem(int key, LivingEntity* target);
	virtual void OpenInventory();

	//모든 생명체는 공격가능하다.
	void Attack(LivingEntity& target);
	//죽음 반환
	bool Dead();
	//인벤토리가 열린지 판단
	bool OpenInven();
	//인벤토리가 비었는지 판단
	int EmptyInventory();
	//현재 레벨 반환
	int ReturnLevel();

	//체력 회복
	void Restore(float value);
	//스태미너 회복(player 사용)
	virtual void RestoreStamina(int value);

};

