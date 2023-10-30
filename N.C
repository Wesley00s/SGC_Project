#include "sgc.h"

void fazerPedido(struct Produto produto[MAX], struct Usuario usuario[MAX], int cont, int contUsr)
{
    char nomeProduto[MAX];
    char nomeUsr[MAX];
    int qnt, j = 0, i = 0;
    int opcaoContinue;
    int contPedidos = 0;
    float total = 0;
    int confirm;

    printf("\n\t\tREALIZAR COMPRA\n");
    int usuarioEncontrado = -1; // Marcador para indicar se o usuário foi encontrado

    limparBuffer();
    printf("\nInforme o nome do usuário: ");
    scanf("%99[^\n]", nomeUsr);
    do
    {
        for (i = 0; i < contUsr; i++)
        {
            if (strcmp(nomeUsr, usuario[i].nome) == 0)
            {
                usuarioEncontrado = i; // Marca o índice do usuário encontrado
                break;                 // Sai do loop assim que encontra o usuário
            }
        }
        int produtoEncontrado = -1;
        if (usuarioEncontrado != -1)
        {
            limparBuffer();
            printf("\nInforme o nome do produto: ");
            scanf("%99[^\n]", nomeProduto);

            for (j = 0; j < cont; j++)
            {
                if (strcmp(nomeProduto, produto[j].nome) == 0)
                {
                    produtoEncontrado = j; // Marca o índice do produto encontrado
                    break;                 // Sai do loop assim que encontra o produto
                }
            }

            if (produtoEncontrado != -1)
            {
                limparBuffer();
                printf("\nInforme a quantidade de %s que deseja comprar (Estoque %d): ", produto[j].nome, produto[j].estoque);
                scanf("%d", &qnt);

                if (qnt <= produto[produtoEncontrado].estoque)
                {
                    printf("\nAdicionado ao Carrinho de compras.\n");

                    strcpy(produto[contPedidos].nomePedido, nomeProduto);
                    produto[contPedidos].qntPedido = qnt;
                    produto[contPedidos].valor = produto[produtoEncontrado].valor;

                    contPedidos++;

                    printf("\nContinuar para compra ou ir para carrinho?\n1 - Continuar\n0 - Carrinho\n");
                    scanf("%d", &opcaoContinue);
                }
                else
                {
                    printf("\nEstoque insuficiente!\n");
                    break;
                }
            }
            else
            {
                printf("\nProduto não encontrado!\n");
                break;
            }
        }
        else
        {
            printf("\nNome de usuário não encontrado!\n");
            break;
        }

        if (opcaoContinue == 0)
        {
            printf("\n\t\tCARRINHO\n");

            printf("\n\t\t==================== Comprovante ================\n\n");
            printf("\t\t-------------------------------------------------\n\n");
            printf("\t\tCLIENTE: %s\n\n", usuario[usuarioEncontrado].nome);
            printf("\t\tID_CLIENTE: %d\n\n", usuario[usuarioEncontrado].ID);
            printf("\t\tPRODUTOs:\n\n");

            for (int k = 0; k < contPedidos; k++)
            {
                printf("\t\t%s\t\tx%d", produto[k].nomePedido, produto[k].qntPedido);
                printf("\n\t\tPREÇO UNITÁRIO: R$%.2f", produto[k].valor);
                printf("\n\t\tSUBTOTAL DE PRODUTO: R$%.2f\n\n", produto[k].valor * produto[k].qntPedido);

                total += produto[k].qntPedido * produto[k].valor;
            }

            printf("\n\n\t\tTOTAL DA COMPRA: R$%.2f\n\n", total);
            printf("\t\t-----------------------------------------------------\n");
            printf("\t\t\tOBRIGADO POR ESCOLHER Plaza Mercantil SA\n");
            printf("\t\t=====================================================\n\n");

            printf("\nConfirmar compra?\n1 - Sim\n2 - Não\n");
            scanf("%d", &confirm);

            if (confirm == 1)
            {
                for (int l = 0; l < contPedidos; l++)
                {
                    // Atualiza o estoque do produto original
                    for (int m = 0; m < cont; m++)
                    {
                        if (strcmp(produto[l].nomePedido, produto[m].nome) == 0)
                        {
                            produto[m].estoque -= produto[l].qntPedido;
                            break;
                        }
                    }
                }
                printf("\nCompras realizadas com sucesso!\n");
            }
            else
            {
                printf("\nCompra cancelada!\n");
            }
        }
    } while (opcaoContinue != 0);
}
