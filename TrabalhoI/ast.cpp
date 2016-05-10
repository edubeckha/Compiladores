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
    std::cout << "(valor booleano " << tipoParaString() << ")";
    return;
}

void Arranjo::printTree(){
    std::cout << "arranjo " << AST::tipoParaString(tipoArranjo) << ": ";
}

void BinOp::printTree(){

    switch(op){
        //esse dynamic cast pode ser uma saida, mas provavelmente estou criando um overhead desnecessario fazendo essas conversoes enquanto ha um jeito mais facil de realizar esse print...
        case assign: 
        std::cout << "Atribuicao de valor para variavel do tipo"<< 
        AST::tipoParaString(dynamic_cast<Variable*>(left)->tipo); 
        left->printTree(); 
        std::cout << ": "; 
        right->printTree(); 
        break;

        case plus: 
        std::cout << "("; left->printTree(); std::cout << " (soma) "; 
        right->printTree(); 
        std::cout << ")"; 
        break;

        case sub: 
        std::cout << "("; left->printTree(); 
        std::cout << " (subtracao) "; 
        right->printTree(); 
        std::cout << ")"; 
        break;

        case times:
        std::cout << "("; left->printTree(); 
        std::cout << " (multiplicacao) "; 
        right->printTree(); 
        std::cout << ")"; 
        break;

        case divi: 
        std::cout << "("; 
        left->printTree(); 
        std::cout << " (divisao) "; 
        right->printTree(); 
        std::cout << ")"; 
        break;
        
        case maior: 
        std::cout << "("; left->printTree(); 
        std::cout << " (maior que) "; 
        right->printTree(); 
        std::cout << ")"; 
        break;

        case menor: 
        std::cout << "("; left->printTree(); 
        std::cout << " (menor que) "; 
        right->printTree(); 
        std::cout << ")"; 
        break;


        case maiorigual: 
        std::cout << "("; left->printTree(); 
        std::cout << " (maior ou igual que) "; 
        right->printTree();
        std::cout << ")"; 
        break;

        case menorigual: 
        std::cout << "("; left->printTree(); 
        std::cout << " (menor ou igual que) "; 
        right->printTree(); 
        std::cout << ")"; 
        break;
        
        case ande: 
        std::cout << "("; left->printTree(); 
        std::cout << " (AND) "; 
        right->printTree(); 
        std::cout << ")"; 
        break;

        case ore: 
        std::cout << "("; left->printTree(); 
        std::cout << " (OR) "; 
        right->printTree(); 
        std::cout << ")"; 
        break;

        case unibool:
        std::cout << "Atribuicao de valor para variavel booleana: "; left->printTree(); 
        std::cout << " (not unario binario) "; 
        right->printTree(); 
        break;

        //ajeitar esses dynamics depois....
        case unario: 
        std::cout << "Atribuicao de valor para variavel do tipo " << AST::tipoParaString(dynamic_cast<Variable*>(left)->tipo);
        left->printTree(); std::cout << ": "; 
        std::cout << " (not unario " << AST::tipoParaString(dynamic_cast<Variable*>(left)->tipo) << ") "; 
        right->printTree(); 
        break;


        default: std::cout << "Operador nao tratado" << std::endl; break;
    }  
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
        std::cout << "Declaracao de variavel do tipo" << AST::tipoParaString(node->tipo) << ": "; node->printTree();
        break;
        default: std::cout << "Operacao nao reconhecida!!!" << std::endl;
    }
}

std::string AST::tipoParaString(Tipo tipo){
    switch(tipo){
        case inteiro : return " inteiro ";
        case real : return " real ";
        case booleano : return " booleano ";
        default : return " indefinido ";
    }
}







