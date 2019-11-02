
# Autor: João Phillipe
# Scrpit Test
#!/bin/bash
echo Digite o numero do lab de Hoje \(com dois digitos\), i.e. \(01\):
read num 
echo Digite \(s\)im para baixar os arquivos e \(n\)ao para somente testalos:
read baixa
echo Soh mais uma coisa, qual eh o nome do arquivo do lab, mesmo?
read lab
if [ "$baixa" = s ]; then
    #Baixa os testes#
    for j in 01 02 03 04 05 06 07 08 09 10
    do
    echo Baixando $j
    echo
    curl https://susy.ic.unicamp.br:9999/mc202ab/$num/dados/arq$j.in --insecure -O -s 
    curl https://susy.ic.unicamp.br:9999/mc202ab/$num/dados/arq$j.res --insecure -O -s 
    done
   a=0 
else
    a=1 
    mkdir TEST
    if [  -d "IN" ]; then
        cd IN
        cp *.in ../TEST
        cd ../RES
        cp *.res ../TEST
        cd ..
        cp $lab TEST
        cd TEST

    else
        cp *.in TEST
        cp *.res TEST
        cp *$lab TEST
    fi
fi

#Compila o 'arquivo.c'
gcc -ansi -pedantic -Wall -Werror -lm  -g $lab  
clear 
#roda os testes
for (( i=1; i<=10; i++ )); do
    arq="arq$(printf '%02d' $i)"
    echo ----Teste $i---- 
    valgrind --leak-check=full -q ./a.out < $arq.in > $arq.out
    diff $arq.out $arq.res 
done

if [ "$a" = 1 ]
then
    cd ..
fi

if [  -d "TEST" ]; then
    rm -fr TEST
else
    mkdir OUT
    mv *.out OUT  
    mkdir IN
    mv *.in IN  
    mkdir RES
    mv *.res RES  
fi
echo 
echo deu certo??
read resp
if [ "$resp" = sim ]
then
    echo Parabens, Agora eh soh submeter!
    echo Voce vai submeter agora??
    read resp2
    if [ "$resp2" = sim ]
    then
        firefox https://susy.ic.unicamp.br:9999/mc202ab/$num
        clear
    fi
else
    echo Tente Outra Vez, ainda da tempo!
fi
