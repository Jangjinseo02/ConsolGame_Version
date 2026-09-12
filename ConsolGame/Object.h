#pragma once
#include "dsObject.h"

class LivingEntity;

class Object : public dsObject
{
protected:
	int type; // player target = 0, other target = 1. 아이템의 타겟 대상 판단 값

public:
	Object(std::string name);
	virtual ~Object();

	virtual void Use(LivingEntity& target); //아이템 혹은 상호작용 오브젝트의 사용
	int Type(); //현재 타입 반환
};

