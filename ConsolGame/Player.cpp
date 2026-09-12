#include "Player.h"
#include "Npc.h"

Player::Player(std::string name, float hp, float attackDamage) : LivingEntity(name, hp, attackDamage, 0) {
	level = 1;

	this->maxStamina = 15;
	this->stamina = maxStamina;

	this->action = false;
}

Player::~Player() {

}

bool Player::Get(Object& obj) {

	if (LivingEntity::Get(obj)) {
		printf("아이템을 획득하였습니다. \t 획득한 아이템 : %s\n===================================\n", obj.ShowName().c_str());
		return true;
	}
		
	printf("아이템을 획득하지 못하였습니다.\n===================================\n");
	return false;
}

bool Player::ReturnAction(LivingEntity &target) {
	//monster가 존재하는 경우 player는 action(attack) 상태이다.
	//action(attack) 상태에서는 스태미너의 감소가 이루어지지 않는다.
	if (&target == NULL)
		action = false;
	else
		action = true;

	return action;
}

void Player::UseStamina() {
	stamina -= 1;

	if (stamina <= 0) {
		dead = true;
	}
	printf("%s의 스테미너가 감소합니다..\t %s의 현재 스테미너 : %d\n================================\n", ShowName().c_str(), ShowName().c_str(), stamina);
}

void Player::OnDamaged(float damage) {
	LivingEntity::OnDamaged(damage);

	if (hp <= 0) {
		dead = true;
		printf("Player Die : %d\n", dead);
	}
}

void Player::OpenInventory()
{
	LivingEntity::OpenInventory();

	printf("=====================================\n소지 금액 : %d\n=====================================\n", money);
	printf("나가려면 아무키나 입력해주세요.\n");
}

//경험치 획득
void Player::SetExp(float value) {
	exp = exp + value >= 100 ? 100 : exp + value;
	printf("%.3f 경험치를 획득하셨습니다. \t", value);
	printf("현재 경험치 : %.3f \n===================================\n", exp);

	if (exp >= 100) {
		LevelUp();
	}
}

//레벨업
void Player::LevelUp() {
	level += 1;
	hp = maxHp;
	attackDamage += 0.5f * level;
	exp = 0;
	printf("레벨이 증가합니다. \t 현재 레벨 : %d \t 현재 공격력 : %.2f \n", level, attackDamage);
	printf("체력을 모두 회복하였습니다. \n===================================\n");
}

//아이템 구매
void Player::BuyItem(Npc& target, int key) {

	Object* item = target.FindInventory(key);

	if (item == NULL) { //item이 없다면
		printf("구매할 수 없었습니다.\n=====================================\n");
		return;
	}
	else if (EmptyInventory() == 0) { //item이 있는데, 인벤토리 내에 빈 공간이 없는 경우
		printf("인벤토리가 가득 찼습니다.\n=====================================\n");
		return;
	}

	int price = target.SellPrice(key); // 가격 받아오기
	printf("소지 금액 : %d\n 아이템 가격 : %d\n", money, price);

	if (money >= price) { // 구매 가격이상 소지금이 있다면
		this->money -= price;
		printf("구매하였습니다.\n=====================================\n");
		Get(*item); //Npc 상인에게서 구매, Npc 상인의 물건 삭제
	}
	else { // 구매 가격이상 소지금이 없다면
		printf("구매할 수 없었습니다.\n=====================================\n");
	}
	printf("소지 금액 : %d\n=====================================\n", money);
	//인벤토리 닫힘
	isOpen = false;
}

//아이템 판매
void Player::SellItem(Npc& target, int key) {
	if (isInventory[key]) { // 인벤토리 내에 key 위치 값이 있다면
		int buyPrice = target.BuyPrice(key); // 가격 받아오기
		this->money += buyPrice; // 소지금에 더해 넣는다.

		printf("판매 가격 : %d \n", buyPrice);
		printf("%s의 판매를 완료하였습니다.\n", inventory[key]->ShowName().c_str());
		printf("=====================================\n소지 금액 : %d\n=====================================\n", money);

		inventory[key] = NULL; // 판매 된 아이템 공간을 초기화
		isInventory[key] = false; // 기존 아이템 위치를 초기화
	}
	else {
		printf("아이템이 존재하지 않습니다.\n=====================================\n");
	}

	//인벤토리 닫힘
	isOpen = false;
}

void Player::RestoreStamina(int value) {
	stamina += value;

	if (stamina >= maxStamina) {
		stamina = maxStamina;
	}

	printf("%s의 스테미너가 회복되었습니다.\t %s의 현재 스테미너 : %d\n================================\n", ShowName().c_str(), ShowName().c_str(), stamina);
}

