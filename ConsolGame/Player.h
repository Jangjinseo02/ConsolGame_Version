#pragma once
#include "LivingEntity.h"
#include "Object.h"

class Player : public LivingEntity
{
private:
	int maxStamina;
	int stamina;

	bool action;
public:
	Player(std::string name, float hp, float attackDamage);
	~Player();

	bool Get(Object& obj); //아이템 획득
	bool ReturnAction(LivingEntity& target); //행동 판단

	void UseStamina(); //스태미너 사용
	void OnDamaged(float damage); //피해를 받음
	void OpenInventory(); //인벤토리 열기

	void SetExp(float value); //경험치 획득
	void LevelUp(); //레벨업

	void BuyItem(Npc& target, int key); //npc에게서 item 구매
	void SellItem(Npc& target, int key); //npc에게 item 판매

	void RestoreStamina(int value); //스태미너 회복
};

