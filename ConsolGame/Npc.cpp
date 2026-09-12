#include "Npc.h"

Npc::Npc(std::string name) : LivingEntity(name, 10, 0, 0) {
	
	int buyprice = rand() % 31 + 10;
	for (int i = 0; i < maxinven; i++) {
		int ran = rand() % 51 + 10;
		price[i] = ran;
		buyPrice[i] = buyprice;
	}
}

Npc::~Npc() {

}

void Npc::OnDamaged(float damage) {
	printf("공격 가능한 대상이 아닙니다.\n===================================\n");
}

void Npc::OpenInventory() {
	LivingEntity::OpenInventory();

	printf("======================================\n구매할 아이템을 숫자키로 선택해주세요.\n======================================\n");
	for (int i = 0; i < maxinven; i++) {
		printf("%d번째 아이템의 판매 가격 : %d\n", i + 1, price[i]);
	}
	printf("======================================\n나가려면 아무키나 입력해주세요.\n======================================\n");
}

int Npc::BuyPrice(int key) {
	return buyPrice[key];
}
int Npc::SellPrice(int key) {
	return price[key];
}

//인벤 내 아이템 반환
Object* Npc::FindInventory(int key) {
	if (isInventory[key]) {
		Object* item = inventory[key];
		inventory[key] = NULL;
		isInventory[key] = false;
		return item;
	}

	printf("해당 위치에 아이템이 존재하지 않습니다.\n======================================\n");
	return NULL;
}