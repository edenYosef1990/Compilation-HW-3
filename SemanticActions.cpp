#include "SemanticActions.h"
#include "output.hpp"




// RetType -> TYPE 

Node * RetTypeAction1(Node * node1){
    return node1;
}

// RetType -> VOID 

Node * RetTypeAction2(){
    return new Type(TYPE_VOID);
}

// Formals -> epsilon

Node * FormalsAction1(){
    return new ParaListObj();
}

// Formals -> FormalsList

Node * FormalsAction2(Node * node1){
    return node1;
}

//FormalsList -> FormalDecl

Node * FormalsListAction1(Node * node1){
    return node1;
}

//FormalsList ->  FormalDecl COMMA FormalsList

Node * FormalsListAction2(Node * node1 , Node * node2 , Node * node3){
    ParaListObj* list1 = dynamic_cast<ParaListObj*>(node1);
    ParaListObj* list3 = dynamic_cast<ParaListObj*>(node3);
    return new ParaListObj(list3,list1);
}

//FormalDecl -> Type ID

Node * FormalDeclAction1(SymbolTable& symTable , Node * node1 , Node * node2){
    TypeNameEnum type = TypeNameToTypeEnum(node1);
    std::string name = (dynamic_cast<IdVal*>(node2))->GetVal();
    Node* returnedNode = symbolNameToExp(symTable.GetTypeOfSymbol(name) , name);
    if(dynamic_cast<IDNotExists*>(returnedNode) == nullptr){
        output::errorDef(yylineno,name);
        yyerror("error!");
    }
    symTable.AddVariableSymbol(name , symTable.getCurrentIndex()+1 ,type);
    return new ParaListObj(type);
}
// PreConditions -> epsilon

Node* PreConditionsAction1() {
    return nullptr;
}

// PreConditions -> PreConditions PreCondition

Node* PreConditionsAction2(Node* node1 , Node* node2) {
    std::cout << std::endl << "here3" << std::endl;
    return new PreCondListObj(dynamic_cast<PreCondListObj*>(node1));
}

//PreCondition -> PRECOND LPAREN Exp RPAREN

void PreConditionAction1(Node* node1 , Node* node2 , Node* node3 , Node* node4) {
    TypeNameEnum type = ExpToFuncPara(node3);
    if(type!=TYPE_BOOL){
        output::errorMismatch(yylineno);
        yyerror("");
    }
}
//Statment -> Type ID SC

void StatmentAction1(SymbolTable& symTable , Node* node1 , Node* node2, Node* node3){
    std::string name = (dynamic_cast<IdVal*>(node2))->IdStr;
        TypeNameEnum type = symTable.GetTypeOfSymbol(name);
        if(type != TYPE_NONEXIST){
            output::errorDef(yylineno,(dynamic_cast<IdVal*>(node2))->IdStr); // already exists in the symbol table
            yyerror("");
        }
        type = TypeNameToTypeEnum(node1);
        symTable.AddVariableSymbol(name , symTable.getCurrentIndex()+1 ,type);
}

//Statment -> Type ID ASSIGN Exp SC

void StatmentAction2(SymbolTable& symTable , Node* node1 , Node* node2, Node* node3, Node* node4, Node* node5){
    std::string name = (dynamic_cast<IdVal*>(node2))->IdStr;
        enum TypeNameEnum type = symTable.GetTypeOfSymbol((dynamic_cast<IdVal*>(node2))->IdStr);
        if(type != TYPE_NONEXIST){
            output::errorDef(yylineno,(dynamic_cast<IdVal*>(node2))->IdStr); // alrady exists in the symbol table
            yyerror("");
        }
        if(dynamic_cast<Type*>(node1)->name != dynamic_cast<DataObj*>(node4)->type){ // mismatch
            output::errorMismatch(yylineno);
            yyerror("");
        }
        type = TypeNameToTypeEnum(node1);
        symTable.AddVariableSymbol(name , symTable.getCurrentIndex()+1 ,type);
}

//Statment -> ID ASSIGN Exp SC
void StatmentAction3(SymbolTable& symTable , Node* node1 , Node* node2, Node* node3, Node* node4){
     enum TypeNameEnum type = symTable.GetTypeOfSymbol((dynamic_cast<IdVal*>(node1))->IdStr);
        if(type == TYPE_NONEXIST){
            output::errorUndef(yylineno, (dynamic_cast<IdVal*>(node1))->IdStr); // not exists in the symbol table
            yyerror("error!");
        }
        if(type != dynamic_cast<DataObj*>(node3)->type){ // mismatch
            output::errorMismatch(yylineno);
            yyerror("error!");
        }
}

//Statment -> BREAK SC 

void StatmentAction4(int in_while_flag)
{if(in_while_flag<=0){
     output::errorUnexpectedBreak(yylineno);
     yyerror("error!");
    }
}

//Statment -> CONTINUE SC

void StatmentAction5(int in_while_flag)
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

// Type -> INT

Node* TypeAction1(){
    return new Type(TYPE_INT);
}

// Type -> BYTE

Node* TypeAction2(){
    return new Type(TYPE_BYTE);
}

// Type -> BOOL

Node* TypeAction3(){
    return new Type(TYPE_BOOL);
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

//=================================== Handling Home Work's Special Functions ===============================================

void CallToEnterScope(SymbolTable& symTable){
    symTable.EnterScope();
}

void CallToExitScope(SymbolTable& symTable){
    output::endScope();
    CallToPrintIDsInScope(symTable);
    symTable.ExitScope();
}

void CallToExitScope(SymbolTable& symTable , Node* paraList){
    output::endScope();
    CallToPrintIDsInScope(symTable,paraList);
    symTable.ExitScope();
}


void EnterWhile(int &in_while_flag) {
    in_while_flag++;
}

void ExitWhile(int &in_while_flag) {
    in_while_flag--;
}

// Assoiated with : FuncDecl -> RetType ID <MARKER> LPAREN Formals RPAREN PreConditions LBRACE Statements RBRACE

void CallToPreConditions(Node* node1 , Node* node2 , Node* node3 , Node* node4 , Node* node5 , Node* node6 , Node* node7){
    std::string name = (dynamic_cast<IdVal*>(node2))->GetVal();
    int num = (node7 != nullptr) ? (dynamic_cast<PreCondListObj*>(node7))->GetNumCond() : 0;
    output::printPreconditions(name,num);
}

void CallToPrintIDsInScope(SymbolTable& symTable , Node * paraList){
    ParaListObj* list = dynamic_cast<ParaListObj*>(paraList);
    int numParas = list->GetParaListSize();
    std::list<Symbol*> IDList = symTable.GetCurrentScope();
    int i=0;
    int j=0;
    for(std::list<Symbol*>::iterator it_scope = IDList.begin() ; 
        it_scope != IDList.end() ; it_scope++){
            if(i<numParas){
                j--;
                output::printID((*it_scope)->GetName(),j,TypeToString((*it_scope)->GetType()));
                i++;
            }
            else if(i=numParas){
                j=0;
                output::printID((*it_scope)->GetName(),j,TypeToString((*it_scope)->GetType()));
                i++;
            }
            else{
                j++;
                output::printID((*it_scope)->GetName(),j,TypeToString((*it_scope)->GetType()));
            }
        }

}

void CallToPrintIDsInScope(SymbolTable& symTable){
    std::list<Symbol*> IDList = symTable.GetCurrentScope();
    for(std::list<Symbol*>::iterator it_scope = IDList.begin() ; 
        it_scope != IDList.end() ; it_scope++){
            output::printID((*it_scope)->GetName(),(*it_scope)->GetIndex(),TypeToString((*it_scope)->GetType()));
        }
}

