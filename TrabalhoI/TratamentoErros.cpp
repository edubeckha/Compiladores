#include "TratamentoErros.h"
using namespace Tipos;

AST::Tipo Tipos::opUnaria(AST::Tipo tipoRecebido, AST::Operation op){
	AST::Tipo tipoRetorno;
	switch(op){
		case AST::unario:

		break;
		case AST::unibool:

		break;
	
	default:
		std::cout << "Operacao nao suportada em nodos binarios!" << std::endl;

	}
	return tipoRetorno;
}


AST::Tipo Tipos::opBinaria(AST::Tipo tipoNodoEsquerda, AST::Tipo tipoNodoDireita, AST::Operation op){
	AST::Tipo tipoRetorno;
	switch(op){
		default:
		if(op == AST::plus || op == AST::sub || op == AST::times || op == AST::divi){
			tipoRetorno = AST::inteiro; //faz com que o tipo de retorno padrao seja inteiro
			if(tipoNodoEsquerda == AST::real || tipoNodoDireita == AST::real){
					tipoRetorno = AST::real;
			}

			if(tipoNodoEsquerda != AST::inteiro || tipoNodoEsquerda != AST::real){
				Tipos::erroTipagem(op, AST::inteiro, AST::real, AST::booleano);
			}

			if(tipoNodoDireita!= AST::inteiro || tipoNodoDireita != AST::real){
				Tipos::erroTipagem(op, AST::inteiro, AST::real, AST::booleano);
			}
		}
	}


	return tipoRetorno;
}
void Tipos::erroTipagem(AST::Operation operacao, AST::Tipo primeiroRecebido, AST::Tipo segundoRecebido, AST::Tipo esperado){
	std::cout << "dando uns erro" << std::endl;
}