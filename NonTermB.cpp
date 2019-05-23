#include "attributes.h"

NonTermB::NonTermB() {

}

NonTermB::NonTermB(std::string name) : DataObj(name) {}

bool NonTermB::IsValidB(Node * node){
    
    int number = (dynamic_cast<NonTermInt*>(node))->GetNumericValue();
    return (number >=0 && number <=255) ? true : false;
}