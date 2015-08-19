/*
Implementar um trabalho que seja capaz de cifrar e descifrar usando os algoritmos citados abaixo.
O programa deve usar como alfabeto os valores que cabem em um byte, ou seja, de 0x00 até 0xff.

3 -  Cifra de Vigenère

repete a palavra

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TAM 200


int main()
{
    char linha[1], chave[TAM];
    int opcao, aux = 0, controleCaractere = 0, numeroCaractere = 0, i, tamChave = 0, k;
    FILE *fp; //abrindo o arquivo da cifra
    FILE *saida;

    //deixando a chave zeara
    for(i=0; i<TAM; i++){
        chave[i] = '\0';
    }

    printf("********************************************\n");
    printf("*  Digite 1 para Criptografar o arquivo    *\n");
    printf("*  Digite 2 para Descriptografar o arquivo *\n");
    printf("********************************************\n");
    scanf("\n %d", &opcao);

    fflush(stdin);
    printf("Informe a chave: ");
    gets(chave);

    //criando os arquivos de resposta e cifra
    if (opcao == 1){
        fp = fopen("cifra.txt", "r+"); //abrindo o arquivo da cifra
        saida = fopen("respostacriptografado.dat", "wb+");
    }else{
        fp = fopen("respostacriptografado.dat", "rb+");
        saida = fopen("respostadescriptografado.txt", "w+");
    }

    for(i = 0; i < TAM; i++){ //pegando tamanho da chave
        if (chave[i] != '\0'){
            tamChave++;
        }
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
    fclose(fp);

    if (opcao == 1){
        fp = fopen("cifra.txt", "r+"); //abrindo o arquivo da cifra
    }else{
        fp = fopen("respostacriptografado.dat", "rb+");
    }

    if (fp != NULL){
        while(!feof(fp)){ //ler um por um
            controleCaractere++;
            if (aux == tamChave){
                aux = 0;
            }
            if(controleCaractere <= numeroCaractere){ //controle para não ler mais caracteres do que contém no arquivo
                fread(linha,sizeof(linha), 1, fp); //escrevendo no arquivo
                if (opcao == 1){
                    k = (linha[0] + chave[aux])%256;
                    fwrite(&k, 1, 1, saida);
                }else{
                    k = (linha[0] + 256 - chave[aux])%256;
                    fwrite(&k, 1, 1, saida);
                }
                aux++;
            } else{
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
