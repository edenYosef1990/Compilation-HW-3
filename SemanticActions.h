#ifndef SEMANTIC_ACTIONS_H
#define SEMANTIC_ACTIONS_H

#include "attributes.h"
#include "SymbolTable.h"

extern int yylineno;
extern Node* yylval;

// FuncDecl -> RetType ID LPAREN Formals RPAREN PreConditions LBRACE Statements RBRACE
void CallToPreConditions(Node* node1 , Node* node2 , Node* node3 , Node* node4 , Node* node5 , Node* node6);
// PreConditions -> epsilon
Node* PreConditionsAction1();
// PreConditions -> PreConditions PreCondition
Node* PreConditionsAction2(Node* node1 , Node* node2);
// Statment -> Type ID SC
void StatmentAction1(SymbolTable& symTable , Node* node1 , Node* node2, Node* node3);
// Statment -> Type ID ASSIGN Exp SC
void StatmentAction2(SymbolTable& symTable , Node* node1 , Node* node2, Node* node3, Node* node4, Node* node5);
//Statment -> ID ASSIGN Exp SC
void StatmentAction3(SymbolTable& symTable , Node* node1 , Node* node2, Node* node3, Node* node4);
//Statment -> BREAK
void StatmentAction4(int in_while_flag);
// Call -> ID LPAREN ExpList RPAREN
Node* CallAction1(SymbolTable& symTable , Node* node1 , Node* node2 , Node* node3 , Node* node4);
// Call -> ID LPAREN RPAREN
Node* CallAction2(SymbolTable& symTable , Node* node1 , Node* node2 , Node* node3);
//ExpList -> Exp COMMA ExpList 
Node* ExpListAction1(Node* node1 , Node* node2 , Node* node3);
//Exp  -> Exp
Node* ExpListAction2(Node* node1);
// Exp -> LPAREN Exp RPAREN
Node* ExpAction1(Node* node1 , Node* node2 , Node* node3);
// Exp -> Exp BINOP Exp
Node* ExpAction2(Node* node1 , Node* node2 , Node* node3);
// Exp -> ID
Node* ExpAction3(SymbolTable& symTable , Node* arg );
// Exp -> Call
Node* ExpAction4(Node* node);
// Exp -> NUM
Node* ExpAction5(Node* node);
// Exp -> NUM B
Node* ExpAction6(Node* node1 , Node* node2);
// Exp -> STRING
Node* ExpAction7();
// Exp -> TRUE
Node* ExpAction8();
// Exp -> FALSE
Node* ExpAction9();
// Exp -> Exp AND Exp
Node* ExpAction10(Node* node1 , Node* node2 , Node* node3);
// Exp -> Exp OR Exp
Node* ExpAction11(Node* node1 , Node* node2 , Node* node3);
// Exp -> Exp RELOP Exp
Node* ExpAction12(Node* node1 , Node* node2 , Node* node3);
// Exp -> NOT Exp
Node* ExpAction13(Node* node1 , Node* node2);

void CallToEnterScope(SymbolTable& symTable);

void CallToExitScope(SymbolTable& symTable);

#endif