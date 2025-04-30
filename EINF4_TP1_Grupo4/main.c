#include <stdio.h>
#include "avl.h"

// Função principal para teste
int main()
{
    AVL *raiz = NULL;
    int escolha, chave, nivel, n, resultado;

    do
    {
        printf("\n--- Menu AVL Tree ---\n");
        printf("1. Inserir elemento\n");
        printf("2. Remover elemento\n");
        printf("3. Imprimir Nivel\n");
        printf("4. Pesquisar No\n");
        printf("5. Soma da Subarvore Esquerda\n");
        printf("6. Encontrar N-esimo Maior\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &escolha);

        switch (escolha)
        {
        case 1:
            printf("Digite a chave para inserir: ");
            scanf("%d", &chave);
            inserirNo(&raiz, chave);
            printf("Elemento inserido com sucesso.\n");
            break;

        case 2:
            printf("Digite a chave para remover: ");
            scanf("%d", &chave);
            removerNo(&raiz, chave);
            printf("Elemento removido com sucesso.\n");
            break;

        case 3:
            printf("Digite o nivel para imprimir: ");
            scanf("%d", &nivel);
            printf("Nos no nivel %d:\n", nivel);
            imprimirNivel(raiz, nivel);
            break;

        case 4:
            printf("Digite a chave para pesquisar: ");
            scanf("%d", &chave);
            if (pesquisarNo(raiz, chave))
            {
                printf("Elemento com chave %d encontrado.\n", chave);
            }
            else
            {
                printf("Elemento com chave %d nao encontrado.\n", chave);
            }
            break;

        case 5:
            resultado = somarSubarvoreEsquerda(raiz);
            printf("Soma da subarvore esquerda: %d\n", resultado);
            break;

        case 6:
            printf("Digite o valor de n: ");
            scanf("%d", &n);
            int encontrado = 0;
            resultado = encontrarMaior(raiz, n, &encontrado);
            if (encontrado)
            {
                printf("O %d-esimo maior elemento e: %d\n", n, resultado);
            }
            else
            {
                printf("Nao ha elementos suficientes na arvore.\n");
            }

            break;

        case 0:
            printf("Saindo...\n");
            break;

        default:
            printf("Opcao invalida! Tente novamente.\n");
        }
    } while (escolha != 0);

    return 0;
}