#pragma once

#include <iostream>
#include <vector>

namespace AST {

//Binary operations
enum Operation { plus, mult };

class Node;

typedef std::vector<Node*> NodeList; //List of ASTs

struct estruturaVariavel {
    
    bool ehDouble;

    union tipoVariavel {
        int i;
        double d;
    };
};

class Node {
    public:
        virtual ~Node() {}
        virtual void printTree(){}
        virtual void* computeTree(){return 0;}
};

class Integer : public Node {
    public:
        int value;
        Integer(int value) : value(value) {  }
        void printTree();
        int computeTree();
};

class Double : public Node {
    public:
       double value;
       Double(double value) : value(value) { }
       void printTree();
       double computeTree();
};

class BinOp : public Node {
    public:
        Operation op;
        Node *left;
        Node *right;
        BinOp(Node *left, Operation op, Node *right) :
            left(left), right(right), op(op) { }
        void printTree();
        void* computeTree();
};

class Block : public Node {
    public:
        NodeList lines;
        Block() { }
        void printTree();
        void* computeTree();
};

}

