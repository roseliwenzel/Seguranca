/*
Implementar um trabalho que seja capaz de cifrar e descifrar usando os algoritmos citados abaixo.
O programa deve usar como alfabeto os valores que cabem em um byte, ou seja, de 0x00 até 0xff.

1- Cifra de Céasar:
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    char linha[1];
    int opcao, chave;
    FILE *fp = fopen("cifra.txt", "r+"); //abrindo o arquivo da cifra
    FILE *saida;
    if (fp != NULL){

        printf("********************************************\n");
        printf("*  Digite 1 para Criptografar o arquivo    *\n");
        printf("*  Digite 2 para Descriptografar o arquivo *\n");
        printf("********************************************\n");
        scanf("\n %d", &opcao);

        printf("Informe a chave: ");
        scanf("%d", &chave);

        //criando os arquivos de resposta
        if (opcao == 1){
            saida = fopen("respostacriptografado.txt", "w+");
        }else{
            saida = fopen("respostadescriptografado.txt", "w+");
        }

        while(!feof(fp)){
            linha[0] = '\0';
            fread(linha, sizeof(linha), 1, fp);
            //para criptografar
            if (opcao == 1){
                if (linha[0] != '\0'){
                    fprintf(saida, "%c", (linha[0] + chave)%256); //256 para ficar dentro da tabela accii
                }

            } //para descriptografar
            else {
                if (linha[0] != '\0'){
                    fprintf(saida, "%c", (linha[0]- chave + 256)%256);
                }
            }
        }
    } else {
        printf("Nao e possivel abrir o arquivo!\n");
    }
    return 0;
}
