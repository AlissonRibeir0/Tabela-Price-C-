#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <locale.h>
#define MAX 80

int main()
{
    int opcao;

    do
    {
        printf("Digite a opção desejada:\n");
        printf("[1]DETALHES  [2]SALVAR  [0]RETORNAR\n");
        scanf("%i",&opcao);
        switch(opcao)
        {
        case 1:
            printf("ESCOLHEU 1");
            break;
        case 2:
            printf("ESCOLHEU 2");
            break;
        default:
            break;
        }
    }while(opcao!=0);
    return 0;
}
