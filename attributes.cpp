#include "attributes.h"

bool IsItConstOrExistingSymbol(DataObj * dataObject){
    if(!(dataObject->IsItVar())){
        return true;
    }
    if(dynamic_cast<IDNotExists*>(dataObject)!=nullptr){
        return true;
    }
    return false;
}

Node* symbolNameToExp(TypeNameEnum type , std::string){
        switch(type){
            case TYPE_FUNC: return new NonTermFunc() ; break; // A Function cant be an ID in expression , so it must be an error!
            case TYPE_INT: return new NonTermInt(); break;
            case TYPE_B: return new NonTermB(); break;
            case TYPE_BYTE: return new NonTermByte(); break;
            case TYPE_BOOL: return new NonTermBool(); break;
            case TYPE_STR: return new NonTermStr(); break;
            case TYPE_NONEXIST: return new IDNotExists(); break;  // An ID in epxression cant be undeclared , so it must be an error!
        }
    return nullptr;  
}
Node* CallToExp(TypeNameEnum type){
    switch(type){
            case TYPE_INT: return new NonTermInt(); break;
            case TYPE_B: return new NonTermB(); break;
            case TYPE_BYTE: return new NonTermByte(); break;
            case TYPE_BOOL: return new NonTermBool(); break;
            case TYPE_STR: return new NonTermStr(); break;
            }
    return nullptr;
}

TypeNameEnum ExpToFuncPara(Node * node){
    if(dynamic_cast<NonTermBool*>(node)!= nullptr){
        return TYPE_BOOL;
    }
    else if(dynamic_cast<NonTermInt*>(node)!= nullptr){
        return TYPE_BOOL;
    }
    else if(dynamic_cast<NonTermStr*>(node)!= nullptr){
        return TYPE_BOOL;
    }
    else if(dynamic_cast<NonTermB*>(node)!= nullptr){
        return TYPE_B;
    }
    else if(dynamic_cast<NonTermByte*>(node)!= nullptr){
        return TYPE_BYTE;
    }
    return TYPE_NONEXIST;
}

std::vector<string> ParaListToStrings(std::list<TypeNameEnum> paraList){
    std::vector<string> vec = std::vector<string>();
    while(!paraList.empty()){
        TypeNameEnum type = paraList.front();
        std::string currPar = ""; 
        switch(type){
            case TYPE_INT: currPar="int"; break;
            case TYPE_B: currPar="b"; break;
            case TYPE_BYTE: currPar="byte"; break;
            case TYPE_BOOL: currPar="bool"; break;
        }
        vec.push_back(currPar);
        paraList.pop_front();
    }
    return vec;

}
