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

Node* TypeNameToExp(TypeNameEnum type){
        switch(type){
            case TYPE_FUNC: return new NonTermFunc() ; break; // A Function cant be an ID in expression , so it must be an error!
            case TYPE_INT: return new NonTermInt(); break;
            case TYPE_BYTE: return new NonTermByte(); break;
            case TYPE_BOOL: return new NonTermBool(); break;
            case TYPE_STR: return new NonTermStr(); break;
        }
    return nullptr;  
}

TypeNameEnum TypeNameToTypeEnum(Node * node){
    Type* typeName = dynamic_cast<Type*>(node);
    return typeName->name;
}

TypeNameEnum ExpToTypeName(Node * node){
    if(dynamic_cast<NonTermBool*>(node)!= nullptr){
        return TYPE_BOOL;
    }
    else if(dynamic_cast<NonTermInt*>(node)!= nullptr){
        return TYPE_INT;
    }
    else if(dynamic_cast<NonTermStr*>(node)!= nullptr){
        return TYPE_STR;
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
            case TYPE_BYTE: currPar="byte"; break;
            case TYPE_BOOL: currPar="bool"; break;
        }
        vec.push_back(currPar);
        paraList.pop_front();
    }
    return vec;

}

std::string TypeToString(TypeNameEnum type){
    switch(type){
            case TYPE_INT: return std::string("INT"); break;
            case TYPE_BYTE: return std::string("BYTE"); break;
            case TYPE_BOOL: return std::string("BOOL"); break;
            case TYPE_STR: return std::string("STRING"); break;
            }
    return "none";
}

int yyerror(char const* message)
{
	exit(0);
}
