/*Ja previamente definido por Laércio Lima Pilla e ampliado para aceitar funcoes e outros tipos de estruturas*/
#include "st.h"
#include "ast.h"

using namespace ST;

extern SymbolTable symtab;

AST::Node * SymbolTable::newVariable ( std::string id, Tipos::Tipo tipoVariavel, AST::Node * next, bool inicializada  ) {
	AST::Variable * retorno = new AST::Variable ( id, tipoVariavel, next );

	if ( checkId ( id ) ) {
		yyerror ( "Erro semantico: redefinicao da variavel %s\n", id.c_str() );
		retorno->temErro ( true );

	}

	else {
	//std::cout << Tipos::tipoParaString(tipoVariavel, true) << std::endl;
		Symbol entry ( tipoVariavel, variable, 0, inicializada );
		addSymbol ( id, entry );
	}

	return retorno; //Creates variable node anyway
}
//////////
AST::Node * SymbolTable::assignVariable ( std::string id ) {
	if(!checkId(id)){
        if(tabelaOrigem != NULL){
            return tabelaOrigem->assignVariable(id);
           } else{
            yyerror("Variável ainda não definida! %s\n", id.c_str());
        }
    }
    entryList[id].initialized = true;
    return new AST::Variable(id, entryList[id].type, NULL); //Creates variable node anyway
}

AST::Node * SymbolTable::useVariable ( std::string id ) {
	AST::Variable * retorno;

	if ( !checkId ( id ) ) {
			if ( tabelaOrigem != NULL ) {
			return tabelaOrigem->useVariable ( id );

		} else {
			yyerror ( "Erro semantico: variavel %s ainda nao declarada.\n", id.c_str() );
		}

		AST::Variable * retErro = new AST::Variable ( id, entryList[id].type, NULL );
		retErro->temErro ( true );
		return retErro; //forca a criacao de um nodo
	}

	if ( !entryList[id].initialized && ! ( entryList[id].type == Tipos::complexo ) ) {
		yyerror ( "Erro semantico: variavel %s ainda nao inicializada.\n", id.c_str() );
		retorno = new AST::Variable ( id, entryList[id].type, NULL );
		retorno->temErro ( true );
	}

	return new AST::Variable ( id, entryList[id].type, NULL ); //Creates variable node anyway
}

/*Retorna o tipo de simbolo, passando um id como parametro*/
Tipos::Tipo SymbolTable::returnType ( std::string id ) {
	return entryList[id].type;
}

/*Realiza a coersao de um tipo na tabela de simbolos*/
void SymbolTable::realizaCoercao ( std::string id ) {
	if ( !checkId ( id ) ) {
		return;
	}

	entryList[id].type = Tipos::real;
}

/*Cria uma nova funcao na tabela de simbolos*/
AST::Node * SymbolTable::newFunction ( std::string id, Tipos::Tipo tipoVariavel, std::vector<AST::Variable *> parametros ) {
	if ( checkId ( id ) ) {
		yyerror ( "Erro semantico: função %s já existe.\n", id.c_str() );
	} else {
		Symbol entry ( tipoVariavel, funcao, parametros, false );
		addSymbol ( id, entry );
	}

	return new AST::Funcao(id, tipoVariavel, parametros);
}

/*Define o corpo da funcao e caso ela nao foi declarada, a mesma eh criada*/
AST::Node * SymbolTable::assignFunction ( std::string id, Tipos::Tipo tipoVariavel, std::vector<AST::Variable *> parametros, AST::Node * body ) {
	if ( ! checkId ( id ) ) {
		this->newFunction ( id, tipoVariavel, parametros );
	}
	ST::Symbol tmp = this->getFunction ( id );
	for ( int i = 0; i < parametros.size(); i++ ) {
		if ( tmp.parametros.at ( i )->tipo != parametros.at ( i )->tipo ) {
			std::cout << "Atenção: tipo de parametro incompativel. \n" << std::endl;
		}
	}
	entryList[id].initialized = true;
	return new AST::Funcao(id, tipoVariavel, parametros);
}

AST::Funcao* SymbolTable::useFunction (std::string id ){
	if ( !checkId ( id ) ) {
		if ( tabelaOrigem != NULL ) {
			return tabelaOrigem->useFunction ( id );
		} else {
			yyerror ( "Erro semantico: funcao %s ainda nao declarada.\n", id.c_str() );
		}
	}

	if(entryList[id].kind != funcao){
		yyerror ( "Erro semantico: %s nao representa uma funcao.\n", id.c_str() );
		//temErro = true
	}

	AST::Funcao* func = new AST::Funcao ( id, entryList[id].type, entryList[id].parametros );
	if ( !entryList[id].initialized ) {
		yyerror ( "Erro semantico: variavel %s ainda nao inicializada.\n", id.c_str() );
		//temErro = true
	}

	return  func; //Creates variable node anyway
}


Symbol SymbolTable::getSymbol ( std::string id ) {
	assert ( checkId ( id ) );
	ST::Symbol retorno = this->entryList.at ( id );
	return retorno;
}

AST::Classe* SymbolTable::newClass(std::string id, ST::SymbolTable* tabelaSimbolosClasse, AST::Block* escopoClasse, AST::ConstrutorClasse* construtor){

	if ( checkId ( id ) ) {
		yyerror ( "Erro semantico: ja existe uma classe com o nome %s\n", id.c_str() );
	}

	else {
		Symbol entry ( tabelaSimbolosClasse, construtor );
		addSymbol ( id, entry );
	}

	return new AST::Classe ( id, escopoClasse, tabelaSimbolosClasse, construtor );
}

AST::Classe* SymbolTable::useClass(std::string id){
	if(!checkId(id)){
		yyerror("Erro semantico: classe referida nao existe \n");
		return new AST::Classe(id, NULL);
	}

	ST::Symbol classe = this->entryList.at(id);
	
	if(classe.kind != ST::classe){
		yyerror("Erro semantico: objeto nao tenta referenciar uma classe \n");
	}

	AST::Classe* c  = new AST::Classe(id, NULL, classe.tabelaClasse, classe.construtor);

	return c;
}

AST::Objeto* SymbolTable::newObjeto(std::string id, AST::Classe* classePertencente){
	AST::Objeto* objeto = new AST::Objeto ( id, classePertencente );

	if ( checkId ( id ) ) {
		yyerror ( "Erro semantico: ja existe um objeto com o nome %s\n", id.c_str() );
	}
	else {
		Symbol entry ( classePertencente );
		addSymbol ( id, entry );
	}

	return objeto;
}

AST::Objeto* SymbolTable::useObjeto(std::string id){
	if(!checkId(id)){
		yyerror("Erro semantico: objeto nao existe \n");
	}

	ST::Symbol objeto = this->entryList.at(id);
	
	if(objeto.kind != ST::objeto){
		yyerror("Erro semantico: variavel nao e do tipo objeto \n");
		std::cout << std::endl;
	}

	AST::Objeto* c  = new AST::Objeto(id, objeto.classePertencente);
	return c;
}

/*Cria novo atributo de classe*/
AST::Atributo* SymbolTable::newAtributo(AST::Variable* var, AST::Classe* classePertencente){
	AST::Atributo* atri = new AST::Atributo ( var, classePertencente );

	if ( checkId ( var->id ) && this->entryList.at(var->id).kind == ST::atributo ) {
		yyerror ( "Erro semantico: ja existe um atributo com o nome %s\n", var->id.c_str() );
	}
	else {
		Symbol entry ( var, classePertencente );
		addSymbol ( var->id, entry );
	}
	return atri;
}

AST::Atributo* SymbolTable::assignAtributo ( AST::Variable* var, AST::Classe* classePertencente ){
	AST::Atributo * retorno = new AST::Atributo ( var, classePertencente );

	if ( !checkId ( var->id ) ) {
		yyerror ( "Atributo ainda não definida! %s\n", var->id.c_str() );
		retorno->temErro ( true );
	}

	classePertencente->tabelaSimbolos->entryList[var->id].initialized = true;
	return retorno;	//retorna o nodo de qualquer jeito
}

/*Usa atributo de classe*/
AST::Atributo* SymbolTable::useAtributo(std::string id){
	if(!checkId(id)){
		yyerror("Erro semantico: atributo nao existe \n");
	}

	ST::Symbol atributo = this->entryList.at(id);
	
	if(atributo.kind != ST::atributo){
		yyerror("Erro semantico: variavel nao e um atributo de classe \n");
		std::cout << std::endl;
	}

	AST::Atributo* a  = new AST::Atributo(atributo.var, atributo.classePertencente);

	return a;
}



