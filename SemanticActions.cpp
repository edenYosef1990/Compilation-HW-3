#include "SemanticActions.h"
#include "output.hpp"



// FuncDecl -> RetType ID LPAREN Formals RPAREN PreConditions LBRACE Statements RBRACE

void CallToPreConditions(Node* node1 , Node* node2 , Node* node3 , Node* node4 , Node* node5 , Node* node6){
    output::printPreconditions((dynamic_cast<IdVal*>(node2))->GetVal(),(dynamic_cast<PreCondListObj*>(node6))->GetNumCond());
}
// PreConditions -> epsilon

Node* PreConditionsAction1() {
    return nullptr;
}

// PreConditions -> PreConditions PreCondition

Node* PreConditionsAction2(Node* node1 , Node* node2) {
    return new PreCondListObj(dynamic_cast<PreCondListObj*>(node1));
}

// Statment -> Type ID SC

void StatmentAction1(SymbolTable& symTable , Node* node1 , Node* node2, Node* node3){
    std::string name = (dynamic_cast<IdVal*>(node2))->IdStr;
        TypeNameEnum type = symTable.GetTypeOfSymbol(name);
        if(type != TYPE_NONEXIST){
            output::errorDef(yylineno,(dynamic_cast<IdVal*>(node2))->IdStr);
            yyerror("error!");
        }
        symTable.AddVariableSymbol(name , symTable.getCurrentIndex()+1 ,type);
}

// Statment -> Type ID ASSIGN Exp SC

void StatmentAction2(SymbolTable& symTable , Node* node1 , Node* node2, Node* node3, Node* node4, Node* node5){
    std::string name = (dynamic_cast<IdVal*>(node2))->IdStr;
        enum TypeNameEnum type = symTable.GetTypeOfSymbol((dynamic_cast<IdVal*>(node2))->IdStr);
        if(type != TYPE_NONEXIST){
            output::errorDef(yylineno,(dynamic_cast<IdVal*>(node2))->IdStr);
            yyerror("error!");
        }
        if(dynamic_cast<Type*>(node1)->name != dynamic_cast<DataObj*>(node4)->type){
            output::errorMismatch(yylineno);
            yyerror("error!");
        }
        symTable.AddVariableSymbol(name , symTable.getCurrentIndex()+1 ,type);
}

//Statment -> ID ASSIGN Exp SC
void StatmentAction3(SymbolTable& symTable , Node* node1 , Node* node2, Node* node3, Node* node4){
     enum TypeNameEnum type = symTable.GetTypeOfSymbol((dynamic_cast<IdVal*>(node1))->IdStr);
        if(type == TYPE_NONEXIST){
            output::errorUndef(yylineno, (dynamic_cast<IdVal*>(node1))->IdStr);
            yyerror("error!");
        }
        if(type != dynamic_cast<DataObj*>(node3)->type){
            output::errorMismatch(yylineno);
            yyerror("error!");
        }
}

//Statment -> BREAK

void StatmentAction4(int in_while_flag)
{if(in_while_flag<=0){
     output::errorUnexpectedBreak(yylineno);
     yyerror("error!");
    }
}


//ExpList -> Exp COMMA ExpList 

Node* ExpListAction1(Node* node1 , Node* node2 , Node* node3) {
        ParaListObj* paralist = dynamic_cast<ParaListObj*>(node3);
        TypeNameEnum type = ExpToFuncPara(node1);
        return new ParaListObj(paralist,type);
} 

//Exp

Node* ExpListAction2(Node* node1) { 
     return new ParaListObj(ExpToFuncPara(node1));
}


// Call -> ID LPAREN ExpList RPAREN

Node* CallAction1(SymbolTable& symTable , Node* node1 , Node* node2 , Node* node3 , Node* node4){
    Symbol * sym = symTable.GetSymbol((dynamic_cast<IdVal*>(node1))->IdStr);
        if(sym == nullptr || sym->GetType() != TYPE_FUNC ){
            output::errorUndefFunc(yylineno,(dynamic_cast<IdVal*>(node1))->IdStr);
            yyerror("error!");
        }
        std::list<TypeNameEnum> symParas = (dynamic_cast<FunctionSymbol*>(sym))->GetParametersList(); 
        std::list<TypeNameEnum> expListparas = (dynamic_cast<ParaListObj*>(node3))->GetParaList();
        std::vector<string> vector_symParas = ParaListToStrings(symParas);
        if(symParas != expListparas){
            output::errorPrototypeMismatch(yylineno,(dynamic_cast<IdVal*>(node1))->IdStr,vector_symParas);
            yyerror("error!");
        }
        return CallToExp(sym->GetType());
}

// Call -> ID LPAREN RPAREN

Node* CallAction2(SymbolTable& symTable , Node* node1 , Node* node2 , Node* node3){
    Symbol * sym = symTable.GetSymbol((dynamic_cast<IdVal*>(node1))->IdStr);
        if(sym == nullptr || sym->GetType() != TYPE_FUNC ){
            output::errorUndefFunc(yylineno,(dynamic_cast<IdVal*>(node1))->IdStr);
            yyerror("error!");
        }
        std::list<TypeNameEnum> symParas = (dynamic_cast<FunctionSymbol*>(sym))->GetParametersList(); 
        std::list<TypeNameEnum> expListparas = std::list<TypeNameEnum>();
        if(symParas != expListparas){
            std::vector<string> vector_symParas = ParaListToStrings(symParas);
            output::errorPrototypeMismatch(yylineno,(dynamic_cast<IdVal*>(node1))->IdStr,vector_symParas);
            yyerror("error!");
        }
        return CallToExp(sym->GetType());
}

// Exp -> LPAREN Exp RPAREN

Node* ExpAction1(Node* node1 , Node* node2 , Node* node3) {
    TypeNameEnum node1Type = ExpToFuncPara(node1);
    TypeNameEnum node2Type = ExpToFuncPara(node3);
    if((node1Type != TYPE_INT && node1Type != TYPE_BYTE)
        | (node2Type != TYPE_INT && node2Type != TYPE_BYTE) ){
            yyerror("error!");
        }
    return CallToExp(TYPE_BOOL);
}

// Exp -> Exp BINOP Exp

Node* ExpAction2(Node* node1 , Node* node2 , Node* node3){
    TypeNameEnum node1Type = ExpToFuncPara(node1);
    TypeNameEnum node2Type = ExpToFuncPara(node3);
    if((node1Type != TYPE_INT && node1Type != TYPE_BYTE)
        | (node2Type != TYPE_INT && node2Type != TYPE_BYTE) ){
            yyerror("error!");
        }
    if(node1Type==TYPE_INT | node2Type==TYPE_INT ){
        return CallToExp(TYPE_INT);
    }
    else{
        return CallToExp(TYPE_BYTE);
    }
}

// Exp -> ID

Node* ExpAction3(SymbolTable& symTable , Node* arg ){
    std::string name = (dynamic_cast<IdVal*>(yylval))->GetVal();
        Node* returnedNode = symbolNameToExp(symTable.GetTypeOfSymbol(name) , name);
        if(dynamic_cast<IDNotExists*>(returnedNode) != nullptr){
            yyerror("no such variable!");
        }
        else if(dynamic_cast<NonTermFunc*>(returnedNode) != nullptr){
            yyerror("this is the name of a function!");
        }
        return returnedNode;
}

// Exp -> Call

Node* ExpAction4(Node* node){
    TypeNameEnum type = ExpToFuncPara(node);
    return CallToExp(type);
}

// Exp -> NUM

Node* ExpAction5(Node* node){
    return new NonTermInt(node);
}

// Exp -> NUM B

Node* ExpAction6(Node* node1 , Node* node2){
    if( !IsItConstOrExistingSymbol(dynamic_cast<DataObj*>(node1)) && NonTermByte::IsValidByte(node2) )
        {
            yyerror("error!");
        }
    return new NonTermByte();
}

// Exp -> STRING

Node* ExpAction7(){
    return new NonTermStr();
}

// Exp -> TRUE

Node* ExpAction8(){
    return new NonTermBool();
}

// Exp -> FALSE

Node* ExpAction9(){
    return new NonTermBool();
}

// Exp -> Exp AND Exp

Node* ExpAction10(Node* node1 , Node* node2 , Node* node3){
    if(!(NonTermBool::IsValidBoolExp(node1,node2,node3)))
        {
             yyerror("error!");
        }
    return new NonTermBool();
}

// Exp -> Exp OR Exp

Node* ExpAction11(Node* node1 , Node* node2 , Node* node3){
    if(!(NonTermBool::IsValidBoolExp(node1,node2,node3)))
        {
             yyerror("error!");
        }
    return new NonTermBool();
}

// Exp -> Exp RELOP Exp

Node* ExpAction12(Node* node1 , Node* node2 , Node* node3){
    if(!(NonTermBool::IsValidBoolExp(node1,node2,node3)))
        {
             yyerror("error!");
        }
    return new NonTermBool();
}

// Exp -> NOT Exp

Node* ExpAction13(Node* node1 , Node* node2){
    if(!(NonTermBool::IsValidBoolExp(node2)))
        {
             yyerror("error!");
        }
    return new NonTermBool();
}

void CallToEnterScope(SymbolTable& symTable){
    symTable.EnterScope();
}

void CallToExitScope(SymbolTable& symTable){
    output::endScope();
    symTable.ExitScope();
}

