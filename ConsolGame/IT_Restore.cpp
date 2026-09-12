#include "IT_Restore.h"
#include "LivingEntity.h"

IT_Restore::IT_Restore(std::string name) : Object(name) {
	type = 1; // player target
}

IT_Restore::~IT_Restore() {

}

void IT_Restore::Use(LivingEntity& target) {
	Object::Use(target);
	target.Restore(30);
}