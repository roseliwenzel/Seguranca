/*
Implementar um trabalho que seja capaz de cifrar e descifrar usando os algoritmos citados abaixo.
O programa deve usar como alfabeto os valores que cabem em um byte, ou seja, de 0x00 até 0xff.

4 -  Cifra de Substituição
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    char alfabeto[255], auxiliarAlfabeto[255], chave[255], linha[1];
    int cont = 0, dimin = 0, valorRandomico, aux = 0, opcao, numeroCaractere;

    FILE *fp = fopen("cifra.txt", "r+"); //abrindo o arquivo da cifra
    FILE *saida;
    //zerando as duas variáveis
    for(cont = 0; cont < 256; cont++){
        auxiliarAlfabeto[cont] = '\0';
        alfabeto[cont] = '\0';
    }
    //colocando o alfabeto accii num vetor
    for(cont = 32; cont < 256; cont++){
        auxiliarAlfabeto[cont] = cont;
        alfabeto[cont] = cont;
    }
    //pega a ultima posição, joga em outro vetor na posição que o randomico encontra
    for(dimin = 255; dimin >= 0; dimin--){
        if(dimin == 0){
            valorRandomico = 0;
        }else{
            valorRandomico = rand() %dimin;
        }
        chave[aux] = auxiliarAlfabeto[valorRandomico];
        auxiliarAlfabeto[valorRandomico] = auxiliarAlfabeto[dimin];
        aux++;
    }

    FILE *documentochave(fopen("resp.txt", "w+"));

    fprintf(documentochave,"%s", "Chave\n\n");
    for (cont = 32; cont < 256; cont++){
        fprintf(documentochave,"\n%c - %c", alfabeto[cont], chave[cont]);
    }
    fclose(documentochave);


    printf("********************************************\n");
    printf("*  Digite 1 para Criptografar o arquivo    *\n");
    printf("*  Digite 2 para Descriptografar o arquivo *\n");
    printf("********************************************\n");
    scanf("\n %d", &opcao);


    if(fp != NULL){ //contando número de caracteres contando no arquivo, pra criptografar
        while(!feof(fp)){
            linha[0] = '\0';
            fread(linha,sizeof(linha), 1, fp);
            if(linha[0] != '\0'){
                numeroCaractere++;
            }
        }
    }
    fclose(fp);
    fp = fopen("cifra.txt", "r+");





    return 0;
}
