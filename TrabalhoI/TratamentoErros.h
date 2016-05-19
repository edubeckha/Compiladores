#pragma once

#include <iostream>

namespace Tipos{
	enum Tipo { inteiro, real, booleano, indefinido };
	enum Operation { plus, sub, times, divi, assign, maior, menor, maiorigual, menorigual, ande, ore, unibool, unario, declaracao, igual, diferente };
	
	Tipo opUnaria(Tipo tipoRecebido, Operation op);
	Tipo opBinaria(Tipo tipoNodoEsquerda, Tipo tipoNodoDireita, Operation op);


	void erroTipagem(Operation operacao, Tipo primeiroRecebido, Tipo segundoRecebido, Tipo esperado);
	bool precisaCoersao(Tipo tipoNodoEsquerda, Tipo tipoNodoDireita);

	std::string tipoParaString(Tipo tipo);
	std::string opParaString(Operation tipo);
}