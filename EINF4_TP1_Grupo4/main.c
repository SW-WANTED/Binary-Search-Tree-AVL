#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

// Defini��es de cores ANSI
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define CYAN "\033[36m"
#define BOLD "\033[1m"

// Fun��o para pausar e limpar a tela
void pausarEContinuar()
{
    printf("\n%sPressione Enter para continuar...%s", CYAN, RESET);
    getchar();
    getchar();
    system("cls");
}

void exibirMenu(int opcaoSelecionada)
{
    printf("\n%s--- Menu AVL Tree ---\n%s", BOLD, RESET);
    printf("%s%s1. Inserir elemento%s\n", opcaoSelecionada == 1 ? GREEN : RESET, BOLD, RESET);
    printf("%s%s2. Remover elemento%s\n", opcaoSelecionada == 2 ? GREEN : RESET, BOLD, RESET);
    printf("%s%s3. Imprimir Arvore%s\n", opcaoSelecionada == 3 ? GREEN : RESET, BOLD, RESET);
    printf("%s%s4. Pesquisar No%s\n", opcaoSelecionada == 4 ? GREEN : RESET, BOLD, RESET);
    printf("%s%s5. Soma da Subarvore Esquerda%s\n", opcaoSelecionada == 5 ? GREEN : RESET, BOLD, RESET);
    printf("%s%s6. Encontrar N-esimo Maior%s\n", opcaoSelecionada == 6 ? GREEN : RESET, BOLD, RESET);
    printf("%s%s0. Sair%s\n", opcaoSelecionada == 0 ? GREEN : RESET, BOLD, RESET);
    printf("%sEscolha uma opcao: %s", CYAN, RESET);
}

int main()
{
    AVL *raiz = NULL;
    int escolha, chave, nivel, n, resultado;

    do
    {
        exibirMenu(-1);
        scanf("%d", &escolha);

        exibirMenu(escolha);

        switch (escolha)
        {
        case 1:
            printf("Digite a chave para inserir: ");
            scanf("%d", &chave);
            inserirNo(&raiz, chave);
            printf("%sElemento inserido com sucesso.%s\n", GREEN, RESET);
            pausarEContinuar();
            break;

        case 2:
            printf("Digite a chave para remover: ");
            scanf("%d", &chave);
            removerNo(&raiz, chave);
            printf("%sElemento removido com sucesso.%s\n", GREEN, RESET);
            pausarEContinuar();
            break;

        case 3: // Opção para imprimir a árvore AVL completa
            printf("Estrutura da Arvore AVL (Horizontalmente):\n");
            imprimirArvore(raiz);
            pausarEContinuar();
            break;

        case 4:
            printf("Digite a chave para pesquisar: ");
            scanf("%d", &chave);
            if (pesquisarNo(raiz, chave))
            {
                printf("%sElemento com chave %d encontrado.%s\n", GREEN, chave, RESET);
            }
            else
            {
                printf("%sElemento com chave %d nao encontrado.%s\n", RED, chave, RESET);
            }
            pausarEContinuar();
            break;

        case 5:
            resultado = somarSubarvoreEsquerda(raiz);
            printf("Soma da subarvore esquerda: %d\n", resultado);
            pausarEContinuar();
            break;

        case 6:
            printf("Digite o valor de n: ");
            scanf("%d", &n);
            int encontrado = 0;
            resultado = encontrarMaior(raiz, n, &encontrado);
            if (encontrado)
            {
                printf("%sO %d-esimo maior elemento e: %d%s\n", GREEN, n, resultado, RESET);
            }
            else
            {
                printf("%sNao ha elementos suficientes na arvore.%s\n", RED, RESET);
            }
            pausarEContinuar();
            break;

        case 0:
            printf("%sSaindo...%s\n", YELLOW, RESET);
            liberarArvore(raiz);
            break;

        default:
            printf("%sOpcao invalida! Tente novamente.%s\n", RED, RESET);
            pausarEContinuar();
        }
    } while (escolha != 0);

    return 0;
}
