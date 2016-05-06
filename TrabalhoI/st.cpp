#include "st.h"

using namespace ST;

extern SymbolTable symtab;

AST::Node* SymbolTable::newVariable(std::string id, AST::Tipo tipoVariavel, AST::Node* next){
    if ( checkId(id) ) yyerror("Redefinição de variável! %s\n", id.c_str());
    else {
    	std::cout<<"creating the symbol"<<std::endl;
    	Symbol entry(tipoVariavel, variable, 0, false);
    	addSymbol(id,entry);
    }
    std::cout << "Novo simbolo criado: " << id << " com tipo " << tipoVariavel << std::endl;
    return new AST::Variable(id, tipoVariavel, next); //Creates variable node anyway
}

AST::Node* SymbolTable::assignVariable(std::string id){
	std::cout<<"assign variable"<<std::endl;
    if ( ! checkId(id) ) {yyerror("Variável ainda não definida! %s\n", id.c_str());}
    entryList[id].initialized = true;
    return new AST::Variable(id, entryList[id].type, NULL); //Creates variable node anyway
}

AST::Node* SymbolTable::useVariable(std::string id){
	std::cout<<"use variable"<<std::endl;
    if (  checkId(id) ) {yyerror("Variable not defined yet! %s\n", id.c_str());std::cout<<"something"<<std::endl;}
    if (  entryList[id].initialized ) {yyerror("Variable not initialized yet! %s\n", id.c_str());std::cout<<"blablabla "<<entryList[id].initialized<<std::endl;}
    return new AST::Variable(id, entryList[id].type, NULL); //Creates variable node anyway
}

