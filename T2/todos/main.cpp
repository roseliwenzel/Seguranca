#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int Substituicao(char arquivoCriptografado[100], char arquivoDescriptografado[100]);
int Transposicao(char arquivoCriptografado[100], char arquivoDescriptografado[100], double qtdCaracteres, int chave, char *textoCompleto);
int Ceasar(char arquivoCriptografado[100], char arquivoDescriptografado[100]);
int Vigener(char arquivoCriptografado[100], char arquivoDescriptografado[100]);

int aux = 0;

int main()
{
    char arquivoCriptografado[100], arquivoDescriptografado[100], characterContador[1], *textoCompleto, *textoDescrip;
    int i = 1, j = 0, ret, charInt, controleParar, continua = 0;
    double qtdCaracteres = 0;

    //Para ler a qtd de caracteres do arquivo original
    FILE *arqDescriptografado;

    printf("Digite o nome do arquivo descriptografado:\n");
    gets(arquivoDescriptografado);

    printf("Digite o nome do arquivo criptografado:\n");
    gets(arquivoCriptografado);

    //chama a função para verificar se o arquivo foi criptografado com ceasar
    Ceasar(arquivoCriptografado, arquivoDescriptografado);
    //se não encontrou a chave
    if(aux == 0){
        //chama a função para verificar se o arquivo foi criptografado com substituição
        Substituicao(arquivoCriptografado, arquivoDescriptografado);
    }

    if(aux == 0){
        arqDescriptografado = fopen(arquivoDescriptografado, "rb");
        //Controle feito para pegar a quantidade de caracteres do arquivo, para calcular o tamanho da matriz na função de trasnposição.
        if(arqDescriptografado != NULL){
            while(!feof(arqDescriptografado)){
                characterContador[0] = '\0';
                fread(characterContador,1,1,arqDescriptografado);
                if(characterContador[0] != '\0'){
                    qtdCaracteres ++;
                }
            }
        }else{
            printf("\nArquivo nao encontrado\n");
            system("pause");
        }
        fclose(arqDescriptografado);
        //Texto completo e original e o texto descriptografado, com tamanho do numero de caracteres do original
        textoCompleto        = (char*) malloc((qtdCaracteres) * sizeof(char));
        textoDescrip = (char*) malloc((qtdCaracteres) * sizeof(char));

        arqDescriptografado = fopen(arquivoDescriptografado, "rb");

        i = 0;

        //grava o valor da tabela ascii, inteiros fazendo o modulo de 256 para ficar positivo
        if(arqDescriptografado != NULL){
             while(!feof(arqDescriptografado) ){
                textoDescrip[0] = '\0';
                fread(textoDescrip,sizeof(char),1,arqDescriptografado);

                if(textoDescrip[0] != '\0'){
                    charInt = (textoDescrip[0] + 256) % 256;
                    textoCompleto[i] = charInt;
                    i++;
                }
             }
        }else{
            printf("\nArquivo nao encontrado\n");
        }

        fclose(arqDescriptografado);

        controleParar = 100;
        continua    = 0;
        //Como transposição não é o ultimo, feito controle para saber se quer continuar ou gerar vingenere
        for(j = 2; j <= qtdCaracteres; j++){
            if(j < controleParar){
                ret = Transposicao(arquivoCriptografado, arquivoDescriptografado, qtdCaracteres, j, textoCompleto);
            }
            else{
                printf("Laço repetiu %d",controleParar);
                printf(" deseja repetir por mais 50(força bruta, transposicao)?[1(y)/0(n)]\n",controleParar);
                scanf("%d",&continua);
                if(continua == 1){
                    controleParar += 50;
                }
                else{
                    break;
                }
            }
            if(ret == 1){
                break;
            }
        }
    }

    if(aux == 0){
        printf("\nNao e transposicao.\n");
        Vigener(arquivoCriptografado, arquivoDescriptografado);
    }
    return 0;
}

int Ceasar(char arquivoCriptografado[100], char arquivoDescriptografado[100]){
    char charCriptografado[1], charDescriptografado[1];
    int chaveAnt = 0, chaveAtu = 0, controleCaracter = 0;

    FILE *arqCriptografado;
    FILE *arqDescriptografado;

    arqCriptografado = fopen(arquivoCriptografado, "rb");
    arqDescriptografado = fopen(arquivoDescriptografado, "rb");

    if(arqCriptografado != NULL && arqDescriptografado != NULL){
        while(!feof(arqCriptografado) && !feof(arqDescriptografado)){
            charCriptografado[0] = '\0';
            charDescriptografado[0] = '\0';

            fread(charCriptografado,sizeof(charCriptografado),1,arqCriptografado);
            fread(charDescriptografado,sizeof(charDescriptografado),1,arqDescriptografado);

            chaveAtu = (charCriptografado[0] - charDescriptografado[0] + 256) % 256;

            if(charCriptografado[0] != '\0' || charDescriptografado[0] != '\0'){
                if(chaveAnt != 0 || controleCaracter != 0){
                    if(chaveAtu != chaveAnt){
                        printf("Nao e Ceasar!\n");
                        fclose(arqCriptografado);
                        fclose(arqDescriptografado);
                        return 0;
                    }
                }else{
                    chaveAnt = chaveAtu;
                    controleCaracter++;
                }
            }
        }
    }else{
        printf("Nao foi possivel abrir o arquivo");
        return 0;
    }
    fclose(arqCriptografado);
    fclose(arqDescriptografado);
    printf("Ceasar. %d\n", chaveAnt);
    aux = 1;
    return 0;
}

int Substituicao(char arquivoCriptografado[100], char arquivoDescriptografado[100]){
    char charCriptografado[1], charDescriptografado[1];
    int i = 0, charCriptografadoInt = 0, charDescriptografadoInt = 0, chave[256];

    FILE *arqCriptografado;
    FILE *arqDescriptografado;

    arqCriptografado = fopen(arquivoCriptografado, "rb");
    arqDescriptografado = fopen(arquivoDescriptografado, "rb");

    for(i = 0 ; i < 256; i++){
        chave[i] = '\0';
    }

    i = 0;
    if(arqCriptografado != NULL && arqDescriptografado != NULL){
        while(!feof(arqCriptografado) || !feof(arqDescriptografado)){
            if(feof(arqCriptografado)){
                fclose(arqCriptografado);
                fclose(arqDescriptografado);
                printf("Nao e Substituicao!");
                return 0;
            }
            if(feof(arqDescriptografado)){
                fclose(arqCriptografado);
                fclose(arqDescriptografado);
                printf("Nao e Substituicao!");
                return 0;
            }
            i++;
            charCriptografado[0] = '\0';
            charDescriptografado[0] = '\0';
            fread(charCriptografado,sizeof(charCriptografado),1,arqCriptografado);
            fread(charDescriptografado,sizeof(charDescriptografado),1,arqDescriptografado);
            charCriptografadoInt = (charCriptografado[0] + 256) % 256;
            charDescriptografadoInt = (charDescriptografado[0] + 256) % 256;

            if(charCriptografado[0] != '\0' || charDescriptografado[0] != '\0'){
                if(chave[charCriptografadoInt] == '\0'){
                    chave[charCriptografadoInt] = charDescriptografadoInt;
                }else{
                    if(chave[charCriptografadoInt] != charDescriptografadoInt){
                        fclose(arqCriptografado);
                        fclose(arqDescriptografado);
                        printf("Nao e Substituicao!\n");
                        return 0;
                    }
                }
            }
        }
    }
    else{
        printf("Nao foi possivel abrir o arquivo.");
        return 0;
    }
    fclose(arqCriptografado);
    fclose(arqDescriptografado);
    printf("Substituicao!");
    aux = 1;
    return 0;
}

int Transposicao(char arquivoCriptografado[100], char arquivoDescriptografado[100], double qtdCaracteres, int chave, char *textoCompleto){
    char *textoCrip;
    int i = 0, qtdLinhas = 0, linha = 0, coluna = 0, charCriptografadoInt = 0;
    textoCrip    = (char*) malloc((qtdCaracteres) * sizeof(char));

    if(chave == 0){
        chave = 1;
    }
    qtdLinhas = ceil(qtdCaracteres/chave);
    char matrizCripografada[1][chave][qtdLinhas];

    FILE *arqCriptografado;

    arqCriptografado = fopen(arquivoCriptografado, "rb");
    if(arqCriptografado != NULL){
         while(!feof(arqCriptografado) ){
            for(linha = 0; linha < chave; linha ++){
                for(coluna = 0; coluna < qtdLinhas; coluna++){
                    textoCrip[0] = '\0';
                    fread(textoCrip,sizeof(char),1,arqCriptografado);
                    if(textoCrip[0] != '\0'){
                        charCriptografadoInt = (textoCrip[0] + 256) % 256;
                        matrizCripografada[0][linha][coluna] = charCriptografadoInt;
                        i++;
                    }
                }
            }
         }
    }else{
        printf("Nao foi possivel abrir o arquivo");
        return 0;
    }

    i = 0;
    for(coluna = 0; coluna < qtdLinhas; coluna++){
        for(linha = 0; linha < chave; linha ++){
            if(i < qtdCaracteres){
                if(textoCompleto[i] == matrizCripografada[0][linha][coluna]){
                    i++;
                }
                else{
                    free(textoCrip);
                    fclose(arqCriptografado);
                    return 0;
                }
            }
        }
    }

    printf("Transposicao. %d\n", chave);
    aux = 1;
    fclose(arqCriptografado);
    free(textoCrip);
    return 1;
}


int Vigener(char arquivoCriptografado[100], char arquivoDescriptografado[100]){
    char charCriptografado[1], charDescriptografado[1];
    int chaveAtu = 0;

    FILE *arqCriptografado;
    FILE *arqDescriptografado;
    FILE *arqResposta;

    arqCriptografado = fopen(arquivoCriptografado, "rb");
    arqDescriptografado = fopen(arquivoDescriptografado, "rb");

    arqResposta = fopen("Chave de Vigenere.dat","wb+");
    if(arqCriptografado != NULL && arqDescriptografado != NULL){
        while(!feof(arqCriptografado) && !feof(arqDescriptografado)){
            charCriptografado[0] = '\0';
            charDescriptografado[0] = '\0';
            fread(charCriptografado,sizeof(charCriptografado),1,arqCriptografado);
            fread(charDescriptografado,sizeof(charDescriptografado),1,arqDescriptografado);

            chaveAtu = (charCriptografado[0] - charDescriptografado[0] + 256) % 256;

            fwrite(&chaveAtu, 1, 1, arqResposta);
        }
    }else{
        printf("Nao foi possivel abrir o arquivo");
        return 0;
    }
    printf("Gerado o arquivo de chave do Vigenere!");
    fclose(arqCriptografado);
    fclose(arqDescriptografado);
    return 0;
}
