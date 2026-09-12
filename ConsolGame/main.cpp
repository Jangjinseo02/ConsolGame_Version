#include "Player.h"
#include "GameMgr.h"
#include <conio.h>
#include <Windows.h>
#include <iostream>

void main() {
	GameMgr mgr;
	std::string name;
	LivingEntity* player = mgr.ReturnPlayer();

	while (1) {
		printf("=======================================\n종료 : 0 \n게임을 시작하려면 아무키나 입력해 주세요\n=======================================\n");
		printf("[ 입력 키 ]\n");
		printf("[ a : 공격 ]\n[ b : 인벤토리 ] [ b : 구매  ]\n[ c : 획득  ]\t[ c : 판매 ]\n[ d : 휴식 ]\n[ 인벤토리 선택 : 숫자 패드 1 ~ 5 ]\n=======================================\n");
		char key = -1;

		key = _getch();

		system("cls");

		if (key != 48) {
			printf("플레이어 이름을 입력해주세요 : ");
			std::cin >> name;
			system("cls");

			if (player == NULL) {
				mgr.SetPlayer(name);
				player = mgr.ReturnPlayer();
			}

			while (!((*player).Dead())) {

				mgr.OnUpdate();
			}
			player = NULL;
		}
		else {
			printf("\n===================================\n게임이 종료됩니다.\n===================================\n");
			break;
		}
	}
	
}