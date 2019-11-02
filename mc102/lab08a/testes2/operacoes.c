/*Operacao de adicao*/
for(i = 0; i < tamvet2; i++)
{
    if((vet[i] + vet2[i]) >= 10)
    {
        result[i] = (vet[i] + vet2[i]) % 10;
        if(i == tamvet - 1)
        {
            tamvet++;
            vet[i + 1] = 1;
        }
        else
        {
            vet[i + 1]++;
        }
    }
    else
    {
        result[i] = vet[i] + vet2[i];
    }
}
for(j = i; j < tamvet; j++)
{    
    result[j] = vet[j];
}

/*Operacao de subtracao*/
for(i = 0; i < tamvet2; i++, flag = 0)
{
    if((vet[i] - vet2[i]) >= 0)
    {
        result[i] = vet[i] - vet2[i];
    }
    else if((vet[i] - vet2[i]) < 0)
    {
        for(j = (i + 1); (j <= tamvet) && (flag == 0); j++)
        {
            if(vet[j] != 0)
            {
                for(k = j; k > i; k--)
                {
                    if(vet[k] == 0)
                    {
                        vet[k] = 9;
                    }
                    else
                    {
                        vet[k]--;
                    }
                }
                vet[i] += 10;
                flag = 1;
                if(vet[tamvet - 1] == 0)
                {
                    tamvet--;
                }
            }
        }
        result[i] = vet[i] - vet2[i];
    }
}
for(j = i; j < tamvet; j++)
{    
    result[j] = vet[j];
}
for(i = 0, contador = 0; i < tamvet; i++)
{
    if(vet[i] == vet2[i])
    {
        contador++;
    }
}
if(contador == tamvet)
{
    tamvet = 1;
}

