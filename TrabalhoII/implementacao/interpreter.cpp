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

			break; // break binOp
		}

		case ITNode::function:
			_case();

		case ITNode::value:
			_case();

		case ITNode::variable:
			_case();
	}
}
//////////
std::string intepreter::processNode ( ITNode * node ) {
	switch ( node->getType() ) {
		case ITNode::atrib:
			_case (
			 assert ( node->_leftSon->getType() == ITNode::variable );
			 assert ( isDefined ( node->_leftSon->getId() ) );

			);

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
