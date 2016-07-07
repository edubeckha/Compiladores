#include <iostream>
#include "itree.h"
#include "interpreter.h"
#define print(x) std::cout << (x) << std::endl;

int main () {
	print ( "Comecando teste do intepretador!" );
	Interpreter i;

	ITNode * um = ITNode::createValue ( Data ( 1 ) );
	ITNode * dois = ITNode::createValue ( Data ( 2 ) );
	ITNode * soma1 = ITNode::createBinOp ( ITNode::sum, dois, um );



	ITNode * soma2 = ITNode::createBinOp ( ITNode::sum, dois, soma1 );

	ITNode * varA = ITNode::createVar ( "a" );
	ITNode * varDefA = ITNode::createDefVar ( "a", Data::integer );
	ITNode * def = ITNode::createDef ( varDefA );




	print ( i.processNode ( soma2 ) );


	return 0;


}

