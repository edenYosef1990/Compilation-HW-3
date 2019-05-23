#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "attributes.h"
#include "list"
#include "string"

using namespace std;

class Symbol {
    std::string SymbolName;
    int SymbolIndex; 
    public:
        Symbol(std::string _symbolName , int _symbolIndex) : SymbolName(_symbolName) , SymbolIndex(_symbolIndex) {}
        std::string GetSymbolName() {return SymbolName;}
        int GetSymbolIndex() {return SymbolIndex;}
    
};

class SymbolTable {
    std::list<std::list<Symbol>> ScopesList;
    int CurrentScopeLevel;
    int CurrentIndexInScope;
    public:
        SymbolTable();
        void EnterScope();
        bool ExitScope();
        int getCurrentIndex();
        void AddSymbol(std::string name , int index);
        bool SymbolTable::IsSymbolExists(std::string name);
};

#endif