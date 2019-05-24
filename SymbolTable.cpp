#include "SymbolTable.h"

SymbolTable::SymbolTable() : ScopesList(), CurrentScopeLevel(0) ,CurrentIndexInScope(0) {
    ScopesList.push_back(std::list<Symbol*>());
}

void SymbolTable::EnterScope() {
    ScopesList.push_back(std::list<Symbol*>());
}

bool SymbolTable::ExitScope() {
    for(std::list<Symbol*>::iterator it_scope = ScopesList.back().begin() ; 
                it_scope != ScopesList.back().end() ; it_scope++) {
                    delete (*it_scope);
                }
    ScopesList.pop_back();
}

int SymbolTable::getCurrentIndex(){
    return ScopesList.back().size();
}

void SymbolTable::AddSymbol(std::string name , int index , TypeNameEnum type){
    ScopesList.back().push_back(new Symbol(name,index,type));
}

TypeNameEnum SymbolTable::GetTypeOfSymbol(std::string name){
    for(std::list<std::list<Symbol*>>::iterator it_scopes = ScopesList.begin() ; 
        it_scopes != ScopesList.end() ; it_scopes++){
            for(std::list<Symbol*>::iterator it_scope = it_scopes->begin() ; 
                it_scope != it_scopes->end() ; it_scope++) {
                    if((*it_scope)->GetName() == name){
                        return (*it_scope)->GetType();
                    }
                }
        }
    return TYPE_NONE;
}




