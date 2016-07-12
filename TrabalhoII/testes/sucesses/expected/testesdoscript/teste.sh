#!/bin/bash

SUCESSES=../testes/sucesses/expected/testesdoscript

for i in {0..1}; do

diff $SUCESSES/expected_1.$i $SUCESSES/output_1.$i  > differ

echo Teste da versão 1.$i

if [ -s differ ];
then
	echo "** Falha no teste da versão 1.$i"
	echo ****Esperado:
	cat $SUCESSES/expected_1.$i
	echo ****Obtido: 
	cat $SUCESSES/output_1.$i
else
	echo "** Sucesso no teste da versão 1.$i"
fi

rm $SUCESSES/output_1.$i

done

rm differ
