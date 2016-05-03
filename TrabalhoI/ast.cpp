#include "ast.h"
#include "st.h"

using namespace AST;

extern ST::SymbolTable symtab;

/* Print methods */
void Integer::printTree(){
    std::cout << value;
    return;
}

void Doubler::printTree(){
    std::cout << "Printando um double com valor: " << value << std::endl;
    return;
}

void BinOp::printTree(){
    left->printTree();
    switch(op){
        case plus: std::cout << " + "; break;
        case sub: std::cout << " - "; break;
        case times: std::cout << " * "; break;
        case divi: std::cout << " / "; break;
        case assign: std::cout << " = "; break;
        case maior: std::cout << " > "; break;
        case menor: std::cout << " < "; break;
        case maiorigual: std::cout << " >= "; break;
        case menorigual: std::cout << " <= "; break;
        case ande: std::cout << " AND "; break;
        case ore: std::cout << " OR "; break;
        case unibool: std::cout << " ~ "; break;
        case atri: std::cout << " := "; break;
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

void Variable::printTree(){
    if (next != NULL){
        next->printTree();
        std::cout << ", ";
    }
    std::cout << id;
}

void TipoVariavel::printTree(){
    std::cout << "asdasdasdas" <<std::endl;
    switch(tipo){
        case inteiro: std::cout << "Foram declaradas variáveis do tipo inteiro: " <<std::endl; break;
        case real: std::cout << "Foram declaradas variáveis do tipo real: " <<std::endl; break;
        case booleano: std::cout << "Foram declaradas variáveis do tipo booleano: " <<std::endl; break;
    }

    return;
}

