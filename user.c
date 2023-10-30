#include "sgc.h"

void adicionarAoCarrinho(struct ItemCarrinho carrinho[MAX], struct Produto produto[MAX], int *contCarrinho, int produtoIndex, int qnt)
{
    strcpy(carrinho[*contCarrinho].nome, produto[produtoIndex].nome);
    carrinho[*contCarrinho].valor = produto[produtoIndex].valor;
    carrinho[*contCarrinho].qntPedido = qnt;
    (*contCarrinho)++;
}

void exibirCarrinho(struct ItemCarrinho carrinho[MAX], int contCarrinho, struct Usuario usuario[MAX], int usrIndex)
{
    float total = 0;

    printf("\n\t\t==================== Comprovante ================\n\n");
    printf("\t\t-------------------------------------------------\n\n");
    printf("\t\tCLIENTE: %s\n\n", usuario[usrIndex].nome);
    printf("\t\tID_CLIENTE: %d\n\n", usuario[usrIndex].ID);
    for (int k = 0; k < contCarrinho; k++)
    {
        printf("\t\t%s\t\tx%d", carrinho[k].nome, carrinho[k].qntPedido);
        printf("\n\t\tPREÇO UNITÁRIO: R$%.2f", carrinho[k].valor);
        printf("\n\t\tSUBTOTAL DE PRODUTO: R$%.2f\n\n", carrinho[k].valor * carrinho[k].qntPedido);

        total += carrinho[k].qntPedido * carrinho[k].valor;
    }

    printf("\n\n\t\tTOTAL DA COMPRA: R$%.2f\n\n", total);
    printf("\t\t-----------------------------------------------------\n");
    printf("\t\t\tOBRIGADO POR ESCOLHER Plaza Mercantil SA\n");
    printf("\t\t=====================================================\n\n");
}

void salvarPedidos(struct ItemCarrinho carrinho[MAX], int contCarrinho, struct Usuario usuario[MAX], int usrIndex)
{
    FILE *arquivo = fopen("storage/pedidos.txt", "a");

    if (arquivo == NULL)
    {
        printf("\nErro ao abrir o arquivo!\n");
        exit(1);
    }

    float total = 0;

    fprintf(arquivo, "\n\n\tPedido: %d\n\n", contCarrinho + 1);
    fprintf(arquivo, "\n\t\t==================== Comprovante ================\n\n");
    fprintf(arquivo, "\t\t-------------------------------------------------\n\n");
    fprintf(arquivo, "\t\tCLIENTE: %s\n\n", usuario[usrIndex].nome);
    fprintf(arquivo, "\t\tID_CLIENTE: %d\n\n", usuario[usrIndex].ID);

    for (int k = 0; k < contCarrinho; k++)
    {
        fprintf(arquivo, "\t\t%s\t\tx%d", carrinho[k].nome, carrinho[k].qntPedido);
        fprintf(arquivo, "\n\t\tPREÇO UNITÁRIO: R$%.2f", carrinho[k].valor);
        fprintf(arquivo, "\n\t\tSUBTOTAL DE PRODUTO: R$%.2f\n\n", carrinho[k].valor * carrinho[k].qntPedido);

        total += carrinho[k].qntPedido * carrinho[k].valor;
    }

    fprintf(arquivo, "\n\n\t\tTOTAL DA COMPRA: R$%.2f\n\n", total);
    fprintf(arquivo, "\t\t-----------------------------------------------------\n");
    fprintf(arquivo, "\t\t\tOBRIGADO POR ESCOLHER Plaza Mercantil SA\n");
    fprintf(arquivo, "\t\t=====================================================\n\n");

    fclose(arquivo);
}

void fazerPedido(struct Produto produto[MAX], struct Usuario usuario[MAX], int cont, int contUsr)
{
    struct ItemCarrinho carrinho[MAX];

    char nomeProduto[MAX];
    int id;
    int qnt, j = 0, i = 0;
    int opcaoContinue;
    int contPedidos = 0;
    int contCarrinho = 0;
    float total = 0;
    int confirm;

    printf("\n\t\tREALIZAR COMPRA\n");

    printf("\nInforme o ID do usuário: ");
    scanf("%d", &id);
    do
    {
        int usuarioEncontrado = -1; // Marcador para indicar se o usuário foi encontrado
        int produtoEncontrado = -1;
        for (i = 0; i < contUsr; i++)
        {
            if (id == usuario[i].ID && usuario[i].tipo == 1)
            {
                usuarioEncontrado = i; // Marca o índice do usuário encontrado
                break;                 // Sai do loop assim que encontra o usuário
            }
        }
        if (usuarioEncontrado != -1)
        {
            limparBuffer();
            printf("\nInforme o nome do produto: ");
            scanf("%99[^\n]", nomeProduto);

            j = -1;
            
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

                    adicionarAoCarrinho(carrinho, produto, &contCarrinho, produtoEncontrado, qnt);
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
                continue;
            }
        }
        else
        {
            printf("\nID de usuário comum não encontrado!\n");
            break;
        }

        if (opcaoContinue == 0)
        {
            printf("\n\t\tCARRINHO\n");

            exibirCarrinho(carrinho, contCarrinho, usuario,usuarioEncontrado);

            printf("\nConfirmar compra?\n1 - Sim\n2 - Não\n");
            scanf("%d", &confirm);

            if (confirm == 1)
            {
                for (int l = 0; l < contPedidos; l++)
                {
                    // Atualiza o estoque do produto original
                    for (int m = 0; m < cont; m++)
                    {
                        if (strcmp(produto[l].nome, produto[m].nome) == 0)
                        {
                            produto[m].estoque -= produto[l].qntPedido;
                            salvarPedidos(carrinho, contCarrinho, usuario, usuarioEncontrado);

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
