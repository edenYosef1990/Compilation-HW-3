#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "attributes.h"
#include "list"
#include "string"
#include "typeEnums.h"

using namespace std;

class Symbol {
    std::string SymbolName;
    int SymbolIndex; 
    TypeNameEnum Type;
    public:
        Symbol(std::string _symbolName , int _symbolIndex , TypeNameEnum type) : SymbolName(_symbolName) , SymbolIndex(_symbolIndex) , Type(type) {}
        std::string GetName() {return SymbolName;}
        int GetIndex() {return SymbolIndex;}
        TypeNameEnum GetType() {return Type;}
        ~Symbol() = default;
};

class VariableSymbol : public Symbol {
    public:
    VariableSymbol(std::string _symbolName , int _symbolIndex , TypeNameEnum type) : Symbol(_symbolName,_symbolIndex,type) {}
};

class FunctionSymbol : public Symbol {
    std::list<TypeNameEnum> ParametersList;
    TypeNameEnum RetType;
    public:
        FunctionSymbol(std::string _symbolName , int _symbolIndex , TypeNameEnum type , std::list<TypeNameEnum> parametersList , TypeNameEnum retType) : 
            Symbol(_symbolName,_symbolIndex,type) , ParametersList(parametersList) , RetType(retType) {}
};

class SymbolTable {
    std::list<std::list<Symbol*>> ScopesList;
    int CurrentScopeLevel;
    int CurrentIndexInScope;
    public:
        SymbolTable();
        void EnterScope();
        bool ExitScope();
        int getCurrentIndex();
        void AddSymbol(std::string name , int index , TypeNameEnum type);
        TypeNameEnum GetTypeOfSymbol(std::string name);
};

#endif