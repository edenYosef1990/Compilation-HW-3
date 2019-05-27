#include "SymbolTable.h"

SymbolTable::SymbolTable() : ScopesList(), CurrentScopeLevel(0) ,CurrentIndexInScope(0) {
    ScopesList.push_back(std::list<Symbol*>());
    std::list<TypeNameEnum> typesList1 = std::list<TypeNameEnum>();
    typesList1.push_back(TYPE_STR);
    AddFuncSymbol("print",0,TYPE_FUNC,typesList1,TYPE_VOID);
    std::list<TypeNameEnum> typesList2 = std::list<TypeNameEnum>();
    typesList2.push_back(TYPE_INT);
    AddFuncSymbol("printi",0,TYPE_FUNC,typesList2,TYPE_VOID);
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

void SymbolTable::AddVariableSymbol(std::string name , int index , TypeNameEnum type){
    ScopesList.back().push_back(new VariableSymbol(name,index,type));
}

void SymbolTable::AddFuncSymbol(std::string name , int index , TypeNameEnum type , std::list<TypeNameEnum> parametersList , TypeNameEnum retType){
    ScopesList.back().push_back(new FunctionSymbol(name,index,type,parametersList,retType));  // sould be changed for Functions!
}

Symbol* SymbolTable::GetSymbol(std::string name){
    for(std::list<std::list<Symbol*>>::iterator it_scopes = ScopesList.begin() ; 
        it_scopes != ScopesList.end() ; it_scopes++){
            for(std::list<Symbol*>::iterator it_scope = it_scopes->begin() ; 
                it_scope != it_scopes->end() ; it_scope++) {
                    if((*it_scope)->GetName() == name){
                        Symbol* ptr = (*it_scope);
                        if(dynamic_cast<VariableSymbol*>(ptr) != nullptr){
                            VariableSymbol * varPtr = dynamic_cast<VariableSymbol*>(ptr);
                            Symbol * copiedSymbolPtr = new VariableSymbol(*varPtr);
                            return copiedSymbolPtr; 
                        }
                        else if(dynamic_cast<FunctionSymbol*>(ptr) != nullptr){
                            FunctionSymbol * funcPtr = dynamic_cast<FunctionSymbol*>(ptr);
                            Symbol * copiedSymbolPtr = new FunctionSymbol(*funcPtr); 
                            return copiedSymbolPtr;
                        }
                    }
                }
        }
    return nullptr;
}

void SymbolTable::printTable(){
     for(std::list<std::list<Symbol*>>::iterator it_scopes = ScopesList.begin() ; 
        it_scopes != ScopesList.end() ; it_scopes++){
            for(std::list<Symbol*>::iterator it_scope = it_scopes->begin() ; 
                it_scope != it_scopes->end() ; it_scope++) {
                    std::cout << "symbol name: " << (*it_scope)->GetName() << std::endl;
                }
        }
}

std::list<Symbol*> SymbolTable::GetCurrentScope(){
    return ScopesList.back();
}




