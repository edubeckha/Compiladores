#!/bin/bash

SUCESSES="../testes/sucesses/expected/testesdoscript"

for i in {0..2}; do

# diff ${SUCESSES}/expected_1.$i ${SUCESSES}/output_1.$i  > differ
diff expected_1.${i} output_1.${i}  > differ
echo ""
echo "==========Inicio=========="
echo Teste da versão 1.${i}

if [ -s differ ];
then
	echo "** Falha no teste da versão 1.${i}"
	echo ****Esperado:
	# cat $SUCESSES/expected_1.${i}
	cat expected_1.${i}
	echo ****Obtido: 
	# cat $SUCESSES/output_1.${i}
	cat output_1.${i}
else
	echo "** Sucesso no teste da versão 1.${i}"
fi

echo "----------Fim----------"
# rm $SUCESSES/output_1.$i

done

rm differ
