#include "OBJ_Pond.h"
#include "LivingEntity.h"
#include "conio.h"


OBJ_Pond::OBJ_Pond(std::string name, Object& fish) : Object(name) {
	type = 1;
	this->fish = &fish;
}

OBJ_Pond::~OBJ_Pond() {
	this->fish = NULL;
}

void OBJ_Pond::Use(LivingEntity& target) {
	printf("연못을 발견하였습니다.\n ===================================\n");
	
	keyCheck(target);
}


void OBJ_Pond::keyCheck(LivingEntity& target) {
	char key = -1;

	printf("[휴식합니다.] \t [물고기를 낚습니다.] \t [물을 마십니다.]\n ===================================\n");

	key = _getch();

	switch (key) {
	case 49:
		Rest(target);
		break;
	case 50:
		Fishing(target);
		break;
	case 51:
		Drink(target);
		break;
	}
}

void OBJ_Pond::Rest(LivingEntity& target) {
	int ran = rand() % 10;

	if (ran <= 3) {
		printf("호수에 몸을 담구었습니다.\n ===================================\n");
		Sleep(1000);
		if (ran <= 1) {
			printf("호수 아래에 무언가가 당신을 끌어당깁니다.\n ===================================\n");
			Sleep(1000);
			if (ran == 0) {
				printf("당신은 빠져나오지 못하였습니다.\n ===================================\n");
				target.OnDamaged(100);
				return;
			}
			printf("당신은 기적적으로 빠져나왔습니다.\n ===================================\n");
			target.OnDamaged(50);
			return;
		}
		else {
			printf("당신은 이 호수가 상당히 좋다는 것을 느꼈습니다.\n ===================================\n");
			target.RestoreStamina(10);
			target.Restore(50);
		}
	}
	else {
		printf("당신은 편안한 휴식을 취하였습니다.\n ===================================\n");
		target.RestoreStamina(5);
	}
}

void OBJ_Pond::Fishing(LivingEntity& target) {
	int ran = rand() % 10;

	if (ran <= 5) {
		//target.Get() 물고기 획득
		printf("물고기를 얻었습니다.!\n ===================================\n");
		target.Get(*fish);
	}
	else if (ran <= 8) {
		//쓰레기 획득
		printf("쓰레기를 얻었습니다... \n ===================================\n");
	}
	else {
		printf("아무것도 얻지 못하였습니다.\n ===================================\n");
	}
}

void OBJ_Pond::Drink(LivingEntity& target) {
	
	int ran = rand() % 10;

	if (ran <= 3) {
		//랜덤 값으로 사망하는 거 만들자.
		printf("식수가 아니었습니다.\n ===================================\n");
		target.OnDamaged(100);
	}
	else {
		target.Restore(50);
	}
}