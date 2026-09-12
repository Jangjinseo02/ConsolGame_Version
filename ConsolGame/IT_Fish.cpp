#include "IT_Fish.h"
#include "LivingEntity.h"

IT_Fish::IT_Fish(std::string name) : Object(name) {
	type = 1; // player target
}
IT_Fish::~IT_Fish() {

}

void IT_Fish::Use(LivingEntity& target) {
	Object::Use(target);
	target.RestoreStamina(10);
}
