#include "TratamentoErros.h"
using namespace Tipos;


bool Tipos::necessitaCoersao(Tipo tipoNodoEsquerda, Tipo tipoNodoDireita){
	if(tipoNodoEsquerda == real || tipoNodoDireita == real){
		if(tipoNodoEsquerda == inteiro || tipoNodoDireita == inteiro){
			return true;
		}
	}
	return false;
}

Tipo Tipos::opUnaria(Tipo tipoRecebido, Operation op){
	switch(op){
		case defineIndiceArranjo:
			if(tipoRecebido != inteiro){
				Tipos::erroIndiceArranjo(inteiro, tipoRecebido);
			}
		break;
		case defineCondicaoLaco:
			if(tipoRecebido != booleano){
				Tipos::erroCondicaoLaco(booleano, tipoRecebido);
			}
		break;
		case unario:
		if(tipoRecebido != real || tipoRecebido != inteiro){
			Tipos::erroTipagem(unario, inteiro, real, tipoRecebido);
		}
		break;
		case unibool:
		if(tipoRecebido != booleano){
			Tipos::erroTipagem(unibool, booleano, indefinido, tipoRecebido);
		}
		break;
	default:
		std::cout << "Operacao nao suportada em operacoes unarias!" << std::endl;
	}
	return tipoRecebido;
}


Tipo Tipos::opBinaria(Tipo tipoNodoEsquerda, Tipo tipoNodoDireita, Operation op){
	switch(op){
		std::cout << "chegou aq no opbinaria";
	case assign:
			if(tipoNodoEsquerda != tipoNodoDireita){
				Tipos::tiposIncompativeis(tipoNodoEsquerda, tipoNodoDireita);
			}
		return tipoNodoEsquerda;		
	 break;
		default:
		if(op == plus || op == sub || op == times || op == divi){
			if(tipoNodoEsquerda == real || tipoNodoDireita == real){
					return real;
			}

			if(tipoNodoEsquerda != inteiro && tipoNodoEsquerda != real){
				Tipos::erroTipagem(op, inteiro, real, booleano);
				break;
			}

			if(tipoNodoDireita != inteiro && tipoNodoDireita != real){
				Tipos::erroTipagem(op, inteiro, real, booleano);
				break;
			}
		} 

		else if(op == maior || op == menor || op == maiorigual || op == menorigual){
				if(tipoNodoEsquerda == inteiro || tipoNodoEsquerda == real){
					if(tipoNodoDireita == booleano){
						erroCondicao(op, tipoNodoEsquerda, tipoNodoDireita, inteiro, booleano);
					}
				}
				return booleano;

		} else {
				std::cout << "Operacao nao suportada em operacoes binarias!" << std::endl;
		}
	}

	return inteiro;
}

void Tipos::erroCondicao(Operation operacao, Tipo primeiroRecebido, Tipo segundoRecebido, Tipo primeiroEsperado, Tipo segundoEsperado){
	std::cout << "A condicao do laco obteve uma operacao de " << opParaString(operacao) << " esperava " << tipoParaString(primeiroEsperado);
	if(segundoEsperado != indefinido){
		std::cout << " ou " + tipoParaString(segundoEsperado);
	}
	std::cout << " mas recebeu " << tipoParaString(primeiroRecebido) << " e " << tipoParaString(segundoRecebido) << "\n";
}

void Tipos::erroTipagem(Operation operacao, Tipo primeiroTipo, Tipo segundoTipo, Tipo recebido){
	std::cout<< "A operacao de " + opParaString(operacao) + " esperava " + tipoParaString(primeiroTipo);
	if(segundoTipo != indefinido){
		std::cout << " ou " + tipoParaString(segundoTipo);
	}
	std::cout << " como parâmetro, mas recebeu " << tipoParaString(recebido) << "." << std::endl;
}

void Tipos::tiposIncompativeis(Tipo primeiroTipo, Tipo segundoTipo){
	std::cout << "Erro semantico: operacao de assign esperava dois tipos compativeis, mas recebeu " <<
	tipoParaString(primeiroTipo) << " e " << tipoParaString(segundoTipo) << std::endl;
}

void Tipos::erroIndiceArranjo(Tipo primeiroTipo, Tipo segundoTipo){
	std::cout << "Erro semantico: lado da condicao esperava  " <<
	tipoParaString(primeiroTipo) << " mas recebeu " << tipoParaString(segundoTipo) << std::endl;
}

void Tipos::erroCondicaoLaco(Tipo esperado, Tipo recebido){
	std::cout << "Erro semantico: indice do arranjo esperava " <<
	tipoParaString(esperado) << " mas recebeu " << tipoParaString(recebido) << std::endl;
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
		case maior: return "maior";
		case maiorigual: return "maior ou igual";
		case menor : return "menor";
		case menorigual : return "menor ou igual";
		default: return "indefinida";
	}
}