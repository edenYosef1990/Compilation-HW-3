#include "attributes.h"

NonTermBool::NonTermBool() {
this->type = TYPE_BOOL;
}

NonTermBool::NonTermBool(std::string name) : DataObj(name) {
this->type = TYPE_BOOL;
}

bool NonTermBool::IsValidBoolExp(Node * node1, Node * node2 , Node * node3){
    if(dynamic_cast<NonTermBool*>(node1) == nullptr || dynamic_cast<NonTermBool*>(node3) == nullptr){
        return false;
    }
    return true;
}

bool NonTermBool::IsValidBoolExp(Node * node){
    
    return true;
}

