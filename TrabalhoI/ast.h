/*Abstract Syntax Tree definition*/
#pragma once

#include <iostream>
#include <vector>

extern void yyerror(const char *s, ...);

namespace AST {

	/*Enum para declaracao de operacoes realizadas entre os nodos*/
	enum Operation { plus, sub, times, divi, assign, maior, menor, maiorigual, menorigual, ande, ore, unibool, unario, declaracao, igual, diferente };
	/*Enum para declaracao de tipos dos nodos*/
	enum Tipo { inteiro, real, booleano, indefinido };
 	static std::string tipoParaString(Tipo tipo);
 	
	class Node;
	typedef std::vector<Node*> NodeList; //List of ASTs

	class Node {
	    public:
	        virtual ~Node() {}
	        virtual void printTree(){}
	};

	class Integer : public Node {
	    public:
	        int value;
	        Integer(int value) : value(value) {  }
	        void printTree();
	};

	class Doubler : public Node {
	public:
	        double value;
	        Doubler(double value) : value(value) { }
	        void printTree();
	};

	class Boolean : public Node {
	public:
	        bool value;
	        Boolean(bool value) : value(value) { }
	        void printTree();
	        std::string tipoParaString(){if(value) return "TRUE"; return "FALSE";}
	};

	class BinOp : public Node {
	    public:
	        Operation op;
	        Tipo tipoRetorno;
	        Node *left;
	        Node *right;
	        BinOp(Node *left, Operation op, Node *right) :
	            left(left), right(right), op(op) { }
	        void printTree();
	};

	/*Nodo que define variaveis do programa. A mesma possui um id, um tipo e um nodo next. Esse nodo eh de grande valia quando
	tratamos de varias variaveis declaradas ao mesmo tempo (int a, b, c...)*/
	class Variable : public Node {
	     public:
	         std::string id;
	         Tipo tipo;
	         Node *next;
	         Variable(std::string id, Tipo tipo, Node *next) : id(id), tipo(tipo), next(next) { }
	         void printTree();      
	};

	/*Nodo que define operacoes unarias do programa. A unica disponivel ate o momento eh a declaracao*/
	class UniOp : public Node {
	public:
		Operation op;
		Node *node;
		UniOp(Node* node, Operation op) : node(node), op(op) { }
		void printTree();
	};

	class Block : public Node {
	    public:
	        NodeList lines;
	        Block() { }
	        void printTree();
	};

	/*Classe para tratamento de arranjos, que recebe uma variavel (para poder ser testada na tabela de simbolos) e um nodo indice, que 
	da a liberdade de colocarmos uma expressao qualquer como indice do arranjo*/
	class Arranjo : public Node {
	public:
		Node* indice;
		Node* var;
		Arranjo(Node* indice, Node* var) : indice(indice), var(var) { }
	    void printTree();		
	};

	class Laco : public Node {
	public:
		Node* condicaoLaco;
		Node* corpoLaco;

		Laco(Node* condicaoLaco, Node* corpoLaco) : condicaoLaco(condicaoLaco), corpoLaco(corpoLaco) { }
		void printTree();
	};
}