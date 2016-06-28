
#ifndef INTERPRETER_H
#define INTERPRETER_H
//Global Includes
#include <map>
//Local Includes
#include "data.h"
#include "itree.h"
#include "st.h"
//Macro Definitions
#define _case(x) {x break;}
class intepreter {

public:
	/*Verifica se o identificador foi definido*/
	bool isDefined ( std::string id );
	/*Verifica o tipo de nodo IT (Variavel, Funcao, Operacao...)*/
	ITNode::NodeType getITType ( std::string id );
	/*Retorna uma resposta equivalente a execucao de um nodo.
	 Se for uma operacao, a executa e retorna um valor se fizer sentido.*/
	std::string processNode ( ITNode * node );
	/*Retorna o valor de um nodo*/
	Data getNodeValue ( ITNode * node );

private:
	std::map<std::string, ITNode *> _idTable;
	ST::SymbolTable * _currentSyntab;

};

bool intepreter::isDefined ( std::string id ) {
	return _currentSyntab->checkId ( id );
}

ITNode::NodeType intepreter::getITType ( std::string id ) {
	ITNode	* _idTable.at ( id );

}


#endif

