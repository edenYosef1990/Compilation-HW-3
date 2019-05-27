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
        Symbol(std::string _symbolName , int _symbolIndex , TypeNameEnum type) : SymbolName(_symbolName) , SymbolIndex(_symbolIndex) , Type(type) {
            
        }
        Symbol(const Symbol& Sym) = default;
        std::string GetName() {return SymbolName;}
        int GetIndex() {return SymbolIndex;}
        TypeNameEnum GetType() {return Type;}
        virtual ~Symbol() = default;
};

class VariableSymbol : public Symbol {
    public:
    VariableSymbol(std::string _symbolName , int _symbolIndex , TypeNameEnum type) : Symbol(_symbolName,_symbolIndex,type) {}
    VariableSymbol(const VariableSymbol& varSym) = default;
};

class FunctionSymbol : public Symbol {
    std::list<TypeNameEnum> ParametersList;
    TypeNameEnum RetType;
    public:
        FunctionSymbol(std::string _symbolName , int _symbolIndex , TypeNameEnum type , std::list<TypeNameEnum> parametersList , TypeNameEnum retType) : 
            Symbol(_symbolName,_symbolIndex,type) , ParametersList(parametersList) , RetType(retType) {}
        FunctionSymbol(const FunctionSymbol& varSym) = default;
        std::list<TypeNameEnum> GetParametersList() {return ParametersList;}
        TypeNameEnum GetRetType() {return RetType;}
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
        void AddVariableSymbol(std::string name , int index , TypeNameEnum type);
        void AddFuncSymbol(std::string name , int index , TypeNameEnum type , std::list<TypeNameEnum> parametersList , TypeNameEnum retType);
        //TypeNameEnum GetTypeOfSymbol(std::string name);
        Symbol* GetSymbol(std::string name);
        std::list<Symbol*> GetCurrentScope();
};

#endif