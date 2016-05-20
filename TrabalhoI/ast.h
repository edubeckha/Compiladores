/*Abstract Syntax Tree definition*/
#pragma once

#include <iostream>
#include <vector>

extern void yyerror(const char *s, ...);

namespace AST {

	//Binary operations
	enum Operation { plus, sub, times, divi, assign, maior, menor, maiorigual, menorigual, ande, ore, unibool, unario, declaracao };
	enum Tipo { inteiro, real, booleano, indefinido, funcao };

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

	class Variable : public Node {
	     public:
	         std::string id;
	         Tipo tipo;
	         Node *next;
	         Variable(std::string id, Tipo tipo, Node *next) : id(id), tipo(tipo), next(next) { }
	         void printTree();
	         std::string tipoParaString(Tipo tipo);
	};

	class UniOp : public Node {
	public:
		Operation op;
		AST::Variable *node;
		UniOp(Node* node, Operation op) : node(dynamic_cast<Variable*>(node)), op(op) { }
		void printTree();
	};

	class Block : public Node {
	    public:
	        NodeList lines;
	        Block() { }
	        void printTree();
	};


	class Funcao : public Node {
	     public:
	         std::string id;
	         Tipo tipo;
	         // Node *right;
	         Node* v;
	         // Funcao(std::string id, Tipo tipo, Node *right) : id(id), tipo(tipo), right(right) { }
	         Funcao(std::string id, Tipo tipo, AST::Node* v) : id(id), tipo(tipo), v(v) { }
	         void printTree();
	         std::string tipoParaString(Tipo tipo);
	};

	class  Parametros : public Node{
	public:
		AST::Node* node;
		Parametros(AST::Node* node) : node(node){}
		void printTree();
	};

	class DefineFuncao : public Node {
	     public:
	         std::string id;
	         Node *right;
	         DefineFuncao(std::string id, Node *right) : id(id), right(right) { }
	         void printTree();
	         // std::string tipoParaString(Tipo tipo);
	};

}