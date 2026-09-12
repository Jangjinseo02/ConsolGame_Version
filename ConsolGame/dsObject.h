#pragma once
#include <string>
#include <Windows.h>

class dsObject
{
private:
	std::string name;

public:
	dsObject(std::string name);
	virtual ~dsObject();

	std::string ShowName(); //오브젝트 이름 반환

};

