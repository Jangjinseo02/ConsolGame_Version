#include "IT_Curse.h"
#include "LivingEntity.h"

IT_Curse::IT_Curse(std::string name) : Object(name) {
	type = 2; // other target
}

IT_Curse::~IT_Curse() {

}


void IT_Curse::Use(LivingEntity& target) {
	Object::Use(target);
	target.OnDamaged(50.0f);	
}