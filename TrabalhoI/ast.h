/*Abstract Syntax Tree definition*/
#pragma once

#include <iostream>
#include <vector>

extern void yyerror(const char *s, ...);

namespace AST {

//Binary operations
enum Operation { plus, times, assign };
enum Tipo { inteiro, real, booleano };
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

class TipoVariavel : public Node {
    public:
    Tipo tipo;
    TipoVariavel(Tipo tipo1) : tipo(tipo1) { std::cout << tipo << std::endl; }
    void printTree(); 
};

class BinOp : public Node {
    public:
        Operation op;
        Node *left;
        Node *right;
        BinOp(Node *left, Operation op, Node *right) :
            left(left), right(right), op(op) { }
        void printTree();
};

class Block : public Node {
    public:
        NodeList lines;
        Block() { }
        void printTree();
};

class Variable : public Node {
     public:
         std::string id;
         Node *next;
         Variable(std::string id, Node *next) : id(id), next(next) { }
         void printTree();
};

}

