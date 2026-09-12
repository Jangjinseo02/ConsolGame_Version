#pragma once
#include "Object.h"
#include "LivingEntity.h"

class IT_Fish :
    public Object
{
public:
    IT_Fish(std::string name);
    ~IT_Fish();

    void Use(LivingEntity& target);
};

