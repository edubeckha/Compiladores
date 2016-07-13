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

#include "itree.h"
//--------------------------------------------------
ITNode::ITNode() : _value ( Data ( 666 ) ) {
	//_value = Data ( 666 );//Valor padrão - bem definido pra saber onde deu erro;
}

//--------------------------------------------------
ITNode::NodeType ITNode::getType() {
	return _type;
}

//--------------------------------------------------
std::string ITNode::getId() {
	return _id;
}
//--------------------------------------------------
ITNode::OperationType ITNode::getOpType() {
	return _opType;
}
//--------------------------------------------------
Data ITNode::getData() {
	return _value;
}
//--------------------------------------------------
void ITNode::updateData ( Data newData ) {
	this->_value = newData;
}
//--------------------------------------------------
ITNode * ITNode::createBinOp ( ITNode::OperationType operation, ITNode * leftSon, ITNode * rightSon ) {
	ITNode  * newNode = new ITNode;
	newNode->_leftSon = leftSon;
	newNode->_rightSon = rightSon;
	newNode->_type = ITNode::binOp;
	newNode->_opType = operation;
	return newNode;
}
//--------------------------------------------------
ITNode * ITNode::createValue ( Data valor ) {
	ITNode * newNode = new ITNode;
	newNode->_type = ITNode::value;
	newNode->_value = Data ( valor );
	return newNode;

}
//--------------------------------------------------
ITNode * ITNode::createVar ( std::string id ) {
	ITNode * newNode = new ITNode;
	newNode->_id = std::string ( id );
	newNode->_type = ITNode::variable;
	return newNode;

}
//--------------------------------------------------
ITNode * ITNode::createDefVar ( std::string id, Data::DataType tipo ) {
	ITNode * newNode = new ITNode;
	newNode->_id = id;
	newNode->_value = Data::createDefault ( tipo );
	newNode->_type = ITNode::variable;
	return newNode;
}
//--------------------------------------------------

ITNode * ITNode::createDef ( ITNode * leftSon ) {
	ITNode * newNode = new ITNode;
	newNode->_leftSon = leftSon;
	newNode->_type = ITNode::def;
	return newNode;

}
//--------------------------------------------------
ITNode * ITNode::createAtrib ( ITNode * leftSon, ITNode * rightSon ) {
	ITNode * newNode = new ITNode;
	newNode->_leftSon = leftSon;
	newNode->_rightSon = rightSon;
	newNode->_type = ITNode::atrib;
	return newNode;
}
//--------------------------------------------------






