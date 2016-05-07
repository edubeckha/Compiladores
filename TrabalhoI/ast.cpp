#include "ast.h"
#include "st.h"

using namespace AST;

extern ST::SymbolTable symtab;

/* Print methods */
void Integer::printTree(){
    std::cout << "(valor inteiro " << value << ")";
    return;
}

void Doubler::printTree(){
    std::cout << "(valor real " << value << ")";
    return;
}

void Boolean::printTree(){
    std::cout << "(valor booleano " << value << ")";
    return;
}

void BinOp::printTree(){
    
    switch(op){
        //esse dynamic cast pode ser uma saida, mas provavelmente estou criando um overhead desnecessario fazendo essas conversoes enquanto ha um jeito mais facil de realizar esse print...
        case assign: std::cout << "Atribuicao de valor para variavel do tipo"<< dynamic_cast<Variable*>(left)->tipoParaString(dynamic_cast<Variable*>(left)->tipo); left->printTree(); std::cout << ": "; right->printTree(); break;

        case plus: std::cout << "("; left->printTree(); std::cout << " (soma real) "; right->printTree(); std::cout << ")"; break;

        case sub: std::cout << "("; left->printTree(); std::cout << " (subtracao real) "; right->printTree(); std::cout << ")"; break;
        case times: std::cout << "("; left->printTree(); std::cout << " (multiplicacao real) "; right->printTree(); std::cout << ")"; break;
        case divi: std::cout << "("; left->printTree(); std::cout << " (divisao real) "; right->printTree(); std::cout << ")"; break;
        
        case maior: std::cout << " > "; break;
        case menor: std::cout << " < "; break;
        case maiorigual: std::cout << " >= "; break;
        case menorigual: std::cout << " <= "; break;
        case ande: std::cout << " AND "; break;
        case ore: std::cout << " OR "; break;

        default: std::cout << "Operador nao tratado" << std::endl; break;
    }
    
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





