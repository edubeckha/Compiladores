/*
 * Copyright (c) 2016 <copyright holder> <email>
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#ifndef ITREE_H
#define ITREE_H
//Local Includes
#include "data.h"
#include <string>






class ITNode {
public:

	/**
	 * @brief Tipos de nodos
	 *
	 */
	enum NodeType {variable, binOp, atrib, def, value, function};//Gonna grow!
//--------------------------------------------------
	/**
	 * @brief Tipos de operacao
	 *
	 */
	enum OperationType {sum, min, mult, div, band, bor, eq};
//--------------------------------------------------
	/**
	 * @brief Construtor Default
	 *
	 */
	ITNode();
//--------------------------------------------------
	/**
	 * @brief Retorna o tipo do nodo
	 *
	 * @return ITNode::NodeType
	 */
	NodeType getType();
//--------------------------------------------------
	/**
	 * @brief Obtém o Identificador
	 *
	 * @return std::string
	 */
	std::string getId();
//--------------------------------------------------
	/**
	 * @brief Obtém o tipo de operacao
	 *
	 * @return ITNode::OperationType
	 */
	OperationType getOpType();
//--------------------------------------------------
	/**
	 * @brief Obtém o dado associado ao nodo
	 *
	 * @return Data
	 */
	Data getData();
//--------------------------------------------------
	/**
	 * @brief Atualiza o valor do nodo
	 *
	 * @param newData Novo valor
	 * @return void
	 */
	void updateData ( Data newData );
//--------------------------------------------------
	/**
	 * @brief Cria um nodo de operacao binaria
	 *
	 * @param operation Obperacao a ser executada
	 * @param leftSon Filho a esquerda do nodo
	 * @param rightSon Filho a direita do nodo
	 * @return ITNode*
	 */
	static ITNode * createBinOp ( OperationType operation, ITNode * leftSon, ITNode * rightSon );
//--------------------------------------------------
	/**
	 * @brief Cria um nodo tipo variável, somente com seu identificador
	 *
	 * @param id Identificador da variavel
	 * @return ITNode*
	 */
	static ITNode * createVar ( std::string id );
//--------------------------------------------------
	/**
	 * @brief Cria um nodo tipo valor, com o valor associado
	 *
	 * @param valor Valor associado ao nodo
	 * @return ITNode*
	 */
	static ITNode * createValue ( Data valor );
//--------------------------------------------------



	ITNode * _leftSon = nullptr;//Filho a esquerda
	ITNode * _rightSon = nullptr;//Filho a direita
	ITNode * _parent = nullptr;//Nodo pai



private:
	std::string _id;//Identificador do nodo, caso seja variavel ou funcao
	Data _value;//Valor de interpretação do nodo.
	NodeType _type;//Tipo do nodo
	OperationType _opType;//Tipo de operacao do nodo (se for alguma operacao);


};


#endif // ITREE_H
