#include "st.h"

using namespace ST;

extern SymbolTable symtab;

AST::Node* SymbolTable::newVariable(std::string id, AST::Tipo tipoVariavel, AST::Node* next){
    std::cout<<"Criando nova variavel: "<< id << std::endl;
    if ( checkId(id) ) yyerror("Erro semantico: redefinicao da variavel %s\n", id.c_str());
    else {
      	Symbol entry(tipoVariavel, variable, 0, false);
    	addSymbol(id,entry);
    }
    return new AST::Variable(id, tipoVariavel, next); //Creates variable node anyway
}

AST::Node* SymbolTable::assignVariable(std::string id){
	std::cout<<"Inicializando variavel: "<< id << std::endl;
    if ( ! checkId(id) ) {yyerror("Variável ainda não definida! %s\n", id.c_str());}
    entryList[id].initialized = true;
    return new AST::Variable(id, entryList[id].type, NULL); //Creates variable node anyway
}

AST::Node* SymbolTable::useVariable(std::string id){
	std::cout<<"Usando variavel: "<< id << std::endl;
    if (  !checkId(id) ) {yyerror("Erro semantico: variavel %s ainda nao declarada.\n", id.c_str());}
    if (  !entryList[id].initialized ) {yyerror("Erro semantico: variavel %s ainda nao inicializada.\n", id.c_str());}
    return new AST::Variable(id, entryList[id].type, NULL); //Creates variable node anyway
}

AST::Tipo SymbolTable::returnType(std::string id){
    return entryList[id].type;
}
