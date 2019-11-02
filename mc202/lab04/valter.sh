
# Autor: João Phillipe
# Scrpit Test
#!/bin/bash
echo -e "\e[92mDigite o numero do lab de Hoje (com dois digitos), i.e. (01):"
read num 
echo -e "\e[92mDigite (s)im para baixar os arquivos e (n)ao para somente testalos:"
read baixa
echo -e "\e[92mSoh mais uma coisa, qual eh o nome do arquivo do lab, mesmo?"
read lab

if [ "$baixa" = s ]; then
    j=1
    k=1
    #Baixa os testes#
    arq="arq$(printf '%02d' $j)"
    echo "Baixando $(printf '%02d' $j)"
    echo
    curl https://susy.ic.unicamp.br:9999/mc202ab/$num/dados/$arq.in --insecure -O -s 
    curl https://susy.ic.unicamp.br:9999/mc202ab/$num/dados/$arq.res --insecure -O -s 
    PARADA=""
    while ["$PARADA" != ""]
    do
        j=$[$j+1]
        arq="arq$(printf '%02d' $j)"
        curl https://susy.ic.unicamp.br:9999/mc202ab/$num/dados/$arq.in --insecure -O -s 
        curl https://susy.ic.unicamp.br:9999/mc202ab/$num/dados/$arq.res --insecure -O -s 
        PARADA=$(grep HTML $arq.in)
        if ["$PARADA" != ""]
        then 
            echo "Baixando $(printf '%02d' $j)"
            echo
        fi
    done
    j=$[$j-1]
    rm -f $arq.in $arq.res
    a=0 

else 
    a=1
    mkdir TEST
    if [  -d "IN" ]; then
        cd IN
        j=$(ls -l | grep -v ^l | wc -l)
        j=$[$j-1]
        cp *.in ../TEST
        cd ../RES
        cp *.res ../TEST
        cd ..
        cp *.c TEST
        cp *.h TEST
        cp $lab TEST
        cd TEST

    else
        cp *.in TEST
        cp *.res TEST
        cp $lab TEST
        cp *.h TEST
        cp *.c   TEST
        cd TEST
    fi
fi

#Compila o 'arquivo.c'
gcc -ansi -std=gnu99 -Wpedantic -Wall -Werror -lm  -g $lab  
if [ $? -ne 0 ] ; then
    echo -e "\e[93mERRO NA COMPILAÇÃO,ESSE \e[4mNEGOCIO\e[24m NAO COMPILA"
    echo -e "\e[93mTente Outra Vez, ainda da tempo!"
    if [ "$a" = 0 ] ; then

        mkdir OUT
        mv *.out OUT  
        mkdir IN
        mv *.in IN  
        mkdir RES
        mv *.res RES 
    fi
    if [  -d "TEST" ]; then
        rm -fr TEST
    fi
    exit
fi
clear 
#roda os testes
echo "Executando os testes..."
erros=0
for (( i=1; i<=$j; i++ )); do
    arq="arq$(printf '%02d' $i)"
    echo ----Teste $i---- 
    valgrind --leak-check=full -q ./a.out < $arq.in > $arq.out

    cmp=$(diff $arq.res $arq.out)

    if [ "$cmp" != "" ]; then
        echo
        echo "========================================="
        echo "Erro encontrado com a entrada '$arq.in':"
        echo
        echo ">>> Saida esperada (SuSy):"
        cat $arq.res
        echo
        ">>> Saida do seu programa:"
        cat $arq.out
        echo
        "========================================="
        rm $arq.out
        erros=$(($erros+1))
    fi
done

echo
echo -e "\e[91m\e[4m\e[5mTotal de erros lógicos:$erros \e[0m"

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
echo -e "\e[93m Deu certo??"
read resp
if [ "$resp" = sim ]
then
    echo -e "\e[5m\e[1m\e[96m\e[4m PARABÉNS\e[25m\e[21m\e[24m, Agora eh soh submeter!"
    echo -e "\e[92mVocê vai submeter agora??"
    read resp2
    if [ "$resp2" = sim ]
    then
        firefox https://susy.ic.unicamp.br:9999/mc202ab/$num
        clear
    fi
else
    echo -e "\e[93mTente Outra Vez, ainda da tempo!"
fi
