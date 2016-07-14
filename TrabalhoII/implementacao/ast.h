/*Abstract Syntax Tree definition*/
#pragma once

#include <iostream>
#include <vector>
#include "TratamentoErros.h"
#include "st.h"

extern void yyerror ( const char * s, ... );
namespace ST {class SymbolTable; class Symbol;};
extern ST::SymbolTable * symbolTable;
namespace AST {

	class Node;
	typedef std::vector<Node *> NodeList; //List of ASTs

	class Node {
	public:
		Tipos::Tipo tipo = Tipos::indefinido;
		virtual ~Node() {}
		virtual void printTree() {}
		void temErro ( bool erro ) {this->erro = erro;}
	private:
		bool erro = false;

	};


	std::string tipoParaString ( Tipos::Tipo tipo );
	AST::Node * realizaCoercao ( std::string id, AST::Node * left, AST::Node * right, ST::SymbolTable * symtab );

	/*Nodo que define um inteiro, com seu tipo e valor do tipo inteiro*/
	class Integer : public Node {
	public:
		int value;
		Integer ( int value ) : value ( value ) {
			tipo = Tipos::inteiro;
		}
		void printTree();
	};

	/*Nodo que define um real, com seu tipo e valor do tipo real*/
	class Doubler : public Node {
	public:
		double value;
		Doubler ( double value ) : value ( value ) {
			tipo = Tipos::real;
		}
		void printTree();
	};

	/*Nodo que define um booleano, com seu tipo e valor do tipo booleano*/
	class Boolean : public Node {
	public:
		bool value;
		Boolean ( bool value ) : value ( value ) {
			tipo = Tipos::booleano;
		}
		void printTree();
		std::string tipoParaString() {
			if ( value ) { return "TRUE"; }

			return "FALSE";
		}
	};

	/*Define um nodo do tipo operacao binaria, que recebe um tipo de operacao (o tipo de operacao feita entre os nodos) e dois nodos que realizam essa operacao*/
	class BinOp : public Node {
	public:
		Tipos::Operation op;
		Node * left;
		Node * right;
		BinOp ( Node * l, Tipos::Operation op, Node * r ) :
			left ( l ), right ( r ), op ( op ) {

			tipo = Tipos::opBinaria ( left->tipo, right->tipo, op );
		}
		void printTree();
	};

	/*Nodo que define variaveis do programa. A mesma possui um id, um tipo e um nodo next. Esse nodo eh de grande valia quando
	tratamos de varias variaveis declaradas ao mesmo tempo (int a, b, c...)*/
	class Variable : public Node {
	public:
		std::string id;
		Node * next;
		Variable ( std::string id, Tipos::Tipo t, Node * next ) : id ( id ), next ( next ) {
			tipo = t;
		}
		void printTree();

	};

	/*Nodo responsavel por um bloco de linhas do sistema*/
	class Block : public Node {
	public:
		NodeList lines;
		Block() { }
		void printTree();
	};

	/*Nodo que define operacoes unarias do programa. A unica disponivel ate o momento eh a declaracao*/
	class UniOp : public Node {
	public:
		Tipos::Operation op;
		Node * node;
		UniOp ( Node * node, Tipos::Operation op, Tipos::Tipo tipoRetorno ) : node ( node ), op ( op ) {
			tipo = tipoRetorno;
		}
		void printTree();
	};

	/*Classe para tratamento de arranjos, que recebe uma variavel (para poder ser testada na tabela de simbolos) e um nodo indice, que
	da a liberdade de colocarmos uma expressao qualquer como indice do arranjo*/
	class Arranjo : public Node {
	public:
		Node * indice;
		Node * var;
		Arranjo ( Node * indice, Node * var ) : indice ( indice ), var ( var ) {
			Tipos::opUnaria ( indice->tipo, Tipos::defineIndiceArranjo );
			tipo = var->tipo;
		}
		void printTree();
	};

	/*Nodo que define um nodo funcao. O mesmo tem um id, um tipo e um vetor de parametros*/
	class Funcao : public Node {
	public:
		std::string id;
		Tipos::Tipo tipo;
		std::vector<AST::Variable *> parametros;
		Funcao ( std::string id, Tipos::Tipo tipo, std::vector<AST::Variable *> parametros ) : id ( id ), tipo ( tipo ), parametros ( parametros ) { }
		void printTree();
	};

	/*Nodo que tem a funcao de definir uma funcao*/
	class DefineFuncao : public Node {
	public:
		std::string id;
		std::vector<AST::Variable *> parametros;
		Tipos::Tipo tipo;
		Node * body;
		DefineFuncao ( std::string id, Tipos::Tipo tipo, std::vector<AST::Variable *> parametros, Node * body ) : id ( id ), tipo ( tipo ), parametros ( parametros ), body ( body ) { }
		void printTree();
	};

	/*Nodo que define o retorno da funcao*/
	class Retorno : public Node {
	public:
		Node * ret;
		Retorno ( AST::Node * ret ) : ret ( ret ) {}
		void printTree();
	};

	/*Node que representa a estrutura condicional. A mesma possui tres
	partes distintas: condicao, corpo do laco if e corpo do lado else*/
	class Condicao : public Node {
	public:
		Node * condicao;
		Node * corpoIf;
		Node * corpoElse;
		//extern ST::SymbolTable* tabelaCondicao; /*Tabela de simbolos do escopo*/
		/*Talvez ter mais uma tabela para o escopo do else??? verificar!*/

		Condicao ( Node * condicao, Node * corpoIf, Node * corpoElse ) : condicao ( condicao ), corpoIf ( corpoIf ), corpoElse ( corpoElse ) {
			Tipos::opUnaria ( condicao->tipo, Tipos::defineCondicaoLaco );
		}
		void printTree();
	};

	/*Classe para tratamento de lacos do tipo while*/
	class Laco : public Node {
	public:
		Node * condicaoLaco;
		Node * corpoLaco;

		Laco ( Node * condicaoLaco, Node * corpoLaco ) : condicaoLaco ( condicaoLaco ), corpoLaco ( corpoLaco ) {
			Tipos::opUnaria ( condicaoLaco->tipo, Tipos::defineCondicaoLaco );
		}
		void printTree();
	};


	/*Nodo que representa o construtor da classe. O mesmo tem um id, uma lista de parametros e um block que representa o seu corpo*/
	class ConstrutorClasse : public Node {
	public:
		std::string id;
		std::vector<AST::Variable *> parametros;
		AST::Block* corpoConstrutor;
		ConstrutorClasse ( std::string id, std::vector<AST::Variable *> parametros, AST::Block* corpoConstrutor ) : id ( id ), parametros ( parametros ), corpoConstrutor (corpoConstrutor) {
		}
		void printTree();
	};

	/*Nodo que representa uma classe. O mesmo tem um id, um block que representa o corpo da classe, uma tabela de simbolos com seus simbolos e seu construtor*/
	class Classe : public Node {
	public:
		std::string id;
		Block* corpoClasse;
		ST::SymbolTable* tabelaSimbolos;
		AST::ConstrutorClasse* construtorClasse;

		Classe(std::string id, Block* corpoClasse, ST::SymbolTable* tabelaSimbolos, AST::ConstrutorClasse* construtorClasse) : id(id), corpoClasse(corpoClasse), tabelaSimbolos(tabelaSimbolos), construtorClasse(construtorClasse) { }

		Classe(std::string id, ST::SymbolTable* tabelaSimbolos) : id(id), tabelaSimbolos(tabelaSimbolos) { }

		void printTree();
	};

	/*Nodo que representa um atributo de uma determinada classe*/
	class Atributo : public Node {
	public:
		AST::Variable* var;
		AST::Classe* classePertencente;

		Atributo(AST::Variable* var, AST::Classe* classePertencente) : var (var), classePertencente(classePertencente) { 
			tipo = var->tipo; }

		void printTree();
	};

	/*Nodo que representa o objeto de uma classe. O mesmo tem um id e a classe a qual pertence*/
	class Objeto : public Node {
	public:
		std::string id;
		AST::Classe* classePertencente;

		Objeto(std::string id, AST::Classe* classePertencente) : id(id), classePertencente(classePertencente) { }
		void verificaParametrosConstrutor(std::vector<Variable* > parametros);
		void verificaParametros(std::string id, std::vector<Variable* > parametros);
		void printTree();
	};

	/*Nodo que representa strings*/
	class String : public Node {
	public:

		const char * aux;

		String ( const char * aux ) : aux ( aux ) {
			tipo = Tipos::string;
		}

		void printTree();
	};

	/*Nodo que representa substrings*/
	class Substring : public Node {
	public:
		std::string id;
		AST::Node* aux;
		int inicio;
		int fim;

		Substring (std::string id, AST::Node* aux, int inicio, int fim ) : id(id), aux ( aux ), inicio(inicio), fim(fim) {
			tipo = Tipos::string;
		}

		void printTree();
	};

	/*Classe para o tamanho de strings*/
	class Tamanho : public Node {
	public:
		std::string id;
		AST::Node * aux;

		Tamanho ( std::string id, AST::Node* aux ) : id(id), aux ( aux ) {
			tipo = Tipos::string;
		}

		void printTree();
	};

}
