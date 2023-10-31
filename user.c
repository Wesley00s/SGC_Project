#include "sgc.h"

/*
adicionarAoCarrinho:

Objetivo: Adiciona um item ao carrinho de compras.
Parâmetros:
carrinho[MAX]: Array de estruturas representando o carrinho.
produto[MAX]: Array de estruturas representando os produtos disponíveis.
contCarrinho: Ponteiro para o contador de itens no carrinho.
produtoIndex: Índice do produto a ser adicionado.
qnt: Quantidade do produto a ser adicionada.
*/

void adicionarAoCarrinho(struct ItemCarrinho carrinho[MAX], struct Produto produto[MAX], int *contCarrinho, int produtoIndex, int qnt)
{
    strcpy(carrinho[*contCarrinho].nome, produto[produtoIndex].nome);
    carrinho[*contCarrinho].valor = produto[produtoIndex].valor;
    carrinho[*contCarrinho].qntPedido = qnt;
    (*contCarrinho)++;
}

/*
exibirCarrinho:

Objetivo: Exibe os itens presentes no carrinho.
Parâmetros:
carrinho[MAX]: Array de estruturas representando o carrinho.
contCarrinho: Número atual de itens no carrinho.
*/

void exibirCarrinho(struct ItemCarrinho carrinho[MAX], int contCarrinho)
{
    printf("\n\t\tCARRINHO\n");
    for (int i = 0; i < contCarrinho; i++)
    {
        printf("\n\n\t* Produto: %s", carrinho[i].nome);
        printf("\n\tUnidade: R$%.2f", carrinho[i].valor);
        printf("\n\tQuantidade: %d", carrinho[i].qntPedido);
        printf("\n\tTotal produto: R$%.2f", carrinho[i].qntPedido * carrinho[i].valor);
    }
    printf("\n\n");
}

/*
removerDoCarrinho:

Objetivo: Remove um item do carrinho.
Parâmetros:
carrinho[MAX]: Array de estruturas representando o carrinho.
contCarrinho: Ponteiro para o contador de itens no carrinho.
nome: Nome do produto a ser removido.
*/

void removerDoCarrinho(struct ItemCarrinho carrinho[MAX], int *contCarrinho, char *nome)
{
    int indice = -1;

    // Procurando o índice do item pelo nome
    for (int i = 0; i < *contCarrinho; i++)
    {
        if (strcmp(carrinho[i].nome, nome) == 0)
        {
            indice = i;
            break;
        }
    }

    if (indice != -1)
    {
        // Movendo os itens subsequentes uma posição para frente para "remover" o item no índice especificado
        for (int i = indice; i < (*contCarrinho - 1); i++)
        {
            strcpy(carrinho[i].nome, carrinho[i + 1].nome);
            carrinho[i].valor = carrinho[i + 1].valor;
            carrinho[i].qntPedido = carrinho[i + 1].qntPedido;
        }
        (*contCarrinho)--;
        printf("\nProduto %s removido do carrinho!\n", nome);
    }
    else
    {
        printf("\nProduto %s não encontrado no carrinho.\n", nome);
    }
}

/*
exibirComprovante:

Objetivo: Exibe um comprovante de compra com detalhes.
Parâmetros:
carrinho[MAX]: Array de estruturas representando o carrinho.
contCarrinho: Número atual de itens no carrinho.
usuario[MAX]: Array de estruturas representando os usuários.
usrIndex: Índice do usuário para o qual o comprovante está sendo gerado.
*/

void exibirComprovante(struct ItemCarrinho carrinho[MAX], int contCarrinho, struct Usuario usuario[MAX], int usrIndex)
{
    float total = 0;

    printf("\n\t\t==================== COMPROVANTE ================\n\n");
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

/*
salvarPedidos:

Objetivo: Salva os detalhes do pedido em um arquivo.
Parâmetros:
carrinho[MAX]: Array de estruturas representando o carrinho.
contCarrinho: Número atual de itens no carrinho.
usuario[MAX]: Array de estruturas representando os usuários.
usrIndex: Índice do usuário que fez o pedido.
*/

void salvarPedidos(struct ItemCarrinho carrinho[MAX], int contCarrinho, struct Usuario usuario[MAX], int usrIndex)
{
    FILE *arquivo = fopen("storage/pedidos.txt", "a");

    if (arquivo == NULL)
    {
        printf("\nErro ao abrir o arquivo!\n");
        exit(1);
    }

    float total = 0;

    fprintf(arquivo, "\n\n* PEDIDO\n\n");
    fprintf(arquivo, "\t\t==================== Comprovante ================\n\n");
    fprintf(arquivo, "\t\t-------------------------------------------------\n\n");
    fprintf(arquivo, "\t\tCLIENTE: %s\n\n", usuario[usrIndex].nome);
    fprintf(arquivo, "\t\tID_CLIENTE: %d\n\n", usuario[usrIndex].ID);

    for (int k = 0; k < contCarrinho; k++)
    {
        fprintf(arquivo, "\t\t%s\t\tx %d", carrinho[k].nome, carrinho[k].qntPedido);
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

/*
fazerPedido:

Objetivo: Permite que um usuário faça pedidos.
Parâmetros:
produto[MAX]: Array de estruturas representando os produtos disponíveis.
usuario[MAX]: Array de estruturas representando os usuários.
carrinho[MAX]: Array de estruturas representando o carrinho.
cont: Número atual de produtos disponíveis.
contUsr: Número atual de usuários.
*/

void fazerPedido(struct Produto produto[MAX], struct Usuario usuario[MAX], struct ItemCarrinho carrinho[MAX], int cont, int contUsr)
{
    char nomeProduto[MAX];
    int id;
    int qntComprada, flagProduto = 0, flagUsr = 0;
    int opcaoContinue;
    int contPedidos = 0;
    int contCarrinho = 0;

    printf("\n\t\tREALIZAR COMPRA\n");

    printf("\nInforme o ID do usuário: ");
    scanf("%d", &id);
    do
    {
        int usuarioEncontrado = -1; // Marcador para indicar se o usuário foi encontrado
        int produtoEncontrado = -1;
        int numVendas = 0;
        float totalVendas = 0;

        for (flagUsr = 0; flagUsr < contUsr; flagUsr++)
        {
            if (id == usuario[flagUsr].ID && usuario[flagUsr].tipo == 1)
            {
                usuarioEncontrado = flagUsr; // Marca o índice do usuário encontrado
                break;                 // Sai do loop assim que encontra o usuário
            }
        }
        if (usuarioEncontrado != -1)
        {
            limparBuffer();
            printf("\nInforme o nome do produto: ");
            scanf("%99[^\n]", nomeProduto);

            flagProduto = -1;

            for (flagProduto = 0; flagProduto < cont; flagProduto++)
            {
                if (strcmp(nomeProduto, produto[flagProduto].nome) == 0)
                {
                    produtoEncontrado = flagProduto; // Marca o índice do produto encontrado
                    break;                 // Sai do loop assim que encontra o produto
                }
            }

            if (produtoEncontrado != -1)
            {
                int controleDeFluxoDeQuantidade = 0;
                do
                {
                    limparBuffer();
                    printf("\nInforme a quantidade de %s que deseja comprar (Estoque %d): ", produto[produtoEncontrado].nome, produto[produtoEncontrado].estoque);
                    scanf("%d", &qntComprada);

                    controleDeFluxoDeQuantidade = 0;
                    if (qntComprada <= produto[produtoEncontrado].estoque)
                    {
                        printf("\nAdicionado ao Carrinho de compras.\n");

                        adicionarAoCarrinho(carrinho, produto, &contCarrinho, produtoEncontrado, qntComprada);
                        exibirCarrinho(carrinho, contCarrinho);
                        contPedidos++;
                        int controleDeFluxoDeRemocao = 0;

                        do
                        {
                            controleDeFluxoDeRemocao = 0;

                            printf("\nContinuar compra ou finalizar?\n0 - Cancelar compra\n1 - Continuar\n2 - Finalizar\n3 - Remover item\n");
                            scanf("%d", &opcaoContinue);

                            char nomeProdutoRemovido[MAX];

                            switch (opcaoContinue)
                            {
                            case 0:
                                printf("\nCompra cancelada!\n");
                                break;
                            case 1:
                                printf("\nContinuar...\n");
                                break;
                            case 2:
                                for (int j = 0; j < contPedidos; j++)
                                {
                                    // Atualiza o estoque do produto original
                                    for (int i = 0; i < cont; i++)
                                    {
                                        if (strcmp(carrinho[j].nome, produto[i].nome) == 0)
                                        {
                                            produto[i].estoque -= carrinho[j].qntPedido;
                                            salvarPedidos(carrinho, contCarrinho, usuario, usuarioEncontrado);
                                            salvarEstoque(produto, cont);
                                        }
                                    }
                                }
                                printf("\nCompras realizadas com sucesso!\n");
                                exibirComprovante(carrinho, contCarrinho, usuario, usuarioEncontrado);
                                break;
                            case 3:
                                limparBuffer();
                                printf("\nNome do produto que deseja remover do carrinho: ");
                                scanf("%99[^\n]", nomeProdutoRemovido);
                                removerDoCarrinho(carrinho, &contCarrinho, nomeProdutoRemovido);
                                exibirCarrinho(carrinho, contCarrinho);
                                controleDeFluxoDeRemocao = 1;
                                break;
                            default:
                                printf("\nOpção inválida!\n");
                            }
                        } while (controleDeFluxoDeRemocao != 0);
                    }
                    else
                    {
                        printf("\nEstoque insuficiente!\n");
                    }
                } while (controleDeFluxoDeQuantidade != 0);
            }
            else
            {
                printf("\nProduto não encontrado!\n");
            }
        }
        else
        {
            printf("\nID de usuário comum não encontrado!\n");
            break;
        }

    } while (opcaoContinue != 0 && opcaoContinue != 2);
}