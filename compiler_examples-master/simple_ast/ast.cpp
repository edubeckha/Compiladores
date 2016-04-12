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

/* Compute methods */
int Integer::computeTree(){
    return value;
}

int BinOp::computeTree(){
    int value, lvalue, rvalue;
    lvalue = left->computeTree();
    rvalue = right->computeTree();
    switch(op){
         case plus: value = lvalue + rvalue;
         std::cout << "Detectada uma soma de " << lvalue << " e " << rvalue << std::endl;
         break;
         case mult: value = lvalue * rvalue;
         std::cout << "Detectada uma multiplicacao de " << lvalue << " e " << rvalue << std::endl;
         break;
    }
    return value;
}

int Block::computeTree(){
    int value;
    for (Node* line: lines) {
        value = line->computeTree();
         std::cout << "Computed " << value << std::endl;
    }
    return 0;
}

/* Compute methods */
double Double::computeTree(){
    return value;
}

double BinOp::computeTree(){
    double value, lvalue, rvalue;
    lvalue = left->computeTree();
    rvalue = right->computeTree();
    switch(op){
         case plus: value = lvalue + rvalue;
         std::cout << "Detectada uma soma de " << lvalue << " e " << rvalue << std::endl;
         break;
         case mult: value = lvalue * rvalue;
         std::cout << "Detectada uma multiplicacao de " << lvalue << " e " << rvalue << std::endl;
         break;
    }
    return value;
}

double Block::computeTree(){
    double value;
    for (Node* line: lines) {
        value = line->computeTree();
         std::cout << "Computed " << value << std::endl;
    }
    return 0;
}