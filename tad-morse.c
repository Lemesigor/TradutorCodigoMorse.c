#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<windows.h>
#include "tad-morse.h"

void preFixado(pNodoA *a)
{
    if (a!= NULL)
    {
        printf(" %c %s\n",a->info,a->codigo);
        preFixado(a->esq);
        preFixado(a->dir);
    }
}

pNodoA* cria_arvore(void){
    return NULL;
}

pNodoA* consultaABP2(pNodoA *a, char chave, int *contador)
{
    if(a == NULL){
        *contador = *contador + 1;
        return NULL;}

    pNodoA* atual = a;
    while (atual != NULL) {
        if (chave == atual->info) {
            *contador = *contador + 1;
            return atual;
        }
        if (chave > atual->info) {
            *contador = *contador + 1;
            atual = atual->dir;
        } else {
            atual = atual->esq;
        }
    }
    return NULL;


}

pNodoA* InsereArvore(pNodoA *a, char ch, char codigo[])
{
    if (a == NULL)
    {
        a = (pNodoA*) malloc(sizeof(pNodoA));
        a->info = ch;
        strcpy(a->codigo,codigo);
        a->esq = NULL;
        a->dir = NULL;
    }
    else
        if (ch < (a->info))
            a->esq = InsereArvore(a->esq,ch,codigo);
        else
            a->dir = InsereArvore(a->dir,ch,codigo);
    return a;
}
int testa_abertura(char nome_entrada[], char nome_tabela[],char nome_saida[])
{
    FILE *arq1, *arq2, *arq3;

    if ((arq1 = fopen(nome_entrada, "r"))== NULL )
    {
        printf("Erro ao abrir arquivo entrada");
        getchar();
        fclose(arq1);
        return 0;
    }



    if ((arq2 = fopen(nome_tabela, "r")) == NULL )
    {
        printf("Erro ao abrir arquivo tabela");
        getchar();
        fclose(arq2);
        return 0;
    }



    if ((arq3 = fopen(nome_saida, "w"))== NULL )
    {
        printf("Erro ao abrir arquivo saida");
        getchar();
        fclose(arq3);
        return 0;
    }



    fclose(arq1);
    fclose(arq2);
    fclose(arq3);
    return 1;  //se chegou aqui, abriu corretamente todos os arquivos
}
char arruma_caracter(char caracter_atual)
{
    switch(caracter_atual){
    case 'ã':return 'A';
            break;

    case 'á':return 'A';
            break;

    case 'à':return 'A';
            break;

    case 'â':return 'A';
            break;

    case 'é':return 'E';
            break;

    case 'ê':return 'E';
            break;

    case 'í':return 'I';
            break;

    case 'ó':return 'O';
            break;

    case 'ô':return 'O';
            break;

    case 'ú':return 'U';
            break;

    case 'ç':return 'C';
            break;
    }
    //Se não é nenhum caracter especial, retorna ele em caixa alta
    return  toupper(caracter_atual);

}

void carrega_tabela_abp(char nome_arquivo[], pNodoA **abp)
{

    FILE *arq1;
    BUFFER_ABP_MORSE buffer_caracter; //Tipo que armazena o caracter e seu código

    arq1 = fopen(nome_arquivo, "r");
    *abp = cria_arvore(); //Se abriu arquivo, cria arvore

    while (!feof(arq1))
    {
        fscanf(arq1, " %c%s", &buffer_caracter.caracterzinho, buffer_caracter.codigozinho);
        *abp = InsereArvore(*abp, buffer_caracter.caracterzinho, buffer_caracter.codigozinho);
    }
    fclose(arq1);
}

void converte_texto_abp(char nome_entrada[],char nome_saida[], pNodoA *abp,int *contador)
{
    FILE *arq, *arq1;
    pNodoA *abp_codigo_atual;
    char buffer_linha[TAM_LINHA];
    int  i = 0;


    arq = fopen(nome_entrada, "r");
    arq1 = fopen(nome_saida,"w");

    while (!feof(arq))
    {
        if (fgets(buffer_linha, sizeof(buffer_linha), arq) != NULL )
        {
            i = 0;      //Zera o contador do array que armazena a linha
            while((buffer_linha[i] != '\n') && (buffer_linha[i] != '\0'))   //Laço percorre a string_buffer
            {
                if (buffer_linha[i] == ' ') //Se for espaço, coloca barra e incrementa o contador
                {
                    fprintf(arq1, "/");
                    i++;
                }
                else if (buffer_linha[i] != ' ')
                {
                    buffer_linha[i] = arruma_caracter(buffer_linha[i]);
                    abp_codigo_atual = consultaABP2(abp, buffer_linha[i],contador);
                    if (abp_codigo_atual != NULL) //Se retoronou um caracter, coloca ele no arquivo
                        fprintf(arq1, "%s  ",abp_codigo_atual->codigo);
                    i++;
                }

            }
        }

    }
    fclose(arq1);
    fclose(arq);
}

pNodoB* criar_arvore_avl()
{
    return NULL;
}

pNodoB* rotacao_direita(pNodoB *a)
{
    pNodoB *p;

    p = a->esq;
    a->esq = p->dir;
    p->dir = a;
    a->FB = 0;
    a = p;
    return a;
}

pNodoB* rotacao_esquerda(pNodoB *a)
{
    pNodoB *p;

    p = a->dir;
    a->dir = p->esq;
    p->esq = a;
    a->FB = 0;
    a = p;
    return a;
}

pNodoB* rotacao_dupla_direita(pNodoB *a)
{
    pNodoB *u, *v;

    u = a->esq;
    v = u->dir;
    u->dir = v->esq;
    v->esq = u;
    a->esq = v->dir;
    v->dir = a;

    if (v->FB == 1) a->FB = -1;
    else a->FB = 0;
    if (v->FB == -1) u->FB = 1;
    else u->FB = 0;
    a = v;
    return a;
}

pNodoB* rotacao_dupla_esquerda(pNodoB *a)
{
    pNodoB *z, *y;
    z = a->dir;
    y = z->esq;
    z->esq = y->dir;
    y->dir = z;
    a->dir = y->esq;
    y->esq = a;
    if (y->FB == -1) a->FB = 1;
    else a->FB = 0;
    if (y->FB == 1) z->FB = -1;
    else z->FB = 0;
    a = y;
    return a;
}

pNodoB* caso_um (pNodoB *a, int *ok)
{
    pNodoB *z;
    z = a->esq;
    if (z->FB == 1) {
        a = rotacao_direita(a);
    } else {
        a = rotacao_dupla_direita(a);
    }
    a->FB = 0;
    ok = 0;
    return a;
}

pNodoB* caso_dois(pNodoB *a, int *ok)
{
    pNodoB *z;
    z = a->dir;
    if (z->FB == -1) {
        a = rotacao_esquerda(a);
    } else {
        a = rotacao_dupla_esquerda(a);
    }
    a->FB = 0;
    ok = 0;
    return a;
}

pNodoB* inserir_arvore_avl(pNodoB *a, char ch, char codigo[], int *ok)
{
    if (a == NULL) {
        a = (pNodoB*) malloc(sizeof(pNodoB));
        a->info = ch;
        strcpy(a->codigo, codigo);
        a->esq = NULL;
        a->dir = NULL;
        a->FB = 0;
        *ok = 1;
    } else if (ch < a->info) {
        a->esq = inserir_arvore_avl(a->esq, ch, codigo, ok);
        if(ok) {
            switch (a->FB) {
            case -1:
                a->FB = 0;
                ok = 0;
                break;
            case 0:
                a->FB = 1;
                break;
            case 1:
                a = caso_um(a, ok);
                break;
            }
        }
    } else {
        a->dir = inserir_arvore_avl(a->dir, ch, codigo, ok);
        if (ok) {
            switch (a->FB) {
            case 1:
                a->FB = 0;
                ok = 0;
                break;
            case 0:
                a->FB = -1;
                break;
            case -1:
                a = caso_dois(a, ok);
                break;
            }
        }
    }
    return a;
}

pNodoB* consultar_arvore_avl(pNodoB *a, char chave, int *contador)
{
    if(a == NULL){
        *contador = *contador + 1;
        return NULL;}

    pNodoB* atual = a;
    while (atual != NULL) {
        if (chave == atual->info) {
            *contador = *contador + 1;
            return atual;
        }
        if (chave > atual->info) {
            *contador = *contador + 1;
            atual = atual->dir;
        } else {
            atual = atual->esq;
        }
    }
    return NULL;
}

void carregar_tabela_avl(char nome_arquivo[], pNodoB **avl)
{
    FILE *arq1;
    int *ok;
    BUFFER_ABP_MORSE buffer_caracter; //Tipo que armazena o caracter e seu código

    arq1 = fopen(nome_arquivo, "r");
    *avl = criar_arvore_avl(); //Se abriu arquivo, cria arvore

    while (!feof(arq1))
    {
        fscanf(arq1, " %c%s", &buffer_caracter.caracterzinho, buffer_caracter.codigozinho);
        *avl = inserir_arvore_avl(*avl, buffer_caracter.caracterzinho, buffer_caracter.codigozinho, ok);
    }
    fclose(arq1);
}

void converte_texto_avl(char nome_entrada[], char nome_saida[], pNodoB *avl, int *contador)
{
    FILE *arq, *arq1;
    pNodoB*avl_codigo_atual;
    char buffer_linha[TAM_LINHA];
    int  i = 0;

    arq = fopen(nome_entrada, "r");
    arq1 = fopen(nome_saida,"w");

    while (!feof(arq))
    {
        if (fgets(buffer_linha, sizeof(buffer_linha), arq) != NULL )
        {
            i = 0;      //Zera o contador do array que armazena a linha
            while((buffer_linha[i] != '\n') && (buffer_linha[i] != '\0'))   //Laço percorre a string_buffer
            {
                if (buffer_linha[i] == ' ') //Se for espaço, coloca barra e incrementa o contador
                {
                    fprintf(arq1, "/");
                    i++;
                }
                else if (buffer_linha[i] != ' ')
                {
                    buffer_linha[i] = arruma_caracter(buffer_linha[i]);
                    avl_codigo_atual = consultar_arvore_avl(avl, buffer_linha[i],contador);
                    if (avl_codigo_atual != NULL) //Se retoronou um caracter, coloca ele no arquivo
                        fprintf(arq1, "%s  ",avl_codigo_atual->codigo);
                    i++;
                }

            }
        }

    }
    fclose(arq1);
    fclose(arq);
}
