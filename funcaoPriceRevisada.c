#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <locale.h>
#include <unistd.h>
#define MAX 80
#define ARQ "price.txt"
//ORIGINAL

typedef struct
{
    char nome[100];
} dataPrice;

int linha(int qtdLinha)
{
    int i;
    for(i=0; i<qtdLinha; i++)
    {
        printf("=");
    }
    printf("\n\n");
}

float calculoPrice(float valorFinanciado,float taxaJuros, int numParcelas)
{
    return valorFinanciado / (((pow(1.0+(taxaJuros/100),numParcelas)) - 1.0) / ((pow(1.0+(taxaJuros/100),numParcelas)) * (taxaJuros/100)));
}

int main()
{
    float vlImovel, vlEntrada, valorFinanciado, taxaJuros, vlParcelasPorMes, amort, vlPorcInicial;
    float totalJuros=0, totalAmort=0;
    int numParcelas;
    char iniciar;
    char tabDet;
    char salvarFinPrice;
    dataPrice a;

    FILE *arquin; //ponteiro para arquivo de entrada
    arquin = fopen(ARQ,"a");  //arquivo de entrada usando "w" que gravará temporariamente no arquivo

    setlocale(LC_ALL,"");

    do
    {
        sleep(1);
        system("cls");
        linha(MAX);
        printf("Deseja fazer uma nova simulacao de financiamento no modelo Price?\n\n[s]SIM\n[n]NAO\n\n");
        scanf("%c",&iniciar);
        getchar();
        if (iniciar != 's' && iniciar != 'S' && iniciar != 'n' && iniciar != 'N')
        {
            printf("Opcao incorreta! Digite 's' para SIM e 'n' para NAO\n\n");
            sleep(1);
            system("cls");
        }
        else
        {
            if(iniciar=='s' || iniciar=='S')
            {
                linha(MAX);
                printf("Digite o valor do imóvel: ");
                scanf("%f",&vlImovel);

                printf("Digite o valor de entrada: ");
                scanf("%f",&vlEntrada);
                printf("\n");

                valorFinanciado = vlImovel - vlEntrada;
                printf("Valor a ser financiado: R$ %.2f\n", valorFinanciado);

                printf("Digite a taxa de juros(%%): ");
                scanf("%f",&taxaJuros);

                printf("Digite o numero de parcelas: ");
                scanf("%i",&numParcelas);

                printf("\n");


                vlParcelasPorMes = calculoPrice(valorFinanciado, taxaJuros, numParcelas);

                linha(MAX);
                printf("Valor do financiamento:R$ %.2f reais.\n",valorFinanciado);
                printf("Valor fixo das parcelas: R$ %.2f reais.\n",vlParcelasPorMes);
                printf("Numeros de parcelas: %i vezes\n", numParcelas);
                printf("Taxa de juros(%%): %.2f%% a.m.\n\n",taxaJuros);

                //Salvando informacoes no arquivo price.txt
                fprintf(arquin,"R$%.2f ",valorFinanciado);
                fprintf(arquin,"%.2f ",vlParcelasPorMes);
                fprintf(arquin,"%i ",numParcelas);
                fprintf(arquin,"%.0f ",taxaJuros);

                //começará daqui a opção de ver tabela detalhada
                //ainda será incluído um "do"

                printf("Valor fixo das parcelas: R$ %.2f reais.\n",vlParcelasPorMes);

                vlPorcInicial = valorFinanciado * (taxaJuros/100);

                amort = vlParcelasPorMes - vlPorcInicial;

                printf("Valor do juros no primeiro mes: R$ %.2f reais.\n",vlPorcInicial);
                printf("Valor da amortizacao no primeiro mes: R$ %.2f reais.\n\n",amort);
                getchar();

                do
                {
                    printf("Deseja ver tabela detalhada?\n");
                    scanf("%c",&tabDet);
                    getchar();
                    if(tabDet != 's' && tabDet != 'S' && tabDet != 'n' && tabDet != 'N')
                    {
                        printf("Opcao incorreta! Digite 's' para SIM e 'n' para NAO\n\n");
                        sleep(1);
                        system("cls");
                    }
                    else
                    {
                        if(tabDet=='s' || tabDet=='S')
                        {
                            sleep(1);
                            system("cls");

                            printf("Valor do financiamento:R$ %.2f reais.\n",valorFinanciado);
                            printf("Valor fixo das parcelas: R$ %.2f reais.\n",vlParcelasPorMes);
                            printf("Numeros de parcelas: %i vezes\n", numParcelas);
                            printf("Taxa de juros(%%): %.2f%% a.m.\n\n",taxaJuros);
                            linha(MAX);

                            printf("Valor fixo das parcelas: R$ %.2f reais.\n",vlParcelasPorMes);

                            vlPorcInicial = valorFinanciado * (taxaJuros/100);

                            amort = vlParcelasPorMes - vlPorcInicial;

                            printf("Valor do juros no primeiro mes: R$ %.2f reais.\n",vlPorcInicial);
                            printf("Valor da amortizacao no primeiro mes: R$ %.2f reais.\n\n",amort);

                            for(int i=2; i<=numParcelas; i++)
                            {
                                valorFinanciado-=amort;
                                vlPorcInicial = valorFinanciado * (taxaJuros/100);
                                amort = vlParcelasPorMes - vlPorcInicial;
                                totalJuros+=vlPorcInicial;
                                totalAmort+=amort;

                                printf("%i%c mes - Parcela fixa de R$ %.2f reais\n", i, 248, vlParcelasPorMes);

                                if(valorFinanciado<0 && vlPorcInicial<0)
                                {
                                    printf("Valor atualizado da amortização: R$ %.2f reais\n",amort);
                                    printf("Valor atualizado do juros: SEM JUROS.\n");
                                    printf("Valor atualizado do saldo devedor: R$ %.2f reais\n\n",valorFinanciado);

                                }
                                else
                                {
                                    printf("Valor atualizado da amortizacao: R$ %.2f reais\n",amort);
                                    printf("Valor atualizado do juros: R$ %.2f reais\n",vlPorcInicial);
                                    printf("Saldo devedor: R$ %.2f reais\n\n",valorFinanciado);

                                }
                            }
                            do
                            {
                                printf("Deseja salvar simulação de financiamento Price?\n");
                                scanf("%c",&salvarFinPrice);
                                getchar();
                                if(salvarFinPrice != 's' && salvarFinPrice != 'S' && salvarFinPrice != 'n' && salvarFinPrice != 'N')
                                {
                                    printf("Opcao incorreta! Digite 's' para SIM e 'n' para NAO\n\n");
                                    sleep(1);
                                    system("cls");
                                }
                                else
                                {
                                    if(salvarFinPrice=='s' || salvarFinPrice=='S')
                                    {
                                        //buscar cadastro do cliente
                                        sleep(1);
                                        system("cls");
                                        printf("Digite nome de usuário cadastrado: ");
                                        scanf("%s",a.nome);


                                        //apagar daqui pra cima se der errado
                                    }
                                }

                            }while(salvarFinPrice != 'n' && salvarFinPrice != 'N');
                            break;

                        }
                    }

                }
                while(tabDet != 'n' && tabDet != 'N');
                printf("Pressione ENTER para retornar.");
                getchar();

            }
        }

        //terminará aqui a tabela detalhada
        //Será colocado um while para resposta 's' ou qualquer outra letra que retornará um erro e será repetida a pergunta


    }
    while(iniciar!='n' && iniciar!='N');

    fclose(arquin);

    linha(MAX);
    printf("RETORNA PARA A PAGINA PRINCIPAL\n");

    getchar();
    return 0;
}
