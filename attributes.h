#ifndef ATTR_H
#define ATTR_H

#include <iostream>
#include "string"
#include "typeEnums.h"
#include "AidFunctions.h"

class Node {
    public:
    Node(){}
    virtual ~Node() = default;
};

//======================================token's Classes=====================================//

class Type : public Node {
    public:
    TypeNameEnum name;
        Type(TypeNameEnum _typeName) : name(_typeName) {}
};

class Op : public Node {
    opTypeEnum type;
    public:
        Op(opTypeEnum _opType) : type(_opType) {}
        Op(char * _opType) {
            std::string strType(_opType);
            if(strType == "=="){
                type = OP_EQU;
            }
            else if(strType == "!="){
                type = OP_NEQ;
            }
            else if(strType == "!="){
                type = OP_NEQ;
            }
            else if(strType == "<"){
                type = OP_RIGHTBIG;
            }
            else if(strType == ">"){
                type = OP_LEFTBIG;
            }
            else if(strType == "<="){
                type = OP_RIGHTBIGEQ;
            }
            else if(strType == ">="){
                type = OP_LEFTBIGEQ;
            }
        }
};

class BoolVal : public Node {
    ValBoolTypeEnum type;
    public:
        BoolVal(ValBoolTypeEnum _ValboolType) : type(_ValboolType) {}
};

class CmdWord : public Node {
    cmdTypeEnum type;
    public:
        CmdWord(cmdTypeEnum _cmdType) : type(_cmdType)  {}
};

class ScopeVal : public Node {
    scopeValEnum type;
    public:
        ScopeVal(scopeValEnum _scopeType) : type(_scopeType) {}

};

class NumVal : public Node {
    int val;
    public:
        NumVal(char * strNum) : val(CharPointerToInt(strNum)) {}
        int getVal() {return val;}
};

class IdVal : public Node {
    std::string IdStr;
    public:
        IdVal(char * strId) : IdStr(strId) {}
        std::string GetVal() {return IdStr;}
};

class StrVal : public Node {
    std::string str;
    public:
        StrVal(char * strVal) : str(strVal) {}
};

//======================================Non Terminals's Classes=====================================//

class DataObj : public Node {
    public:
        TypeNameEnum type;
        std::string Name;
        bool IsVar;
        DataObj(std::string name ) : Name(name) {
            IsVar = true;
        }
        DataObj() {
            IsVar = false;
        }
        bool IsItVar() {return IsVar;}
        virtual ~DataObj() = default;
};

class NonTermBool : public DataObj {
    std::string name;
    bool IsVar;
    public:
    static bool IsValidBoolExp(Node * node);
    static bool IsValidBoolExp(Node * node1, Node * node2 , Node * node3);
    NonTermBool();
    NonTermBool(std::string name);
    bool IsItVar() {return IsItVar();}
};

class NonTermStr : public DataObj {
     public:
     NonTermStr();
     NonTermStr(std::string name);
};

class NonTermInt : public DataObj {
    int NumericValue;
    public:
    NonTermInt(Node * numericValueNode);
    NonTermInt(std::string name);
    int GetNumericValue();
};

class NonTermB : public DataObj {
    public:
    static bool IsValidB(Node * node1);
    NonTermB();
    NonTermB(std::string name);
};

class NonTermByte : public DataObj {
    public:
    NonTermByte();
    NonTermByte(std::string name);
};

class IDNotExists : public DataObj {
    std::string name;
    public:
    IDNotExists();
    IDNotExists(std::string name);
};

class NonTermFunc : public DataObj {
    std::string name;
    public:
    NonTermFunc();
    NonTermFunc(std::string name);
};

class NonTermVoid : public DataObj {
    std::string name;
    public:
    NonTermVoid();
    NonTermVoid(std::string name);
};

bool IsItConstOrExistingSymbol(DataObj * dataObject);


#define YYSTYPE Node*

#endif