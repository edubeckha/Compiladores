/*Ja previamente definido por Laércio Lima Pilla*/
#include "st.h"

using namespace ST;

extern SymbolTable symtab;

AST::Node* SymbolTable::newVariable(std::string id, Tipos::Tipo tipoVariavel, AST::Node* next){
    if ( checkId(id) ) yyerror("Erro semantico: redefinicao da variavel %s\n", id.c_str());
    else {
      	Symbol entry(tipoVariavel, variable, 0, false);
    	addSymbol(id,entry);
    }
        return new AST::Variable(id, tipoVariavel, next); //Creates variable node anyway
}

AST::Node* SymbolTable::assignVariable(std::string id){
    if ( ! checkId(id) ) {yyerror("Variável ainda não definida! %s\n", id.c_str());}
    entryList[id].initialized = true;
    return new AST::Variable(id, entryList[id].type, NULL); //Creates variable node anyway
}

AST::Node* SymbolTable::useVariable(std::string id){
    if (  !checkId(id) ) {yyerror("Erro semantico: variavel %s ainda nao declarada.\n", id.c_str());}
    if (  !entryList[id].initialized ) {yyerror("Erro semantico: variavel %s ainda nao inicializada.\n", id.c_str());}
    return new AST::Variable(id, entryList[id].type, NULL); //Creates variable node anyway
}

Tipos::Tipo SymbolTable::returnType(std::string id){
    return entryList[id].type;
}

void SymbolTable::realizaCoercao(std::string id){
    entryList[id].type = Tipos::real;
}

//int:i; real[10]:ar; i:=1; while i <= 10 do ar[1]:= 0.0; i := i + 1; end while -> v1.4