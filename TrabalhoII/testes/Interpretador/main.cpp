#include <iostream>
#include "itree.h"
#include "interpreter.h"
#define print(x) std::cout << (x) << std::endl;

int main () {
	print ( "Comecando teste do intepretador!\n\nOs comandos serão expressos entre '<>' " );
	Interpreter i;

	/*Nos seguintes testes, serão geradas manualmentes as arvores que
	 * deveriam ser geradas para os comandos em destaque.
	 * Devido a restrições de espaço-tempo, o interpretador não pode ser
	 * implantado na parte de reconhecimento de comandos  :C
	 *
	 */

	print ( "Teste numero 1: < 1+2 > " );
	/*Cria nodos de valor para as literais 1 e 2 (inteiros), e um nodo de soma, que é processado*/
	ITNode * um = ITNode::createValue ( Data ( 1 ) );
	ITNode * dois = ITNode::createValue ( Data ( 2 ) );
	ITNode * soma1 = ITNode::createBinOp ( ITNode::sum, dois, um );
	std::cout << "Resultado: " << i.processNode ( soma1 ) << std::endl;

	print ( "\nTeste numero 2: < 1+(1+2) >" );
	/*Cria um novo nodo de soma, que recebe como filhos 1 e a soma anterior*/
	ITNode * soma2 = ITNode::createBinOp ( ITNode::sum, um, soma1 );
	std::cout << "Resultado: " << i.processNode ( soma2 ) << std::endl;

	print ( "\nTeste numero 3: < 2*(1+2) >" );
	/*Cria um nodo de multiplicação, como filhos o literal 2 e a soma 1*/
	ITNode * mult1 = ITNode::createBinOp ( ITNode::mult, dois, soma1 );
	std::cout << "Resultado: " << i.processNode ( mult1 ) << std::endl;


	print ( "\nTeste numero 4: < int a; a = 1+2 >\nEste comando não tem retorno visual ao usuário." );

	/*Variavel a*/
	ITNode * varA = ITNode::createVar ( "a" );
	/*Cria a arvore de definição da variavel inteira a */
	ITNode * varDefA = ITNode::createDefVar ( "a", Data::integer );
	ITNode * def = ITNode::createDef ( varDefA );
	i.processNode ( def ); //Definicoes nao printam nada no consolo.

	/*Cria o nodo de atribuição do valor de 1+2 a "a"*/
	ITNode * atribA = ITNode::createAtrib ( varA, soma1 );
	/*Processa a atribuição*/
	i.processNode ( atribA );

	print ( "\nTeste numero 5: < a >" );
	/*Processa um nodo variavel com o identificador de uma variavel. Imprime na tela o conteúdo da mesma*/
	std::cout << "Resultado: " << i.processNode ( varA ) << std::endl;

	print ( "\nTeste letra 6: < (a+1.5)/2 >" );
	/*Cria os nodos das opereracoes. Note que para uma variavel ser usada como argumento de operacao,
	 * basta passar seu identificador pra frente num nodo*/
	ITNode * umEMeio = ITNode::createValue ( Data ( ( float ) 1.5 ) );
	ITNode * soma6 = ITNode::createBinOp ( ITNode::sum, varA, umEMeio );
	ITNode * divisao6 = ITNode::createBinOp ( ITNode::div, soma6, dois );
	std::cout << "Resultado: " << i.processNode ( divisao6 ) << std::endl;

	print ( "\nTeste numero 7: < 2+2 == 4 >" );
	ITNode * soma7 = ITNode::createBinOp ( ITNode::sum, dois, dois );
	ITNode * quatro = ITNode::createValue ( Data ( 4 ) );
	ITNode * comparacao7 = ITNode::createBinOp ( ITNode::eq, soma7, quatro );
	std::cout << "Resultado: " << i.processNode ( comparacao7 ) << std::endl;

	print ( "\nTeste numero 8: < 2 == 4 >" );
	ITNode * comparacao8 = ITNode::createBinOp ( ITNode::eq, dois, quatro );
	std::cout << "Resultado: " << i.processNode ( comparacao8 ) << std::endl;

	print ( "\nTeste numero 9: < 2 == 4 or 2 == 2 >" );
	ITNode * comparacao9_1 = ITNode::createBinOp ( ITNode::eq, dois, quatro );
	ITNode * comparacao9_2 = ITNode::createBinOp ( ITNode::eq, dois, dois );
	ITNode * comparacao9_3 = ITNode::createBinOp ( ITNode::bor, comparacao9_1, comparacao9_2 );
	std::cout << "Resultado: " << i.processNode ( comparacao9_3 ) << std::endl;


	print ( "\nTeste numero 10: < 2 == 4 and 2 == 2 >" );
	ITNode * comparacao10 = ITNode::createBinOp ( ITNode::band, comparacao9_1, comparacao9_2 );
	std::cout << "Resultado: " << i.processNode ( comparacao10 ) << std::endl;

	print ( "\nTeste numero 11: < 4 == 4 and 2 == 2 >" );
	ITNode * comparacao11_1 = ITNode::createBinOp ( ITNode::eq, quatro, quatro );
	ITNode * comparacao11 = ITNode::createBinOp ( ITNode::band, comparacao11_1, comparacao9_2 );
	std::cout << "Resultado: " << i.processNode ( comparacao11 ) << std::endl;

	print ( "\nTeste numero 12: < string x,y; x = \"me pas\" ; y = \"sa prof!\" >\nEste comando nao gera retorno visual ao usuário" );
	ITNode * varDefX = ITNode::createDefVar ( "x", Data::DataType::string );
	ITNode * varDefY = ITNode::createDefVar ( "y", Data::DataType::string );

	ITNode * defX = ITNode::createDef ( varDefX );
	ITNode * defY = ITNode::createDef ( varDefY );

	i.processNode ( defX );
	i.processNode ( defY );

	ITNode * x = ITNode::createVar ( "x" );
	ITNode * y = ITNode::createVar ( "y" );

	ITNode * texto1 = ITNode::createValue ( Data ( std::string ( "me pas" ) ) );
	ITNode * texto2 = ITNode::createValue ( Data ( std::string ( "sa prof!" ) ) );

	ITNode * atribX = ITNode::createAtrib ( x, texto1 );
	ITNode * atribY = ITNode::createAtrib ( y, texto2 );

	i.processNode ( atribX );
	i.processNode ( atribY );

	print ( "\nTeste numero 13: < x + y >" );

	ITNode * concat13 = ITNode::createBinOp ( ITNode::sum, x, y );
	std::cout << "Resultado: " << i.processNode ( concat13 ) << std::endl;

	print ( "\nTeste numero 14: < x = x + y >; x[0,7]; " );
	atribX = ITNode::createAtrib ( x, concat13 );
	i.processNode ( atribX );
	ITNode * intervalo14 = ITNode::createRange ( ITNode::createValue ( Data ( 0 ) ), ITNode::createValue ( Data ( 7 ) ) );
	ITNode * substring14 = ITNode::createSubstring ( x, intervalo14 );
	std::cout << "Resultado: " << i.processNode ( substring14 ) << std::endl;




	return 0;


}



