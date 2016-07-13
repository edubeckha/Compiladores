#!/bin/bash

SUCESSES="../testes/sucesses"

make all
echo "*******************************************"
echo "Teste dos casos de sucesso: não geram erros"
echo "*******************************************"
cor=0

for i in {0..6}; do
./myparse < ${SUCESSES}/inputs/input_1.${i} > output

diff -bBw ${SUCESSES}/expected/expected_1.${i} output  > differ

echo "===================="
echo "Teste da versão 1.${i}"

if [ -s differ ];
then
	echo ""
	echo "** Falha no teste da versão 1.${i}"
	echo ""
	echo ****Esperado:
	echo ""
	cat ${SUCESSES}/expected/expected_1.${i}
	echo ""
	echo ****Obtido: 
	cat output
	echo ""
else
	echo ""
	echo "** Sucesso no teste da versão 1.${i}"
	let cor++
	echo ""
fi

done
echo "---------------"
echo "Fim dos testes."
echo "---------------"
echo Passou em ${cor}.
echo Falhou em $(( i - cor )).

rm output
rm differ
