#From anywhere; for everybody!
# Scrpit: Test for lab's COMP 
#!/bin/bash

#PERGUNTAS USUAIS AO USUARIO    
echo -e "\e[92mDigite o numero do lab de Hoje (com dois digitos), i.e. (01):"
read num 
echo -e "\e[92mDigite (\e[93ms\e[92m)im para baixar os arquivos e (\e[93mn\e[92m)ao para somente testalos:"
read baixa
echo -e "\e[92mVocê quer usar o Valgrind,(\e[93ms\e[92m)im || (\e[93mn\e[92m)ao?"
read val
function Online {
wget -q --tries=10 --timeout=20 --spider http://google.com
if [[ $? -eq 0 ]]; then
        on=1
else
    on=0
fi
}
#Trecho de codigo comentado para, evitar tempo perdido
#echo -e "\e[92mSoh mais uma coisa, qual eh o nome do arquivo do lab, mesmo?"
#read lab

on=0
#Caso a o usuario queira baixar os Testes
if [ "$baixa" = s ]; then
    trap 'rm  *.in *.res -f ; echo "NÃO ME MATE!!" ; exit' 0 1 2 3 15  
    j=1
    k=1
    #Baixa os testes#
    arq="arq$(printf '%02d' $j)"
    echo "Baixando $(printf '%02d' $j)"
    echo
    #Comando usado para fazer o download do SuSy
    curl https://susy.ic.unicamp.br:9999/mc202ab/$num/dados/$arq.in --insecure -O -s 
    curl https://susy.ic.unicamp.br:9999/mc202ab/$num/dados/$arq.res --insecure -O -s 
    PARADA=""
    # A Parada se da quando nao eh valido o arquivo baixado
    while ["$PARADA" != ""]
    do
        Online
        if [ "$on" = 0 ]; then
            echo "Putz.. Sua internet não tá boa"
            exit
        fi
        j=$[$j+1]
        arq="arq$(printf '%02d' $j)"
        curl https://susy.ic.unicamp.br:9999/mc202ab/$num/dados/$arq.in --insecure -O -s 
        curl https://susy.ic.unicamp.br:9999/mc202ab/$num/dados/$arq.res --insecure -O -s 
        PARADA=$(grep HTML $arq.in)
        if ["$PARADA" != ""]
        then 
            echo "Baixando $(printf '%02d' $j)"
            echo
            if [ ! -e "$arq.in"  ]; then
            echo "Putz.. Sua internet não tá boa"
            echo "Não consigo baixar os arquivos direito...."
            echo "Tente Novamente mais tarde"
            exit
            fi
        fi
    done
    j=$[$j-1]
    rm -f $arq.in $arq.res
    baixado=0 
    trap 'rm  *.in *.res -f ; echo "NÃO ME MATE!!" ; exit'  1 2 3 15 
    #Caso o usuario nao queira baixar os Testes
else 
    baixado=1
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
        #cp $lab TEST
        cd TEST

    else
        cp *.in TEST
        cp *.res TEST
       # cp $lab TEST
        cp *.h TEST
        cp *.c   TEST
        cd TEST
    fi
trap 'rm -rf ../TEST ; echo "NÃO ME MATE!!!" ; exit'   1 2 3 15 

fi
#Compila o 'arquivo.c'

#Mudar aqui o $lab no fim por *.c
gcc -ansi -std=gnu99 -Wpedantic -Wall -Werror -lm  -g *.c  
#Caso de Erro de Compilacao
if [ $? -ne 0 ] ; then
    echo -e "\e[93mERRO NA COMPILAÇÃO,ESSE \e[4mNEGOCIO\e[24m NAO COMPILA"
    echo -e "\e[93mTente Outra Vez, ainda da tempo!"
    if [ "$baixado" = 0 ] ; then

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
function echo_erro {
    echo -e "\e[91m\e[4m\e[5mOs erros até o Teste $i  "
    echo -e "Total de erros:$erros \e[0m"
}
function Organiza {
if [ "$baixado" = 0 ] ; then
    mkdir OUT > /dev/null 2>&1
    mv *.out OUT > /dev/null 2>&1 
    mkdir IN > /dev/null 2>&1
    mv *.in IN > /dev/null 2>&1
    mkdir RES > /dev/null 2>&1
    mv *.res RES > /dev/null 2>&1
else
    cd ..
fi
if [  -d "TEST" ]; then
    rm -fr TEST
fi
}
#Roda os Testes


echo "Executando os testes..."
erros=0
trap ' Organiza ; clear ; echo_erro  ; exit'  1 2 3 15 
for (( i=1; i<=$j; i++ )); do
    arq="arq$(printf '%02d' $i)"
    echo ----Teste $i---- 
    if [ "$val" = s ] ; then
        valgrind --leak-check=full -q ./a.out < $arq.in > $arq.out
    else
        ./a.out < $arq.in > $arq.out

    fi
    #Compara com os arquivos da Resolucao
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
echo -e "\e[91m\e[4m\e[5mTotal de erros lógicos:$erros \e[0m"

if [ "$baixado" = 1 ]
then
    cd ..
fi
#Verifica se Existe a pasta TEST
if [  -d "TEST" ]; then
    rm -fr TEST
else
    mkdir OUT > /dev/null 2>&1
    mv *.out OUT  
    mkdir IN > /dev/null 2>&1
    mv *.in IN  
    mkdir RES > /dev/null 2>&1
    mv *.res RES  
fi
echo 
trap 'rm *.out -f ; exit'  1 2 3 15 
echo -e "\e[93m Deu certo??"
read resp
#Entra no site do SuSy caso o usuario responda sim
if [ "$resp" = sim ] || [ "$resp" = s ]
then
    echo -e "\e[5m\e[1m\e[96m\e[4m PARABÉNS\e[25m\e[21m\e[24m, Agora eh soh submeter!"
    echo -e "\e[92mVocê vai submeter agora??"
    read resp2
    if [ "$resp2" = sim ] || [ "$resp2" = s ]
    then
        nohup firefox https://susy.ic.unicamp.br:9999/mc202ab/$num & > /dev/null
        rm nohup.out -f
        clear
    fi
else
    echo -e "\e[93mTente Outra Vez, ainda da tempo!"
fi
