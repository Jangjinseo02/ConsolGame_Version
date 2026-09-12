#include "dsObject.h"

dsObject::dsObject(std::string name) {
	this->name = name;
}

dsObject::~dsObject() {

}

std::string dsObject::ShowName() {
	return name;
}