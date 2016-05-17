#include "ast.h"
#include "st.h"

using namespace AST;

extern ST::SymbolTable symtab;

/*Metodos de impressao*/

/*Imprime o valor do nodo quando o mesmo for inteiro*/
void Integer::printTree(){
    std::cout << "(valor inteiro " << value << ")";
    return;
}

/*Imprime o valor do nodo quando o mesmo for real*/
void Doubler::printTree(){
    std::cout << "(valor real " << value << ")";
    return;
}

/*Imprime o valor do nodo quando o mesmo for booleano*/
void Boolean::printTree(){
    std::cout << "(valor booleano " << tipoParaString() << ")";
    return;
}

/*Imprime o arranjo, seu tipo e seu indice quando o nodo for do tipo arranjo*/
void Arranjo::printTree(){
    std::cout << "arranjo do tipo "<< 
    AST::tipoParaString(dynamic_cast<Variable*>(var)->tipo)
    << " {+indice: ";
    indice->printTree();
    std::cout << "}";
}
/*Imprime um componente complexo juntamente com seu tipo*/
void ComponenteComplexo::printTree(){
    std::cout << "Componente " <<
    AST::tipoParaString(var->tipo) 
    << ": " << var->id 
    << std::endl;
}

/*Imprime o valor das operacoes binarias criadas na gramatica. Cada case influencia em uma operacao diferente*/
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

/*Imprime cada linha de insercao respectivamente*/
void Block::printTree(){
    for (Node* line: lines) {
        line->printTree();
        std::cout << std::endl;
    }
}

/*Imprime as informacoes das variaveis criadas no programa, juntamente com seu tipo*/
void Variable::printTree(){
    if (next != NULL){
        next->printTree();
        std::cout << ", " << id;
    } else {
        std::cout << "variavel do tipo" << AST::tipoParaString(tipo) << ": " << id;
    }
}

/*Imprime uma operacao unaria. A unica por enquanto no programa eh a operacao de declaracao (tanto de arranjos como variaveis "comuns")*/
void UniOp::printTree(){
    switch(op){
        case declaracao:
            std::cout << "Declaracao de ";
            node->printTree();
        break;

        /*Talvez esteja tomando uma linha de pensamento totalmente errada aqui....pensar um pouco mais*/
        case defComplex:
            std::cout << "Definicao tipo: complex\n+componentes: " << std::endl;
            foreach(ComponenteComplexo c : vetorComponentes){
                    c->printTree(); std::cout << "\n";
            }
            std::cout << "Fim definicao" << std::endl;
        break;

        default: std::cout << "Operacao nao reconhecida!!!" << std::endl;
    }
}

/*Imprime */
void Complexo::printTree(){
    std::cout << "aaaaaa nova era!" << std::endl;
}

/*Funcao que recebe um tipo e retorna uma string, ajudando na impressao das informacoes do nodo que contenha tipo*/
std::string AST::tipoParaString(Tipo tipo){
    switch(tipo){
        case inteiro : return " inteiro ";
        case real : return " real ";
        case booleano : return " booleano ";
        default : return " indefinido ";
    }
}







