#include <iostream>
#include "itree.h"
#include "interpreter.h"
#define print(x) std::cout << (x) << std::endl;

int main () {
	print ( "Comecando teste do intepretador!" );
	Interpreter i;

	ITNode * um = ITNode::createValue ( Data ( (float)1.5 ) );
	ITNode * dois = ITNode::createValue ( Data ( 2 ) );
	ITNode * soma1 = ITNode::createBinOp ( ITNode::sum, dois, um );



	ITNode * soma2 = ITNode::createBinOp ( ITNode::sum, dois, soma1 );

	//Variavel a
	ITNode * varA = ITNode::createVar ( "a" );

	//Define a variavel a
	ITNode * varDefA = ITNode::createDefVar ( "a", Data::integer );
	ITNode * def = ITNode::createDef ( varDefA );

	//Atribui o valor de soma2 a "a"
	ITNode * atribA = ITNode::createAtrib ( varA, soma2 );



	print ( "Resultado da soma2: " )
	print ( i.processNode ( soma2 ) );
	print ( "Definicao da variavel inteira 'a'" );
	print ( i.processNode ( def ) );
	print (	"Atribuicao da soma a variavel a" );
	print ( i.processNode ( atribA ) );
	print ( "Valor da variavel a: " ) ;
	print ( i.processNode ( varA ) );

	soma2 = ITNode::createBinOp ( ITNode::mult, soma1, soma1 );
	atribA = ITNode::createAtrib ( varA, soma2 );

	print (	"Atribuicao da multiplicacao a variavel a" );
	print ( i.processNode ( atribA ) );
	print ( "Valor da variavel a: " ) ;
	print ( i.processNode ( varA ) );

	ITNode * soma3 = ITNode::createBinOp ( ITNode::sum , varA, soma2 );
	print ( "Resultado da soma a + [(2+1) * (2+1)]: " );
	print ( i.processNode ( soma3 ) );

	return 0;


}

