#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){


    char caracterCriptografado[1], caracterDescriptografado[1], arquivoEntradaCrip[100], arquivoEntradaDescrip[100];
    int chave = 0, chaveAnterior = 0, contCaracter = 0;

    printf("\n Informe o nome do arquivo criptografado: ");
    gets(arquivoEntradaCrip);

    printf("\n Informe o nome do arquivo descriptografado: ");
    gets(arquivoEntradaDescrip);

    FILE *Criptografado;
    FILE *Descriptografado;
    FILE *Final;

    Criptografado = fopen(arquivoEntradaCrip, "rb");
    Descriptografado = fopen(arquivoEntradaDescrip, "rb");

    if(Criptografado != NULL && Descriptografado != NULL){
        while(!feof(Criptografado) && !feof(Descriptografado)){
            caracterCriptografado[0] = '\0';
            caracterDescriptografado[0] = '\0';
            fread(caracterCriptografado,sizeof(caracterCriptografado), 1, Criptografado);
            fread(caracterDescriptografado,sizeof(caracterDescriptografado), 1, Descriptografado);

            chave = (caracterDescriptografado[0] - caracterCriptografado[0] + 256) % 256;

            if(caracterCriptografado[0] == '\0' || caracterDescriptografado[0] == '\0'){
                if(chaveAnterior != 0 || contCaracter != 0){
                    if(chaveAnterior != chave){
                        printf("Criptografia nao e Ceasar");
                        break;
                    }
                }else{
                    chaveAnterior = chave;
                    contCaracter++;
                }
            }else{
                printf("Criptografia de Ceaser, chave: %d ", chave);
                break;
            }
        }
    }



    return 0;
}
