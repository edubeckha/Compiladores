#include "ast.h"
#include "st.h"

using namespace AST;

extern ST::SymbolTable symtab;

/* Print methods */
void Integer::printTree(){
    std::cout << "(variavel inteira " << value << ") ";
    return;
}

void Doubler::printTree(){
    std::cout << "(variavel real " << value << ") ";
    return;
}

void Boolean::printTree(){
    std::cout << "(variavel booleana " << value << ") ";
    return;
}

void BinOp::printTree(){
    switch(op){
        case assign: std::cout << "Atribuicao de valor para variavel: "; break;
        case plus: std::cout << " + "; break;
        case sub: std::cout << " - "; break;
        case times: std::cout << " * "; break;
        case divi: std::cout << " / "; break;
        case maior: std::cout << " > "; break;
        case menor: std::cout << " < "; break;
        case maiorigual: std::cout << " >= "; break;
        case menorigual: std::cout << " <= "; break;
        case ande: std::cout << " AND "; break;
        case ore: std::cout << " OR "; break;

        default: std::cout << "Operador nao tratado" << std::endl; break;
    }
    
    left->printTree();
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

void UniOp::printTree(){
    switch(op){
        case declaracao:
        std::cout << "Declaracao de variavel do tipo" << node->tipoParaString(node->tipo) << ": "; node->printTree();
        break;
        default: std::cout << "Operacao nao reconhecida!!! (Ou ainda nao tratada pelo compileiro)." << std::endl;
    }
}

std::string Variable::tipoParaString(Tipo tipo){
    switch(tipo){
        case inteiro : return " inteiro: ";
        case real : return " real: ";
        case booleano : return " booleano: ";
        default : return " indefinido: ";
    }
}





