#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<windows.h>
#define TAM_NOME_ARQ 50
#define TAM_CODIGO  8   //Tamanho máximo do caracter em codigo morse
#define TAM_LINHA   5000 //Tamanho máximo de uma linha de um arqivo

//Struct que armazena temporariamente o caracter e o código para passar para a abp
typedef struct{
    char caracterzinho;
    char codigozinho[TAM_CODIGO];
}BUFFER_ABP_MORSE;


//Struct da ABP
struct TNodoA
{
    char info;
    char codigo[TAM_CODIGO];
    struct TNodoA *esq;
    struct TNodoA *dir;
};
typedef struct TNodoA pNodoA;

// Estrutura para AVL.
struct TNodoB
{
    char info;
    int FB;
    char codigo[TAM_CODIGO];
    struct TNodoB *esq;
    struct TNodoB *dir;
};

typedef struct TNodoB pNodoB;


///FUNÇOES COM ABP
//Cria uma ABP
pNodoA* cria_arvore(void);

// Recebe endereço da raiz e chave procuradaSe encontrar, devolve nodo encontrado,caso contrário devolve nulo
pNodoA* consultaABP2(pNodoA *a, char chave, int *contador);

//Insere um nodo em uma ABP
pNodoA* InsereArvore(pNodoA *a, char ch, char codigo_inserir[]);

//Imprime uma árvore pelo pré-fixado-esquerda
void preFixado(pNodoA *a);

///FUNÇOES PARA ABERTURA DE ARQUIVO
//Abre o arquivo da tabela e passa a chave o código morse para uma abp
void carrega_tabela_abp(char nome_tabela[], pNodoA **abp);
//Converte um arquivo de texto para sua forma em árvore binária
void converte_texto_abp (char nome_entrada[],char nome_saida[], pNodoA *abp, int *contador);
//Testa se o caracter tem algum acento
char arruma_caracter (char caracter_atual);
//Testa a abertura dos arquivos
int testa_abertura(char nome_entrada[], char nome_tabela[],char nome_saida[]);
// Abre o arquivo da tabela e passa a chave do código Morse para uma AVL.
void carregar_tabela_avl(char nome_arquivo[], pNodoB **avl);
// Converte um arquivo de texto para sua forma em árvore binária.
void converte_texto_avl(char nome_entrada[], char nome_saida[], pNodoB *avl, int *contador_avl);



///FUNÇÕES COM AVL
//Cria uma árvore AVL.
pNodoB* criar_arvore_avl(void);
//Inserir um nodo em uma árvore AVL.
pNodoB* inserir_arvore_avl(pNodoB *a, char ch, char codigo[], int *ok);
// Consultar valor na AVL.
pNodoB* consultar_arvore_avl(pNodoB *a, char chave, int *contador_avl);
// Fazer rotação para à direita.
pNodoB* rotacao_direita(pNodoB *a);
// Fazer rotação para à esquerda.
pNodoB* rotacao_esquerda(pNodoB *a);
// Fazer rotação dupla para à direita.
pNodoB* rotacao_dupla_direita(pNodoB *a);
// Fazer rotação dupla para à esquerda.
pNodoB* rotacao_dupla_esquerda(pNodoB *a);
// Verifica rotação a ser feita, se para à direita ou dupla à direita.
pNodoB* caso_um(pNodoB *a, int *ok);
// Verifica rotação a ser feita, se para à esquerda ou dupla à esquerda.
pNodoB* caso_dois(pNodoB *a, int *ok);



