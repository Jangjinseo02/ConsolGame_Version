#pragma once
#include "Object.h"

class LivingEntity;

class OBJ_Pond :
    public Object
{
private:
    Object* fish;
public:
    OBJ_Pond(std::string name, Object& fish);
    ~OBJ_Pond();

    void Use(LivingEntity& target);

    void keyCheck(LivingEntity& target);

    void Rest(LivingEntity& target);
    void Fishing(LivingEntity& target);
    void Drink(LivingEntity& target);
};

