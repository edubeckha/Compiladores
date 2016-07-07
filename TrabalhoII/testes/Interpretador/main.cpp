#include <iostream>
#include "itree.h"
#include "interpreter.h"
#define print(x) std::cout << (x) << std::endl;

int main () {
	print ( "Comecando teste do intepretador!" );
	Interpreter i;
	ITNode * um = ITNode::createValue ( Data ( 1 ) );
	ITNode * dois = ITNode::createValue ( Data ( 2 ) );
	ITNode * soma12 = ITNode::createBinOp ( ITNode::sum, dois, um );
	std::cout << i.processNode ( soma12 );
	return 0;


}

