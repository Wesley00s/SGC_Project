#include "sgc.h"

// Função para adicionar um item ao carrinho de compras
void adicionarAoCarrinho(struct ItemCarrinho carrinho[MAX], struct Produto produto[MAX], int *contCarrinho, int produtoIndex, int qnt)
{
    strcpy(carrinho[*contCarrinho].nome, produto[produtoIndex].nome); // Copia o nome do produto para o novo item no carrinho
    carrinho[*contCarrinho].valor = produto[produtoIndex].valor; // Atribui o valor do produto para o novo item no carrinho
    carrinho[*contCarrinho].qntPedido = qnt; // Atribui a quantidade desejada para o novo item no carrinho
    (*contCarrinho)++; // Incrementa o contador do carrinho para refletir a adição do novo item
}

// Função para exibir carrinho de compras
void exibirCarrinho(struct ItemCarrinho carrinho[MAX], int contCarrinho)
{
    printf("\n\t\tCARRINHO\n");
    for (int i = 0; i < contCarrinho; i++) // Loop para percorrer todos os itens no carrinho
    {
        printf("\n\n\t* Produto: %s", carrinho[i].nome);
        printf("\n\tUnidade: R$%.2f", carrinho[i].valor);
        printf("\n\tQuantidade: %d", carrinho[i].qntPedido);
        printf("\n\tTotal produto: R$%.2f", carrinho[i].qntPedido * carrinho[i].valor);
    }
    printf("\n\n");
}

// Função para remover item do carrinho
void removerDoCarrinho(struct ItemCarrinho carrinho[MAX], int *contCarrinho, char *nome)
{
    //  Inicializa uma variável indice para armazenar o índice do item a ser removido. Inicia com -1 para indicar que o item ainda não foi encontrado.
    int indice = -1;

    // Procurando o índice do item pelo nome
    for (int i = 0; i < *contCarrinho; i++)
    {
        if (strcmp(carrinho[i].nome, nome) == 0) // Verifica se o nome do produto no carrinho é igual ao nome fornecido para remoção.
        {
            //  Se encontrar o item, armazena o índice e sai do loop.
            indice = i; 
            break;
        }
    }

    if (indice != -1) // Verifica se o item foi encontrado ou não.
    {
        // Movendo os itens subsequentes uma posição para frente para "remover" o item no índice especificado
        for (int i = indice; i < (*contCarrinho - 1); i++)
        {
            strcpy(carrinho[i].nome, carrinho[i + 1].nome);
            carrinho[i].valor = carrinho[i + 1].valor;
            carrinho[i].qntPedido = carrinho[i + 1].qntPedido;
        }
        (*contCarrinho)--; // Decrementeando o contador de carrinho
        printf("\nProduto %s removido do carrinho!\n", nome);
    }
    else
    {
        printf("\nProduto %s não encontrado no carrinho.\n", nome);
    }
}

// Função para exibir um comprovante de compra
void exibirComprovante(struct ItemCarrinho carrinho[MAX], int contCarrinho, struct Usuario usuario[MAX], int usrIndex)
{
    float total = 0;

    // Exibe o cabeçalho do comprovante
    printf("\n\t\t==================== COMPROVANTE ================\n\n");
    printf("\t\t-------------------------------------------------\n\n");
    printf("\t\tCLIENTE: %s\n\n", usuario[usrIndex].nome);
    printf("\t\tID_CLIENTE: %d\n\n", usuario[usrIndex].ID);

    // Loop para percorrer todos os itens no carrinho
    for (int k = 0; k < contCarrinho; k++)
    {
        // Exibe detalhes de cada item no carrinho
        printf("\t\t%s\t\tx%d", carrinho[k].nome, carrinho[k].qntPedido);
        printf("\n\t\tPREÇO UNITÁRIO: R$%.2f", carrinho[k].valor);
        printf("\n\t\tSUBTOTAL DE PRODUTO: R$%.2f\n\n", carrinho[k].valor * carrinho[k].qntPedido);

        // Calcula o total acumulado
        total += carrinho[k].qntPedido * carrinho[k].valor;
    }

    // Exibe o total da compra e o rodapé do comprovante
    printf("\n\n\t\tTOTAL DA COMPRA: R$%.2f\n\n", total);
    printf("\t\t-----------------------------------------------------\n");
    printf("\t\t\tOBRIGADO POR ESCOLHER Plaza Mercantil SA\n");
    printf("\t\t=====================================================\n\n");
}

// Função para salvar os detalhes do pedido em um arquivo
void salvarPedidos(struct ItemCarrinho carrinho[MAX], int contCarrinho, struct Usuario usuario[MAX], int usrIndex)
{
    // Abre o arquivo no modo de adição (append)
    FILE *arquivo = fopen("storage/pedidos.txt", "a");

    // Verifica se o arquivo foi aberto com sucesso
    if (arquivo == NULL)
    {
        // Exibe uma mensagem de erro e encerra o programa
        printf("\nErro ao abrir o arquivo!\n");
        exit(1);
    }

    float total = 0;

    // Escreve no arquivo os detalhes do pedido
    fprintf(arquivo, "\n\n* PEDIDO\n\n");
    fprintf(arquivo, "\t\t==================== Comprovante ================\n\n");
    fprintf(arquivo, "\t\t-------------------------------------------------\n\n");
    fprintf(arquivo, "\t\tCLIENTE: %s\n\n", usuario[usrIndex].nome);
    fprintf(arquivo, "\t\tID_CLIENTE: %d\n\n", usuario[usrIndex].ID);

    // Loop para percorrer todos os itens no carrinho
    for (int k = 0; k < contCarrinho; k++)
    {
        fprintf(arquivo, "\t\t%s\t\tx %d", carrinho[k].nome, carrinho[k].qntPedido);
        fprintf(arquivo, "\n\t\tPREÇO UNITÁRIO: R$%.2f", carrinho[k].valor);
        fprintf(arquivo, "\n\t\tSUBTOTAL DE PRODUTO: R$%.2f\n\n", carrinho[k].valor * carrinho[k].qntPedido);

        // Calcula o total acumulado
        total += carrinho[k].qntPedido * carrinho[k].valor;
    }

    // Escreve no arquivo o total da compra e o rodapé do comprovante
    fprintf(arquivo, "\n\n\t\tTOTAL DA COMPRA: R$%.2f\n\n", total);
    fprintf(arquivo, "\t\t-----------------------------------------------------\n");
    fprintf(arquivo, "\t\t\tOBRIGADO POR ESCOLHER Plaza Mercantil SA\n");
    fprintf(arquivo, "\t\t=====================================================\n\n");

    // Fecha o arquivo
    fclose(arquivo);
}
void fazerPedido(struct Produto produto[MAX], struct Usuario usuario[MAX], struct ItemCarrinho carrinho[MAX], int cont, int contUsr)
{
    // Variáveis para armazenar dados do pedido
    char nomeProduto[MAX];
    int id;
    int qntComprada, flagProduto = 0, flagUsr = 0;
    int opcaoContinue;
    int contPedidos = 0;
    int contCarrinho = 0;

    printf("\n\t\tREALIZAR COMPRA\n");

    // Solicita o ID do usuário
    printf("\nInforme o ID do usuário: ");
    scanf("%d", &id);

    do // Um loop principal que executa as etapas do pedido até que o usuário decida cancelar ou concluir pedido
    {
        // Marcadores para indicar se o usuário e o produto foram encontrados
        int usuarioEncontrado = -1;
        int produtoEncontrado = -1;

        // Loop para buscar o usuário pelo ID
        for (flagUsr = 0; flagUsr < contUsr; flagUsr++)
        {
            if (id == usuario[flagUsr].ID && usuario[flagUsr].tipo == 1)
            {
                usuarioEncontrado = flagUsr; // Marca o índice do usuário encontrado
                break;                       // Sai do loop assim que encontra o usuário
            }
        }

        if (usuarioEncontrado != -1)
        {
            // Limpa o buffer do teclado
            limparBuffer();

            // Solicita o nome do produto
            printf("\nInforme o nome do produto: ");
            scanf("%99[^\n]", nomeProduto);

            flagProduto = -1;

            // Loop para buscar o produto pelo nome
            for (flagProduto = 0; flagProduto < cont; flagProduto++)
            {
                if (strcmp(nomeProduto, produto[flagProduto].nome) == 0)
                {
                    produtoEncontrado = flagProduto; // Marca o índice do produto encontrado
                    break;                           // Sai do loop assim que encontra o produto
                }
            }

            if (produtoEncontrado != -1)
            {
                int controleDeFluxoDeQuantidade = 0; // Indicador para verificar se o usuário excedeu a quantidade em estoque do produto

                do // Loop para controlar o fluxo caso  o usuário exceda a quantidade em estoque do produto, para que retorne desse ponto
                    {
                        // Limpa o buffer do teclado
                        limparBuffer();

                        // Solicita a quantidade desejada do produto
                        printf("\nInforme a quantidade de %s que deseja comprar (Estoque %d): ", produto[produtoEncontrado].nome, produto[produtoEncontrado].estoque);
                        scanf("%d", &qntComprada);

                        controleDeFluxoDeQuantidade = 0; // Inicializa indicador com zero para garantir uma verificação correta após o usuário exceder a quantidade em estoque do produto

                        if (qntComprada <= produto[produtoEncontrado].estoque)
                        {
                            printf("\nAdicionado ao Carrinho de compras.\n");

                            // Adiciona o produto ao carrinho
                            adicionarAoCarrinho(carrinho, produto, &contCarrinho, produtoEncontrado, qntComprada);

                            // Exibe o carrinho
                            exibirCarrinho(carrinho, contCarrinho);

                            // Incrementa o contador de pedidos
                            contPedidos++;

                            int controleDeFluxoDeRemocao = 0; // Indicador para verificar se o usuário informou o nome de um produto para remover não existente no estoque

                            do // Loop para controlar o fluxo caso o usuário informe o nome de um produto para remover não existente no estoque, para que retorne desse ponto
                            {
                                controleDeFluxoDeQuantidade = 0;
                                // Limpa o buffer do teclado
                                limparBuffer();

                                printf("\nContinuar compra ou finalizar?\n0 - Cancelar compra\n1 - Continuar\n2 - Finalizar\n3 - Remover item\n");
                                scanf("%d", &opcaoContinue);

                                char nomeProdutoRemovido[MAX]; // Guarda o nome do produto infromado pelo usuário para ser removido do estoque

                                switch (opcaoContinue) // Condições para opções do usuário
                                {
                                case 0: // Se o usuário cancelar a compra
                                    printf("\nCompra cancelada!\n");
                                    break;
                                case 1: // Se o usuário escolher continuar adicionando produtos no carrinho
                                    printf("\nContinuar...\n");
                                    break;
                                case 2: // Finaliza compra
                                    // Atualiza o estoque do produto original e salva os pedidos
                                    for (int j = 0; j < contPedidos; j++)
                                    {
                                        for (int i = 0; i < cont; i++)
                                        {
                                            if (strcmp(carrinho[j].nome, produto[i].nome) == 0) // Verifica o nome do produto para salvar no estoque
                                            {
                                                produto[i].estoque -= carrinho[j].qntPedido;                       // Decrementa o estoque do produto
                                                salvarPedidos(carrinho, contCarrinho, usuario, usuarioEncontrado); // Salva pedidos em um arquivo
                                                salvarEstoque(produto, cont);                                      // Atualiza estoque após a compra bem sucedida
                                            }
                                        }
                                    }
                                    printf("\nCompras realizadas com sucesso!\n");
                                    exibirComprovante(carrinho, contCarrinho, usuario, usuarioEncontrado); // Exibe o comprovante da compra
                                    controleDeFluxoDeQuantidade = 0; // Sinalizapara sair do loop após finalizar compras

                                    break;
                                case 3: // Remover produto o carrinho
                                    // Limpa o buffer do teclado
                                    limparBuffer();

                                    // Solicita o nome do produto a ser removido do carrinho
                                    printf("\nNome do produto que deseja remover do carrinho: ");
                                    scanf("%99[^\n]", nomeProdutoRemovido);

                                    // Remove o produto do carrinho
                                    removerDoCarrinho(carrinho, &contCarrinho, nomeProdutoRemovido);

                                    // Exibe o carrinho
                                    exibirCarrinho(carrinho, contCarrinho);

                                    // Sinaliza o controle de fluxo para continuar a remoção
                                    controleDeFluxoDeRemocao = 1;
                                    break;
                                default:
                                    printf("\nOpção inválida!\n");
                                }
                            } while (controleDeFluxoDeRemocao != 0); // Condção para quando o usuário informar um nome de produto não existente no estoque ser verdadeira e voltar do ponto indicado
                        }
                        else
                        {
                            printf("\nEstoque insuficiente!\n");
                            controleDeFluxoDeQuantidade = 1; // Sinaliza o controle de fluxo para continuar a compra
                        }
                    } while (controleDeFluxoDeQuantidade != 0); // Condção para quando o usuário exceder ser verdadeira e voltar do ponto indicado
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

    } while (opcaoContinue != 0 && opcaoContinue != 2); // Condições para as opções do usuário e conclusão de compra
}