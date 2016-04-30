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


class Nome : public Node {
    public:
        char* value;
        Nome(char* value) : value(value) {  }
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

