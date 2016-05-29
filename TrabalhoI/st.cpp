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

/*Realiza a coersao de um tipo na tabela de simbolos*/
void SymbolTable::realizaCoercao(std::string id){
    if(!checkId(id)){
        return;
    }
    entryList[id].type = Tipos::real;
}

AST::Node* SymbolTable::newFunction(std::string id, Tipos::Tipo tipoVariavel, std::vector<ST::Symbol*> parametros){
    if( checkId(id) )
        yyerror("Erro semantico: função %s já existe.\n", id.c_str());
    else {
        Symbol entry(tipoVariavel, function, parametros, false);
        addSymbol(id,entry);
    }
    return NULL;
}

AST::Node* SymbolTable::assignFunction(std::string id, std::vector<ST::Symbol*> next, AST::Node* body){
    if ( ! checkId(id) ) {
        yyerror("função ainda não definida! %s\n", id.c_str());
    }
    ST::Symbol tmp = this->getFunction(id);
    for (int i = 0; i < next.size(); i++)
    {
    	if (tmp.parametros.at(i)->type != next.at(i)->type)
    	{
    		std::cout<<"Atenção: tipo de parametro incompativel."<<std::endl;
    	}
    }
    entryList[id].initialized = true;
    return NULL;
}
