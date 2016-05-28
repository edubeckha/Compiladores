/*Abstract Syntax Tree definition*/
#pragma once

#include <iostream>
#include <vector>
#include "TratamentoErros.h"
#include "st.h"

extern void yyerror(const char *s, ...);
namespace ST {class SymbolTable;};
extern ST::SymbolTable* symbolTable;
namespace AST {

	class Node;
	typedef std::vector<Node*> NodeList; //List of ASTs

	class Node {
	    public:
	    	Tipos::Tipo tipo = Tipos::indefinido;
	        virtual ~Node() {}
	        virtual void printTree(){}
	};


	std::string tipoParaString(Tipos::Tipo tipo);
 	AST::Node* realizaCoercao(std::string id, AST::Node* left, AST::Node* right);

 	/*Nodo que define um inteiro, com seu tipo e valor do tipo inteiro*/
	class Integer : public Node {
	    public:
	        int value;
	        Integer(int value) : value(value) {
	        tipo = Tipos::inteiro;  }
	        void printTree();
	};

	/*Nodo que define um real, com seu tipo e valor do tipo real*/
	class Doubler : public Node {
	public:
	        double value;
	        Doubler(double value) : value(value) { 
	        	tipo = Tipos::real; }
	        void printTree();
	};

	/*Nodo que define um booleano, com seu tipo e valor do tipo booleano*/
	class Boolean : public Node {
	public:
	        bool value;
	        Boolean(bool value) : value(value) {
	        	tipo = Tipos::booleano; }
	        void printTree();
	        std::string tipoParaString(){
	        	if(value) return "TRUE"; return "FALSE";	
	        }
	};

	/*Define um nodo do tipo operacao binaria, que recebe um tipo de operacao (o tipo de operacao feita entre os nodos) e dois nodos que realizam essa operacao*/
	class BinOp : public Node {
	    public:
	        Tipos::Operation op;
	        Node *left;
	        Node *right;
	        BinOp(Node *l, Tipos::Operation op, Node *r) :
	            left(l), right(r), op(op) {
	        	tipo = Tipos::opBinaria(left->tipo, right->tipo, op); }
	        void printTree();
	};

	/*Nodo que define variaveis do programa. A mesma possui um id, um tipo e um nodo next. Esse nodo eh de grande valia quando
	tratamos de varias variaveis declaradas ao mesmo tempo (int a, b, c...)*/
	class Variable : public Node {
	     public:
	         std::string id;
	         Node *next;
	         Variable(std::string id, Tipos::Tipo t, Node *next) : id(id), next(next) {
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
		Node *node;
		UniOp(Node* node, Tipos::Operation op, Tipos::Tipo tipoRetorno) : node(node), op(op) {
			tipo = tipoRetorno;
		}
		void printTree();
	};

	/*Classe para tratamento de arranjos, que recebe uma variavel (para poder ser testada na tabela de simbolos) e um nodo indice, que 
	da a liberdade de colocarmos uma expressao qualquer como indice do arranjo*/
	class Arranjo : public Node {
	public:
		Node* indice;
		Node* var;
		Arranjo(Node* indice, Node* var) : indice(indice), var(var) { 
			Tipos::opUnaria(indice->tipo, Tipos::defineIndiceArranjo);
			tipo = var->tipo;
		}
	    void printTree();		
	};


	/*Node que representa a estrutura condicional. A mesma possui tres
	partes distintas: condicao, corpo do laco if e corpo do lado else*/
	class Condicao : public Node {
		public:
		Node* condicao;
		Node* corpoIf;
		Node* corpoElse;
		//extern ST::SymbolTable* tabelaCondicao; /*Tabela de simbolos do escopo*/
		/*Talvez ter mais uma tabela para o escopo do else??? verificar!*/

		Condicao(Node* condicao, Node* corpoIf, Node* corpoElse) : condicao(condicao), corpoIf(corpoIf), corpoElse(corpoElse) {
			Tipos::opUnaria(condicao->tipo, Tipos::defineCondicaoLaco);
		}
		void printTree();
	};

	/*Classe para tratamento de lacos do tipo while*/
	class Laco : public Node {
	public:
		Node* condicaoLaco;
		Node* corpoLaco;

		Laco(Node* condicaoLaco, Node* corpoLaco) : condicaoLaco(condicaoLaco), corpoLaco(corpoLaco) {
			Tipos::opUnaria(condicaoLaco->tipo, Tipos::defineCondicaoLaco);
		}
		void printTree();
	};
}