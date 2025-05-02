#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "avl.h"

#define ESPACO 4 // Define o espaçamento entre os nós

// Definição da estrutura AVL
struct avl
{
    int chave;
    struct avl *esquerda, *direita;
    int altura;
};

// Função para obter a altura de um nó
int obterAltura(AVL *no)
{
    return no ? no->altura : 0;
}

// Função para calcular o fator de balanceamento
int obterFactorBalanceamento(AVL *node)
{
    return node ? obterAltura(node->esquerda) - obterAltura(node->direita) : 0;
}

// Função para atualizar a altura de um nó
void atualizarAltura(AVL *no)
{
    if (no)
    {
        int alturaEsquerda = obterAltura(no->esquerda);
        int alturaDireita = obterAltura(no->direita);
        no->altura = (alturaEsquerda > alturaDireita ? alturaEsquerda : alturaDireita) + 1;
    }
}

// Rotação à direita
AVL *RotacionarDireita(AVL *raiz)
{
    AVL *novaRaiz = raiz->esquerda;
    raiz->esquerda = novaRaiz->direita;
    novaRaiz->direita = raiz;
    atualizarAltura(raiz);
    atualizarAltura(novaRaiz);
    return novaRaiz;
}

// Rotação à esquerda
AVL *RotacionarEsquerda(AVL *raiz)
{
    AVL *novaRaiz = raiz->direita;
    raiz->direita = novaRaiz->esquerda;
    novaRaiz->esquerda = raiz;
    atualizarAltura(raiz);
    atualizarAltura(novaRaiz);
    return novaRaiz;
}

// Função para balancear um nó
AVL *balancearNo(AVL *node)
{
    atualizarAltura(node);
    int factorBalanceamento = obterFactorBalanceamento(node);

    // Rotação à direita
    if (factorBalanceamento > 1 && obterFactorBalanceamento(node->esquerda) >= 0)
    {
        return RotacionarDireita(node);
    }

    // Rotação à esquerda
    if (factorBalanceamento < -1 && obterFactorBalanceamento(node->direita) <= 0)
    {
        return RotacionarEsquerda(node);
    }

    // Rotação dupla à direita
    if (factorBalanceamento > 1 && obterFactorBalanceamento(node->esquerda) < 0)
    {
        node->esquerda = RotacionarEsquerda(node->esquerda);
        return RotacionarDireita(node);
    }

    // Rotação dupla à esquerda
    if (factorBalanceamento < -1 && obterFactorBalanceamento(node->direita) > 0)
    {
        node->direita = RotacionarDireita(node->direita);
        return RotacionarEsquerda(node);
    }

    return node;
}

// Função para criar um novo nó
AVL *criarNo(int chave)
{
    AVL *no = malloc(sizeof(AVL));
    if (!no)
    {
        fprintf(stderr, "Erro ao alocar memória para novo nó.\n");
        exit(1);
    }
    no->chave = chave;
    no->esquerda = no->direita = NULL;
    no->altura = 1;
    return no;
}

// Função para inserir um nó na AVL
void inserirNo(AVL **raiz, int chave)
{
    if (!(*raiz))
    {
        *raiz = criarNo(chave);
        return;
    }

    if (chave < (*raiz)->chave)
    {
        inserirNo(&((*raiz)->esquerda), chave);
    }
    else if (chave > (*raiz)->chave)
    {
        inserirNo(&((*raiz)->direita), chave);
    }
    else
    {
        return; // Chave duplicada não é permitida
    }

    *raiz = balancearNo(*raiz);
}

// Função para encontrar o menor nó
AVL *encontrarMenorNo(AVL *no)
{
    while (no->esquerda)
    {
        no = no->esquerda;
    }
    return no;
}

// Função para remover um nó da AVL
void removerNo(AVL **raiz, int chave)
{
    if (!(*raiz))
    {
        return;
    }

    if (chave < (*raiz)->chave)
    {
        removerNo(&((*raiz)->esquerda), chave);
    }
    else if (chave > (*raiz)->chave)
    {
        removerNo(&((*raiz)->direita), chave);
    }
    else
    {
        if (!(*raiz)->esquerda || !(*raiz)->direita)
        {
            AVL *temp = (*raiz)->esquerda ? (*raiz)->esquerda : (*raiz)->direita;
            free(*raiz);
            *raiz = temp;
        }
        else
        {
            AVL *temp = encontrarMenorNo((*raiz)->direita);
            (*raiz)->chave = temp->chave;
            removerNo(&((*raiz)->direita), temp->chave);
        }
    }

    if (*raiz)
    {
        *raiz = balancearNo(*raiz);
    }
}

// Função para pesquisar um nó
AVL *pesquisarNo(AVL *raiz, int chave)
{
    if (!raiz || raiz->chave == chave)
    {
        return raiz;
    }

    if (chave < raiz->chave)
    {
        return pesquisarNo(raiz->esquerda, chave);
    }
    else
    {
        return pesquisarNo(raiz->direita, chave);
    }
}

int somarSubarvore(AVL *raiz)
{
    if (!raiz)
    {
        return 0;
    }
    return raiz->chave + somarSubarvore(raiz->esquerda) + somarSubarvore(raiz->direita);
}

// Função para somar os nós da subárvore esquerda
int somarSubarvoreEsquerda(AVL *raiz)
{
    if (!raiz || !raiz->esquerda)
    {
        return 0;
    }
    return somarSubarvore(raiz->esquerda);
}

// Função para encontrar o N-ésimo maior elemento
int encontrarMaiorHelper(AVL *raiz, int *n, int *resultado)
{
    if (!raiz)
        return 0;

    // Busca primeiro na direita (elementos maiores)
    if (encontrarMaiorHelper(raiz->direita, n, resultado))
        return 1;

    (*n)--; // Decrementa a posição
    if (*n == 0)
    {
        *resultado = raiz->chave;
        return 1; // Encontrado
    }

    return encontrarMaiorHelper(raiz->esquerda, n, resultado);
}

int encontrarMaior(AVL *raiz, int n, int *encontrado)
{
    int resultado = -1;
    *encontrado = encontrarMaiorHelper(raiz, &n, &resultado);
    return resultado;
}

// Função auxiliar para desenhar a árvore horizontalmente
void desenhaArvoreHoriz(AVL *arvore, int profundidade, char *caminho, int direita) {
    if (arvore == NULL) {
        return;
    }

    // Incrementa a profundidade
    profundidade++;

    // Desenha a subárvore direita primeiro
    desenhaArvoreHoriz(arvore->direita, profundidade, caminho, 1);

    // Configura o mapa de ramificações
    caminho[profundidade - 2] = 0;
    if (direita) {
        caminho[profundidade - 2] = 1;
    }
    if (arvore->esquerda) {
        caminho[profundidade - 1] = 1;
    }

    // Imprime o nó atual com os traços e ramificações
    printf("\n");
    for (int i = 0; i < profundidade - 1; i++) {
        if (i == profundidade - 2) {
            printf("+");
        } else if (caminho[i]) {
            printf("|");
        } else {
            printf(" ");
        }

        for (int j = 1; j < ESPACO; j++) {
            if (i < profundidade - 2) {
                printf(" ");
            } else {
                printf("-");
            }
        }
    }
    printf("%d\n", arvore->chave);

    // Imprime os espaços verticais abaixo
    for (int i = 0; i < profundidade; i++) {
        if (caminho[i]) {
            printf("|");
        } else {
            printf(" ");
        }

        for (int j = 1; j < ESPACO; j++) {
            printf(" ");
        }
    }

    // Desenha a subárvore esquerda
    desenhaArvoreHoriz(arvore->esquerda, profundidade, caminho, 0);
}

// Função principal para desenhar a árvore horizontalmente
void imprimirArvore(AVL *arvore) {
    char caminho[255] = {}; // Caminho para rastrear as ramificações
    desenhaArvoreHoriz(arvore, 0, caminho, 0);
}

void liberarArvore(AVL *raiz) {
    if (!raiz) return;
    liberarArvore(raiz->esquerda);
    liberarArvore(raiz->direita);
    free(raiz);
    raiz = NULL;
}