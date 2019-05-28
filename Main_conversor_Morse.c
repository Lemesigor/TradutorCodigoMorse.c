#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<windows.h>
#include "tad-morse.h"

int main( int argc, char *argv[] )
{
    pNodoA *abp_tabela;
    pNodoB *avl_tabela;
    int contador_abp = 0, contador_avl = 0; //contador de comparaçòes
    char nome_entrada[TAM_NOME_ARQ],nome_tabela[TAM_NOME_ARQ],nome_saida[TAM_NOME_ARQ],nome_saida_avl[TAM_NOME_ARQ] = {"saida_avl.txt"};


    strcpy(nome_entrada,argv[1]);   //Passa os argumentos para um vetor teste
    strcpy(nome_tabela,argv[2]);
    strcpy(nome_saida,argv[3]);

    if (testa_abertura(nome_entrada,nome_tabela,nome_saida))    //Testa se os arquivos foram abertos corretamente
    {
        carrega_tabela_abp(nome_tabela, &abp_tabela);
        converte_texto_abp(nome_entrada,nome_saida,abp_tabela,&contador_abp);
        fflush(stdin);
        carregar_tabela_avl(nome_tabela, &avl_tabela);
        converte_texto_avl(nome_entrada, nome_saida_avl, avl_tabela,&contador_avl);
        printf("\n\t %d comparacoes na ABP \n\t %d comparacoes na AVL",contador_abp,contador_avl);
    }

    return 0;
}
