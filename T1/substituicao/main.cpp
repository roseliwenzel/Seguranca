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
    char alfabeto[256], auxiliarAlfabeto[256], chave[256], linha[1];
    int cont = 0, dimin = 0, valorRandomico, aux = 0, opcao, numeroCaractere = 0, i, k;

    srand(time(NULL));

    FILE *fp;
    FILE *saida;
    FILE *documentochave;

    //colocando o alfabeto accii num vetor
    for(cont = 0; cont < 256; cont++){
        auxiliarAlfabeto[cont] = cont;
        alfabeto[cont] = cont;
    }

    printf("********************************************\n");
    printf("*  Digite 1 para Criptografar o arquivo    *\n");
    printf("*  Digite 2 para Descriptografar o arquivo *\n");
    printf("********************************************\n");
    scanf("\n %d", &opcao);

    if(opcao == 1){// se for criptografar ele cria a chave
        //pega a ultima posição, joga em outro vetor na posição que o randomico encontra
        for(dimin = 255; dimin >= 0; dimin--){
            if(dimin == 0){
                valorRandomico = 0;
            }else{
                valorRandomico = rand() %dimin;
            }
            chave[aux] = auxiliarAlfabeto[valorRandomico]; //Joga na chave na posição aux o valor do alfabeto na posição randomica
            auxiliarAlfabeto[valorRandomico] = auxiliarAlfabeto[dimin]; //Joga a ultima posição da auxiliar na posição do randomico
            aux++;
        }

        documentochave = fopen("chave.dat", "wb+");
        for(i = 0; i <= 255; i++){
            k = chave[i];
            fwrite(&k,1,1,documentochave);
        }

    }else{//se for decriptar ele pega a ultima chave gerada
        k = 0;
        documentochave = fopen("chave.dat", "rb+");
        if(documentochave != NULL){
            while(!feof(documentochave)){
                fread(linha,sizeof(linha), 1, documentochave);
                if(k < 256){
                    chave[k] = linha[0];
                    k++;
                }
            }
        }
    }
    fclose(documentochave);

    //criando os arquivos de resposta e cifra
    if (opcao == 1){
        fp = fopen("cifra.txt", "r+"); //abrindo o arquivo da cifra
        saida = fopen("respostacriptografado.dat", "wb+");
    }else{
        fp = fopen("respostacriptografado.dat", "rb+");
        saida = fopen("respostadescriptografado.txt", "w+");
    }

    if(fp != NULL){ //contando número de caracteres contando no arquivo, pra criptografar
        while(!feof(fp)){
            linha[0] = '\0';
            fread(linha,sizeof(linha), 1, fp);
            if(linha[0] != '\0'){
                numeroCaractere++;
            }
        }
    }

    printf("%d", numeroCaractere);
    system("pause");

    fclose(fp);
    //criando os arquivos de resposta e cifra
    if (opcao == 1){
        fp = fopen("cifra.txt", "r+"); //abrindo o arquivo da cifra
    }else{
        fp = fopen("respostacriptografado.dat", "rb+");
    }
    if (fp != NULL){
        aux = 0;
        while(!feof(fp)){ //ler um por um
            if(aux < numeroCaractere){ //controle para não ler mais caracteres do que contém no arquivo
                fread(linha,sizeof(linha), 1, fp); //escrevendo no arquivo
                if (opcao == 1){
                    k = chave[linha[0]];
                }else{
                    for(i = 0; i < 256; i++){
                        if(chave[i] == linha[0]){
                            k = alfabeto[i];
                        }
                    }
                }
                fwrite(&k, 1, 1, saida);
                aux++;
            }else{
                break;
            }
        }
        fclose(fp);
        fclose(saida);
    } else {
        printf("Nao e possivel abrir o arquivo!\n");
    }


    return 0;
}
