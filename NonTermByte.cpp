#include "attributes.h"

NonTermByte::NonTermByte() {
this->type = TYPE_BYTE;
}

NonTermByte::NonTermByte(std::string name) : DataObj(name) {this->type = TYPE_BYTE;}
