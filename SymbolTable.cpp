#include "SymbolTable.h"

SymbolTable::SymbolTable() : ScopesList(), CurrentScopeLevel(0) ,CurrentIndexInScope(0) {
    ScopesList.push_back(std::list<Symbol>());
}

void SymbolTable::EnterScope() {
    ScopesList.push_back(std::list<Symbol>());
}

bool SymbolTable::ExitScope() {
    ScopesList.pop_back();
}

int SymbolTable::getCurrentIndex(){
    return ScopesList.back().size();
}

void SymbolTable::AddSymbol(std::string name , int index){
    ScopesList.back().push_back(Symbol(name,index));
}

bool SymbolTable::IsSymbolExists(std::string name){
    for(std::list<std::list<Symbol>>::iterator it_scopes = ScopesList.begin() ; 
        it_scopes != ScopesList.end() ; it_scopes++){
            for(std::list<Symbol>::iterator it_scope = it_scopes->begin() ; 
                it_scope != it_scopes->end() ; it_scope++) {
                    if(it_scope->GetSymbolName() == name){
                        return true;
                    }
                }
        }
    return false;
}




