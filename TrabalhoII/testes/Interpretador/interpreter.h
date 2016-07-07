
#ifndef INTERPRETER_H
#define INTERPRETER_H
//Global Includes
#include <map>
#include <cassert>
#include <string>
//Local Includes
#include "data.h"
#include "itree.h"
#include "st.h"
//Macro Definitions
#define _case(x) {x break;}
class Interpreter {

public:

	/**
	 * @brief Verifica se o identificador foi definido (Está na tabela de simbolos)
	 *
	 * @param id Identificador do nodo
	 * @return bool
	 */
	bool isDefined ( std::string id );


	/**
	 * @brief Verifica o tipo de nodo IT (Variavel, Funcao, Operacao...)
	 *
	 * @param id Identificador do nodo
	 * @return ITNode::NodeType
	 */
	ITNode::NodeType getITType ( std::string id );


	/**
	 * @brief Retorna uma resposta equivalente a execucao de um nodo.
	 * Se for uma operacao, a executa e retorna um valor se fizer sentido
	 *
	 * @param node Nodo a ser processado
	 * @return std::string
	 */
	std::string processNode ( ITNode * node );


	/**
	 * @brief Obtém o valor associado a um nodo
	 *
	 * @param node Nodo a ser analisado
	 * @return Data
	 */
	Data getNodeValue ( ITNode * node );


	/**
	 * @brief Adiciona um novo identificador na tabela de simbolos
	 *
	 * @param id Novo identificador a ser adicionado
	 * @param node Nodo associado a este identificador
	 * @return void
	 */
	void addId ( std::string id, ITNode * node );

private:
	/**
	 * @brief Processa o valor de um nodo, realizando todas as operacoes da arvore deste nodo.
	 *
	 * @param node Nodo raiz da arvore ou subarvore
	 * @return Data
	 */
	Data processNodeValue ( ITNode * node );
	/**
	 * @brief Tabela interna de símbolos
	 *
	 */
	std::map<std::string, ITNode *> _idTable;



//	ST::SymbolTable * _currentSyntab; // Não tenho usado isso.

};

#endif


