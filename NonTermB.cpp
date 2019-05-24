#include "attributes.h"

NonTermB::NonTermB() {
this->type = TYPE_B;
}

NonTermB::NonTermB(std::string name) : DataObj(name) {this->type = TYPE_B;}

bool NonTermB::IsValidB(Node * node){
    
    int number = (dynamic_cast<NonTermInt*>(node))->GetNumericValue();
    return (number >=0 && number <=255) ? true : false;
}