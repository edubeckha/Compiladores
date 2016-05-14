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
    std::cout << "arranjo do tipo "<< 
    AST::tipoParaString(dynamic_cast<Variable*>(var)->tipo)
    << " {+indice: ";
    indice->printTree();
    std::cout << "}";
}

void BinOp::printTree(){

    switch(op){
        case assign: 
        std::cout << "Atribuicao de valor para ";
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

        case igual:
            std::cout<<"Atribuicao de valor para variavel booleana: ";
            std::cout << ": ("; left->printTree(); 
            std::cout << " (igual booleano) "; 
            right->printTree();
            std::cout << ")"; 
        break;

        case diferente:
            std::cout<<"Atribuicao de valor para variavel booleana: ";
            std::cout << ": ("; left->printTree(); 
            std::cout << " (diferente booleano) "; 
            right->printTree();
            std::cout << ")"; 
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
        std::cout << ", " << id;
    } else {
        std::cout << "variavel do tipo" << AST::tipoParaString(tipo) << ": " << id;
    }
}

void UniOp::printTree(){
    switch(op){
        case declaracao:
            std::cout << "Declaracao de ";
            node->printTree();
        break;
        default: std::cout << "Operacao nao reconhecida!!!" << std::endl;
    }
}

/*Imprime a condicao, quando a mesma aparecer na arvore.
Deve-se atentar ao fato de que a mesma imprimira o corpo do else somente
se ha algum nodo compondo este corpo*/
void Condicao::printTree(){
    std::cout << "Expressao condicional " << std::endl;
    std::cout << "+se: " << std::endl;
    condicao->printTree();
    std::cout << "\n+entao: " << std::endl;
    corpoIf->printTree();

    if(corpoElse != NULL){
    std::cout << "\n+senao: " << std::endl;
    corpoElse->printTree();
    }

    std::cout << "\nFim expressao condicional" << std::endl;
}

std::string AST::tipoParaString(Tipo tipo){
    switch(tipo){
        case inteiro : return " inteiro ";
        case real : return " real ";
        case booleano : return " booleano ";
        default : return " indefinido ";
    }
}







