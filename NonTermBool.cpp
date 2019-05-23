#include "attributes.h"

NonTermBool::NonTermBool() {

}

NonTermBool::NonTermBool(std::string name) : DataObj(name) {

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

