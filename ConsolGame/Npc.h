#pragma once
#include "LivingEntity.h"
class Npc :
    public LivingEntity
{
    int price[5];
    int buyPrice[5];
public:
    Npc(std::string name);
    ~Npc();

    //데미지를 입는다.
    void OnDamaged(float damage);
    //인벤토리를 연다
    void OpenInventory();

    //구매 가격
    int BuyPrice(int key);
    //판매 가격
    int SellPrice(int key);

    //인벤토리 내 아이템을 반환
    Object* FindInventory(int key);
};

