###########################################################
# Created: 16/03/2013
#
# Author: Carla Negri Lintzmayer (carlanl@ic.unicamp.br)
#
# Revision: Zanoni Dias (21/03/2015)
###########################################################

#!/bin/bash

self="${0##*/}"

[ $# -eq 1 ] || 
{ echo "Uso: ./$self <laboratorio>"; exit 1; }

lab=$1

# Verificando se o comando curl está instalado:

hash curl 2>/dev/null || 
{ echo "Erro: este script necessita do programa curl instalado."; exit 1; }

# Compilando o programa:

echo "Compilando o programa..."

gcc -ansi -pedantic -Wall -Werror *.c -o $lab -lm
if [ $? -ne 0 ] ; then
    echo "Erro na compilação. Abortando testes."
    exit
fi

# Criando o diretorio de testes:

if [ ! -d "testes" ]; then
    echo "Criando diretorio de testes..."
    mkdir -p testes
fi

# Fazendo download dos arquivos de testes:

if [ ! -f "testes/testes.zip" ]; then
    echo "Baixando os arquivos de testes..."
    curl https://susy.ic.unicamp.br:9999/mc102qrst/$lab/aux/testes.zip --insecure -O -s -L

    echo "Descompactando os arquivos de testes..."
    mv testes.zip testes
    cd testes
    rm -rf arq*in arq*res
    unzip testes.zip
    cd ..
fi

# Executando os testes:
cd testes

echo "Executando os testes..."

for (( i=1; i<=10; i++ )); do
    arq="arq$(printf '%02d' $i)"
    ../$lab < $arq.in > $arq.out
done

# Comparando os resultados:
erros=0
for i in `ls -1 arq*in`; do
    arq=${i%.in}

    cmp=$(diff $arq.res $arq.out)

    if [ "$cmp" != "" ]; then
        echo
        echo "========================================="
        echo "Erro encontrado com a entrada '$arq.in':"
        echo
        echo ">>> Saida esperada (SuSy):"
        cat $arq.res
        echo ">>> Saida do seu programa:"
        cat $arq.out
        echo "========================================="
        rm $arq.out
        erros=$(($erros+1))
    fi
done

echo
echo "Total de erros encontrados: $erros"
cd ..
