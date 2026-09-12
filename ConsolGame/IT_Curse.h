#pragma once
#include "Object.h"

class IT_Curse :
    public Object
{
public:
    IT_Curse(std::string name);
    ~IT_Curse();

    void Use(LivingEntity& target);
};

