#include "ast.h"

using namespace AST;

/* Print methods */
void Integer::printTree(){
    std::cout << value;
    return;
}

void BinOp::printTree(){
    left->printTree();
    switch(op){
        case plus: std::cout << " + ";
        std::cout << "Soma" << std::endl;
        break;
        case mult: std::cout << " * ";
        std::cout << "Multiplicacao" << std::endl;
        break;
    }
    right->printTree();
    return;
}

void Block::printTree(){
    for (Node* line: lines) {
        line->printTree();
        std::cout << std::endl;
    }
}


void Nome::printTree(){
    std::cout << "O usuário declarou um tipo " << tipo << " com nome: " << value << std::endl;
}

