#include "st.h"

using namespace ST;

extern SymbolTable symtab;

AST::Node* SymbolTable::newVariable(std::string id, AST::Tipo tipoVariavel, AST::Node* next){
    if ( checkId(id) ) yyerror("Variable redefinition! %s\n", id.c_str());
    else {
    	std::cout<<"creating the symbol"<<std::endl;
    	Symbol entryint(inteiro, variable, 0, false);
    	addSymbol(id,entryint);
    	Symbol entryreal(real, variable, 0, false);
    	addSymbol(id,entryreal);
    	Symbol entrybool(booleano, variable, 0, false);
    	addSymbol(id,entrybool);
    	Symbol entryindef(indefinido, variable, 0, false);
    	addSymbol(id,entryindef);
    }
    return new AST::Variable(id, tipoVariavel, next); //Creates variable node anyway
}

AST::Node* SymbolTable::assignVariable(std::string id, AST::Tipo tipoVariavel){
	std::cout<<"assign variable"<<std::endl;
    if ( ! checkId(id) ) {yyerror("Variable not defined yet! %s\n", id.c_str());std::cout<<"thingsome"<<! checkId(id)<<std::endl;}
    entryList[id].initialized = true;
    return new AST::Variable(id, tipoVariavel, NULL); //Creates variable node anyway
}

AST::Node* SymbolTable::useVariable(std::string id, AST::Tipo tipoVariavel){
	std::cout<<"use variable"<<std::endl;
    if (  checkId(id) ) {yyerror("Variable not defined yet! %s\n", id.c_str());std::cout<<"something"<<std::endl;}
    if (  entryList[id].initialized ) {yyerror("Variable not initialized yet! %s\n", id.c_str());std::cout<<"blablabla "<<entryList[id].initialized<<std::endl;}
    return new AST::Variable(id, tipoVariavel, NULL); //Creates variable node anyway
}

