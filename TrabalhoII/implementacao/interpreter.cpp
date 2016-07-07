#include "interpreter.h"
typedef ITNode::OperationType optype;
//////////
bool intepreter::isDefined ( std::string id ) {
	return _idTable.find ( id )  != _idTable.end();
}
//////////
ITNode::NodeType intepreter::getITType ( std::string id ) {
	ITNode	* aNode =  _idTable.at ( id );
	ITNode::NodeType tipoNodo = aNode->getType();
	return tipoNodo;

}
//////////
Data intepreter::processNodeValue ( ITNode * node ) {
	switch ( node->getType() ) {
		case ITNode::atrib:
			_case ( return processNodeValue ( node->_rightSon ); );

		case ITNode::binOp: {
			assert ( node->_leftSon != nullptr );
			assert ( node->_rightSon != nullptr );

			switch ( node->getOpType() ) {
				case ITNode::sum: {
					Data vNodeL = processNodeValue ( node->_leftSon );
					Data vNodeR = processNodeValue ( node->_rightSon );
					return vNodeL.sum ( & vNodeR );
					break;
				}

				case ITNode::min: {
					Data vNodeL = processNodeValue ( node->_leftSon );
					Data vNodeR = processNodeValue ( node->_rightSon );
					return vNodeL.subtrair ( & vNodeR );
					break;
				}

				case ITNode::mult: {
					Data vNodeL = processNodeValue ( node->_leftSon );
					Data vNodeR = processNodeValue ( node->_rightSon );
					return vNodeL.multiply ( &vNodeR );
					break;
				}

				case ITNode::div: {
					Data vNodeL = processNodeValue ( node->_leftSon );
					Data vNodeR = processNodeValue ( node->_rightSon );
					return vNodeL.divide ( &vNodeR );
					break;
				}

				case ITNode::band: {
					Data vNodeL = processNodeValue ( node->_leftSon );
					Data vNodeR = processNodeValue ( node->_rightSon );
					return vNodeL.bAnd ( &vNodeR );
					break;
				}

				case ITNode::bor: {
					Data vNodeL = processNodeValue ( node->_leftSon );
					Data vNodeR = processNodeValue ( node->_rightSon );
					return vNodeL.bOr ( & vNodeR );
					break;
				}

				case ITNode::eq: {
					Data vNodeL = processNodeValue ( node->_leftSon );
					Data vNodeR = processNodeValue ( node->_rightSon );


					break;
				}
			}//switch op

			break; // break binOp
		}

		case ITNode::function:
			_case ( return Data ( 666 ); );

		case ITNode::value:
			_case (
			 return node->getData();
			);

		case ITNode::variable:

			_case (
			 assert ( isDefined ( node->getId() ) );
			 return this->_idTable.at ( node->getId() )->getData();
			);

		case ITNode::def:
			_case (
			 return node->_leftSon->getData();
			);
	}
}
//////////
std::string intepreter::processNode ( ITNode * node ) {
	switch ( node->getType() ) {
		case ITNode::atrib:
			_case (
			 assert ( node->_leftSon->getType() == ITNode::variable );
			 assert ( isDefined ( node->_leftSon->getId() ) );
			 std::string id = node->_leftSon->getId();
			 ITNode * aNode = _idTable.at ( id );
			 Data newData = processNodeValue ( node->_rightSon );
			 assert ( aNode->getData().type() == newData.type() );
			 aNode->updateData ( newData );
			 return "";

			);

		case ITNode::binOp:
			_case (
			 node->updateData ( processNodeValue ( node ) );
			 return node->getData().toString();
			);

		case ITNode::function:
			_case (
			 return "FUNCAO NAO IMPLEMENTADA!\n";
			);

		case ITNode::value:
			_case (
			 return node->getData().toString();
			);

		case ITNode::variable:
			_case (
			 assert ( isDefined ( node->getId() ) );
			 return _idTable.at ( node->getId() )->getData().toString();
			);

		case ITNode::def://Ainda não pensei como fazer com casos do tipo "int a, b,c ;"
			_case (
			 std::string newId = node->_leftSon->getId();
			 assert ( ! ( isDefined ( newId ) ) );
			 addId ( newId, node->_leftSon );
			 return ""; //Definição de variavel nao imprime nada!
			);
	}
}

//////////
void intepreter::addId ( std::string id, ITNode * node ) {
	assert ( ! ( isDefined ( id ) ) );
	this->_idTable.insert ( std::pair<std::string, ITNode *> ( id, node ) );
}

/*Sessão escrotissima de templates
//Swich no tipo de nodo---------------------
switch ( node->getType() ) {
case ITNode::atrib:
	_case();

case ITNode::binOp:
	_case();

case ITNode::function:
	_case();

case ITNode::value:
	_case();

case ITNode::variable:
	_case();
}
}
--------------------------------------------
Switch de tipo de operacao
switch ( node->getOpType() ) {
				case ITNode::sum: {
					break;
				}

				case ITNode::min: {
					break;
				}

				case ITNode::mult: {
					break;
				}

				case ITNode::div: {
					break;
				}

				case ITNode::band: {
					break;
				}

				case ITNode::bor: {

				}
			}//switch op
--------------------------------------------

*/

