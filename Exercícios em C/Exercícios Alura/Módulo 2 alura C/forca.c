#include <stdio.h>
#include <string.h>
#include "forca.h"
#include <time.h>
#include <stdlib.h>


char palavrasecreta[20];
char chutes[26];
int chutesdados = 0;


void escolhepalavra() {

    FILE* f;
    f = fopen("../palavras.txt", "r");
    if (f == NULL) {
    printf("Erro ao abrir o arquivo palavras.txt\n");
    exit(1);
}
    

    int qtdpal; 
    fscanf(f,"%d",&qtdpal);
    printf("Número de palavras: %d\n", qtdpal);

    srand(time(0));
    int randomico= rand() % qtdpal;

    for (int i = 0; i <= randomico; i++)
    {
        fscanf(f,"%s",palavrasecreta);
    }


    fclose(f);
    printf("A palavra secreta é: %s\n", palavrasecreta);
}


int jachutou(char letra) {
    int achou = 0;
    for(int j = 0; j < chutesdados; j++) {
        if(chutes[j] == letra) {
            achou = 1;
            break;
        }
    }

    return achou;
}

void abertura() {
    printf("/****************/\n");
    printf("/ Jogo de Forca */\n");
    printf("/****************/\n\n");
}

void chuta() {
    char chute;
    printf("Qual letra? ");
    scanf(" %c", &chute);

    chutes[chutesdados] = chute;
    chutesdados++;
}

void desenhaforca() {

    printf("Você já deu %d chutes\n", chutesdados);

    for(size_t i = 0; i < strlen(palavrasecreta); i++) {

        if(jachutou(palavrasecreta[i])) {
            printf("%c ", palavrasecreta[i]);
        } else {
            printf("_ ");
        }

    }
    printf("\n");

}

int contadordefalhas(){

    int erros=0;

    for (int i = 0; i < chutesdados; i++)
    {
        int existe=0;
        for (size_t j = 0; j < strlen(palavrasecreta); j++)
        {
            if (chutes[i]== palavrasecreta[j])
            {
                existe=1;
                break;
            }
                
        }

        if (!existe)
        {
            erros++;
        }
        
    }

    return erros>=5;
    
}

int ganhou(){
    for (size_t i = 0; i < strlen(palavrasecreta); i++)
    {
        if (!jachutou(palavrasecreta[i]))
        {
           return 0;
        }
    }
    
    return 1;
}

void finalizacao (){
    printf("\n Jogo FInalizado com Sucesso! ");
    
}

int main() {

    abertura();
    escolhepalavra();

    do {

        desenhaforca();
        chuta();

        

    } while (!ganhou() && !contadordefalhas());

    finalizacao();

}