#pragma once

#include <iostream>
#include <vector>

namespace AST {

//Binary operations
enum Operation { plus, mult };
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


class Variavel : public Node {
    public:
        char* tipoVariavel;
        char* value;
        Variavel(char* tipoVariavel, char* value) : tipoVariavel(tipoVariavel), value(value) {  }
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

}

