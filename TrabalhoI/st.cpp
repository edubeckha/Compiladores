#include "st.h"

using namespace ST;

extern SymbolTable symtab;

AST::Node* SymbolTable::newVariable(std::string id, AST::Tipo tipoVariavel, AST::Node* next){
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

AST::Tipo SymbolTable::returnType(std::string id){
    return entryList[id].type;
}

AST::Node* SymbolTable::newFunction(std::string id, AST::Tipo tipoVariavel, std::vector<AST::Variable*> parametros){
    // std::cout<<"Criando nova função"<<std::endl;
    if( checkId(id) )
        yyerror("Erro semantico: função %s já existe.\n", id.c_str());
    else {
    	// std::cout<<"criando simbolo"<<std::endl;
        Symbol entry(tipoVariavel, function, 0, false);
        addSymbol(id,entry);
    }
    return new AST::Funcao(id, tipoVariavel, parametros);
}

AST::Node* SymbolTable::assignFunction(std::string id, std::vector<AST::Variable*> next){
    // std::cout<<"Inicializando função"<<std::endl;
    if ( ! checkId(id) ) {
        yyerror("função ainda não definida! %s\n", id.c_str());
    }

    entryList[id].initialized = true;
    return new AST::DefineFuncao(id, next); //Creates variable node anyway
    // return new AST::Funcao(next); //Creates variable node anyway
}
