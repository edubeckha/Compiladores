#!/bin/bash

SUCESSES=../testes/sucesses

make all

echo "Teste dos casos de sucesso: não geram erros"

for i in {0..1}; do

./myparse < $SUCESSES/inputs/input_1.$i > output

diff $SUCESSES/expected/expected_1.$i output  > differ

echo Teste da versão 1.$i

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

rm output
rm differ
