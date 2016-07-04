#!/bin/bash

SUCESSES=$HOME/projetos/compilladores_parte2/TrabalhoII/testes/sucesses

make

for i in {0..6}; do

./myparse < SUCESSES/inputs/input_1.$i > output

diff output SUCESSES/expected/expected_1.$i > differ

echo "Testando versão 1.$i"

if [ -s differ ];
then
	echo "** Falha no teste da versão 1.$i"
	echo ****Esperado:
	cat $SUCESSES/expected/expected_1.$i
	echo ****Obtido: 
	cat output
else
	echo "** Sucesso no teste da versão 1.$i"
fi

done
