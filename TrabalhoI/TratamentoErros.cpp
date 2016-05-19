#include "TratamentoErros.h"
using namespace Tipos;

Tipo Tipos::opUnaria(Tipo tipoRecebido, Operation op){
	Tipo tipoRetorno;
	switch(op){
		case unario:

		break;
		case unibool:

		break;
	
	default:
		std::cout << "Operacao nao suportada em operacoes unarias!" << std::endl;

	}
	return tipoRetorno;
}


Tipo Tipos::opBinaria(Tipo tipoNodoEsquerda, Tipo tipoNodoDireita, Operation op){
	Tipo tipoRetorno;
	switch(op){

	case assign: break;
		default:
		if(op == plus || op == sub || op == times || op == divi){
			tipoRetorno = inteiro; //faz com que o tipo de retorno padrao seja inteiro
			if(tipoNodoEsquerda == real || tipoNodoDireita == real){
					tipoRetorno = real;
			}

			if(tipoNodoEsquerda != inteiro || tipoNodoEsquerda != real){
				Tipos::erroTipagem(op, inteiro, real, booleano);
				break;
			}

			if(tipoNodoDireita != inteiro || tipoNodoDireita != real){
				Tipos::erroTipagem(op, inteiro, real, booleano);
				break;
			}
		} else {
				std::cout << "Operacao nao suportada em operacoes binarias!" << std::endl;
		}
	}


	return tipoRetorno;
}
void Tipos::erroTipagem(Operation operacao, Tipo primeiroTipo, Tipo segundoTipo, Tipo recebido){
	std::cout<< "A operacao de " + opParaString(operacao) + " esperava " + tipoParaString(primeiroTipo);
	if(segundoTipo != indefinido){
		std::cout << " ou " + tipoParaString(segundoTipo);
	}
	std::cout << " como parâmetro, mas recebeu " << tipoParaString(recebido) << "." << "\n";
}

std::string Tipos::tipoParaString(Tipo tipo){
	switch(tipo){
		case inteiro: return "inteiro";

		case real: return "real";

		case booleano: return "booleano";

		default: return "indefinido";
	}


}

std::string Tipos::opParaString(Operation op){
	switch(op){
		case plus: return "soma";
		case sub: return "subtracao";
		default: return "indefinida";
	}
}