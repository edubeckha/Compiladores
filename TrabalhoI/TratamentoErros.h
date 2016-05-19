#pragma once

#include "ast.h"

namespace Tipos{

	AST::Tipo opUnaria(AST::Tipo tipoRecebido, AST::Operation op);
	AST::Tipo opBinaria(AST::Tipo tipoNodoEsquerda, AST::Tipo tipoNodoDireita, AST::Operation op);


	void erroTipagem(AST::Operation operacao, AST::Tipo primeiroRecebido, AST::Tipo segundoRecebido, AST::Tipo esperado);
	bool precisaCoersao(AST::Tipo tipoNodoEsquerda, AST::Tipo tipoNodoDireita);
}