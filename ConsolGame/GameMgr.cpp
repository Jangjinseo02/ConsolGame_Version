#include "GameMgr.h"
#include "Player.h"
#include "Monster.h"
#include "Npc.h"
#include "IT_Restore.h"
#include "IT_Curse.h"
#include "IT_Fish.h"
#include "OBJ_Pond.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>

GameMgr::GameMgr() {
	keyCount = 0;
	maxObjectSize = 3;
	
	Add(0, new IT_Restore("상처약"));
	Add(1, new IT_Curse("저주"));
	Add(2, new IT_Fish("물고기"));
	//3 == field item
	monster = NULL;
	objPond = new OBJ_Pond("물고기", *Find(maxObjectSize - 1));
}

GameMgr::~GameMgr() {
	delete player;
	delete objPond;
	
	for (int i = 0; i < 2; i++) {
		Delete(i);
	}
	m_ITMap.clear();
	objPond = NULL;
}

LivingEntity* GameMgr::ReturnPlayer() {
	return player;
}

bool GameMgr::KeyCheck() {
	char key = -1;
	
	if (keyCount > 0) {
		if (player && player->OpenInven())
			if (!npc)
				printf("숫자키를 입력하여 아이템을 사용하세요\n");
	}
	else if (keyCount == 0) 
		if(npc)
			printf("어떤 행동을 하시겠습니까? \n[ 공격 ]\n[ 판매 ]\n[ 구매 ]\n");
		else if(monster)
			printf("어떤 행동을 하시겠습니까? \n[ 공격 ]\n[ 인벤토리 ]\n[ 획득 ]");	
		else
			printf("어떤 행동을 하시겠습니까? \n[ 공격 ]\n[ 인벤토리 ]\n[ 획득 ]\n[ 휴식 ]");
		
	key = _getch();
	system("cls");

	if (keyCount >= 0 && keyCount < 1) {
		keyCount += 1;

		switch (key) {
		case 97: // a : 공격
			if (monster)
				if (monster->Dead())
					printf("몬스터는 이미 죽어있습니다.\n===================================\n");
				else
					player->Attack(*monster);
			else if (npc)
				player->Attack(*npc);
			break;
		case 98: // b : 인벤토리 열기
			player->OpenInventory();
			KeyCheck();
			break;
		case 99: // c : 아이템 획득
			if (monster && monster->Dead()) //몬스터가 죽은 상태
				if (monster->DropItem())
					player->Get(*(monster->DropItem()));
				else
					printf("몬스터가 지닌 아이템이 존재하지 않습니다. \n아이템을 획득하지 못했습니다.\n===================================\n");
			else if (Find(maxObjectSize)) { //field item 발견
				player->Get(*Find(maxObjectSize));
			}
			else if (npc) { //상인 발견
				npc->OpenInventory();
				KeyCheck();
			}
			else //아무것도 존재하지 않을 경우
				printf("아이템을 획득하지 못했습니다.\n===================================\n");
			break;
		case 100: //몬스터와 npc 모두 존재 하지 않을 경우
			if (player && !npc && !monster) {
				printf("휴식을 취합니다.\n===================================\n");
				player->RestoreStamina(3);
				player->OnDamaged(10);
			}
			break;
		default:
			printf("아무런 행동을 하지 않았습니다.\n===================================\n");
			break;
		}

		if (Find(maxObjectSize))
			m_ITMap.erase(maxObjectSize);
		if (npc) {
			delete npc;
			npc = NULL;
		}
	}else {
		keyCount = 0;

		//인벤토리에 대한 행위 1~5 < 한번의 키 입력 이후 모든 키 입력은 숫자 키로 진행
		if (key > 48 && key <= 53) {
			
			if (npc) {
				if (player->OpenInven())
					player->SellItem(*npc, key - 49);
				else
					player->BuyItem(*npc, key - 49);

				KeyCheck();
			}
			else
				player->Action(key - 49, *monster);
		}
		else {
			printf("인벤토리를 나갑니다.\n===================================\n");
		}
	}

	keyCount = 0;
	return key;
}

void  GameMgr::OnUpdate() {

	srand((unsigned int)time(NULL));
	int pers = rand() % 100; //모든 생성은 확률로 진행

	printf("당신은 나아갑니다.\n=================================== \n");

	//monster를 상대하고 있지 않다면 스태미너를 지속적으로 사용
	if (!(player->ReturnAction(*monster)))
		player->UseStamina(); //전투 중이 아닌 상태에서 매번 스태미너 지속 사용, npc와의 활동에서는 keycheck의 재귀 호출에 의해서 이 부분이 실행되지 않음

	if (!player->Dead()) {
		if (monster == NULL && pers >= 70)
			SetMonster(pers);

		if (monster != NULL) {

			KeyCheck();

			Sleep(1000);

			if (monster != NULL && monster->Dead()) { //몬스터가 죽은 경우

				if (monster->DropItem()) //아이템이 있다면
					printf("아이템을 발견하였습니다. \n===================================\n");
				else //아이템이 없다면
					printf("몬스터가 지닌 아이템이 존재하지 않습니다.\n===================================\n");
				KeyCheck(); // 아이템 발견에 관한 키 입력

				player->SetExp(monster->GetExp()); //몬스터 당 알맞은 경험치 player에게 전달

				delete monster; //동적으로 몬스터 삭제
				monster = NULL; //monster 초기화
			}
			else { //몬스터가 죽지 않은 경우
				monster->Action('1', *player); //몬스터는 행동 '1'은 행동에 관한 인벤토리 키 값
			}
		}
		else if (pers >= 60) { //확률에 따른 연못 생성
			objPond->Use(*player); //연못을 player가 사용 > 연못 효과 적용 대상이 player가 된다.
		}
		else {
			int ran = rand() % 9;
			if (ran >= 7) { //field 아이템 발견
				printf("아이템을 발견하였습니다. \n===================================\n");

				Add(maxObjectSize, Find(ran / 8)); //map 가장 끝에 추가
			}
			else if (ran >= 5) {
				npc = new Npc("상점 주인"); //상인 생성
				for (int i = 0; i < 5; i++) { //상인 인벤토리 세팅
					int ran = rand() % 2;
					npc->Get(*Find(ran)); //map에서 랜덤으로 아이템 생성
				}
				printf("상점 주인과 만났습니다.\n ===================================\n");
			}
			else //위의 모든 일이 일어나지 않은 경우
				printf("아무일도 없었습니다.\n===================================\n");

			KeyCheck(); //키 체크 하여 이후 행동 판단
			player->SetExp(10); // originexp = 10; // 기본적인 player가 얻는 경험치 할당
		}
	}

	if (player->Dead()) { //플레이어가 죽은 경우
		printf("당신은 더이상 나아갈 수 없습니다.\n");
		ClearPlayer(); //모든 세팅을 지우고 초기화한다.
		return;
	}

	Sleep(1000);
}
//플레이어 세팅
void GameMgr::SetPlayer(std::string name) {
	std::string playerName = name;
	float hp = 100.0f;
	float atttackDamage = 10.0f;

	player = new Player(playerName, hp, atttackDamage);
}
//초기화
void GameMgr::ClearPlayer() {
	//플레이어 삭제 -> 몬스터 삭제
	if(player)
		delete player;
	if(monster)
		delete monster;
	if (npc)
		delete npc;
	
	player = NULL;
	monster = NULL;
	npc = NULL;
}
//몬스터 세팅
void GameMgr::SetMonster(int pers) {

	int ranItem = rand() % 2; //random item
	int ranLevel = rand() % player->ReturnLevel() + 1; //random level
	float value = 2 * ranLevel;

	if (pers <= 90) {
		monster = new Monster("고블린", 28 + value, 3 + value, 13 + value, 3 + ranLevel, ranLevel, Find(ranItem));
		monster->Get(*(monster->DropItem()));
	}
	else if (pers <= 97) {
		monster = new Monster("오크", 33 + value, 13 + value, 28 + value, 18 + ranLevel, ranLevel, Find(ranItem));
		monster->Get(*(monster->DropItem()));
	}
	else if (pers <= 100) {
		monster = new Monster("트롤", 58 + value, 28 + value, 48 + value, 48 + ranLevel, ranLevel, Find(ranItem));
		monster->Get(*(monster->DropItem()));
	}
	printf("%d레벨 %s가 나타났습니다. \n===================================\n", monster->ReturnLevel(), monster->ShowName().c_str());
}


void GameMgr::Add(int key, Object* value) {
	m_ITMap[key] = value;
}

Object* GameMgr::Find(int key) {
	return m_ITMap[key];
}

void GameMgr::Delete(int key) {
	ITEM_MAP::iterator it = m_ITMap.find(key);
	if (it != m_ITMap.end()) {
		delete it->second;
		m_ITMap.erase(it);
	}
}