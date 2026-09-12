#pragma once
#include <map>
#include <string>

//생명체 클래스
class LivingEntity;
class Player;
class Monster;
class Npc;
//오브젝트 클래스
class Object;
class IT_Restore;
class IT_Curse;
class IT_Fish;
class OBJ_Pond;


class GameMgr
{
	typedef std::map<int, Object*> ITEM_MAP;

	ITEM_MAP m_ITMap; //아이템 할당, 랜덤으로 받아오기.

	Player* player;
	Monster* monster;
	Npc* npc;
	Object* object;
	OBJ_Pond* objPond;

	int keyCount;
	int maxObjectSize;
	
public:
	GameMgr();
	~GameMgr();

	LivingEntity* ReturnPlayer();
	bool KeyCheck(); //키보드 입력이 있는지 체크한다.
	void OnUpdate(); //게임을 갱신한다.

	void SetPlayer(std::string name); //플레이어 세팅
	void ClearPlayer(); //게임 초기화
	void SetMonster(int pers); //몬스터 세팅

	void Add(int key, Object* value); //map add
	Object* Find(int key); //map find
	void Delete(int key); //map delete
};

