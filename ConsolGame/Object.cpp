#include "Object.h"
#include "LivingEntity.h"

Object::Object(std::string name) : dsObject(name) {
	type = 0;
}

Object::~Object() {

}

void Object::Use(LivingEntity& target) {
	printf("아이템을 사용하였습니다.\n===================================\n");
	//item use
}

int Object::Type() {
	return type;
}