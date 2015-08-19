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

    }



    return 0;
}
