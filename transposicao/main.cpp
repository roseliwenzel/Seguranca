/*
Implementar um trabalho que seja capaz de cifrar e descifrar usando os algoritmos citados abaixo.
O programa deve usar como alfabeto os valores que cabem em um byte, ou seja, de 0x00 até 0xff.

2 - Cifra de Transposição

o da matriz - matriz transposta

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


int main()
{
    char linha[1];
    int opcao, chave, numlinhas = 0, linhamatriz, colunamatriz, k;
    double qtdcaracteres = 0.0;
    FILE *fp; //abrindo o arquivo da cifra
    FILE *saida;

    printf("********************************************\n");
    printf("*  Digite 1 para Criptografar o arquivo    *\n");
    printf("*  Digite 2 para Descriptografar o arquivo *\n");
    printf("********************************************\n");
    scanf("\n %d", &opcao);

    printf("Informe a chave: ");
    scanf("%d", &chave);

    //criando os arquivos de resposta e cifra
    if (opcao == 1){
        fp = fopen("cifra.txt", "r+"); //abrindo o arquivo da cifra
        saida = fopen("respostacriptografado.dat", "wb+");
    }else{
        fp = fopen("respostacriptografado.dat", "rb+");
        saida = fopen("respostadescriptografado.txt", "w+");
    }

    //contando o número de caracteres
    if (fp != NULL){
        while(!feof(fp)){
            linha[0] = '\0';
            fread(linha, sizeof(linha), 1, fp);
            //para criptografar
            if (linha[0] != '\0'){
                qtdcaracteres++;
            }
        }
    }
    //quantidade de linhas necessárias para gravar a frase na matriz
    numlinhas = ceil(qtdcaracteres/chave);

    fclose(fp);

     //criando os arquivos de resposta e cifra
    if (opcao == 1){
        fp = fopen("cifra.txt", "r+"); //abrindo o arquivo da cifra
        saida = fopen("respostacriptografado.dat", "wb+");
    }else{
        fp = fopen("respostacriptografado.dat", "rb+");
        saida = fopen("respostadescriptografado.txt", "w+");
    }

    //criando as duas matrizes para criptografar ou descriptografar
    char matrizC[1][numlinhas][chave];
    char matrizD[1][chave][numlinhas];

    if (fp != NULL){
        while(!feof(fp)){ //gravando as informações na matriz - escreve por linha
             if (opcao == 1) {
                for (linhamatriz = 0; linhamatriz < numlinhas; linhamatriz++){
                    for(colunamatriz = 0; colunamatriz < chave; colunamatriz++){
                        linha[0] = ' ';
                        fread(linha, sizeof(linha), 1, fp);
                        matrizC[0][linhamatriz][colunamatriz] = linha[0];
                    }
                }
            } else {
                for (linhamatriz = 0; linhamatriz < chave; linhamatriz++){
                    for(colunamatriz = 0; colunamatriz < numlinhas; colunamatriz++){
                        linha[0] = ' ';
                        fread(linha, sizeof(linha), 1, fp);
                        matrizD[0][linhamatriz][colunamatriz] = linha[0];
                    }
                }
            }
            break;
        }
        fclose(fp);
        if (opcao == 1) { //lendo as informações da matriz transposta - lendo por coluna
            for(colunamatriz = 0; colunamatriz < chave; colunamatriz++){
                for (linhamatriz = 0; linhamatriz < numlinhas; linhamatriz++){
                    k = matrizC[0][linhamatriz][colunamatriz];
                    fwrite(&k,1,1,saida);
                }
            }
        } else {
            for(colunamatriz = 0; colunamatriz < numlinhas; colunamatriz++){
                for (linhamatriz = 0; linhamatriz < chave; linhamatriz++){
                    k = matrizD[0][linhamatriz][colunamatriz];
                    fwrite(&k,1,1,saida);
                }
            }
        }
        fclose(saida);
    } else {
        printf("Nao e possivel abrir o arquivo!\n");
    }
    return 0;
}
