#include "sgc.h"

// Função para adicionar um item ao carrinho de compras
int adicionarAoCarrinho(struct Usuario usuario[MAX_USERS], struct Produto produto[MAX_PRODUCTS], int *contCarrinho, int produtoIndex, int qnt, int estoqueAtualizado)
{
    int ocorrencia = 0; // Variável para verificar se o produto já existe no carrinho
    int adicionar;      // Armazena a quantidade de produtos que o usuário deseja adicionar

    // Loop para verificar se o produto já existe no carrinho
    for (int i = 0; i < *contCarrinho; i++)
    {
        for (int i = 0; i < *contCarrinho; i++)
        {
            if (strcmp(usuario[i].carrinho[i].nome, produto[produtoIndex].nome) == 0) // Loop para verificar se o produto já existe no carrinho
            {
                ocorrencia = 1;
                printf("\nProduto já presente no carrinho, quantidade %d.\n", usuario[i].carrinho[i].qntPedido);
                printf("\nDeseja voltar ou adicionar mais unidades de %s?\n\
                0 - Voltar\n\
                1 - Adicionar\n\
                ",    produto[produtoIndex].nome);
                scanf("%d", &adicionar);

                if (adicionar == 1)
                {
                    int qntAdd;
                    printf("\nInforme a quantidade: ");
                    scanf("%d", &qntAdd);
                    printf("\nMais %d unidades de %s adicionado ao carrinho!\n", qntAdd, produto[produtoIndex].nome);
                    usuario[i].carrinho[i].qntPedido += qntAdd; // Se o produto já existe, apenas incrementa a quantidade desejada
                    produto[produtoIndex].estoque -= qntAdd;    // Se o produto já existe
                    break;
                }
                return 1;
                break;
            }
        }
    }

    if (ocorrencia == 0)
    {
        strcpy(usuario[*contCarrinho].carrinho[*contCarrinho].nome, produto[produtoIndex].nome); // Copia o nome do produto para o novo item no carrinho
        usuario[*contCarrinho].carrinho[*contCarrinho].valor = produto[produtoIndex].valor;      // Atribui o valor do produto para o novo item no carrinho
        usuario[*contCarrinho].carrinho[*contCarrinho].qntPedido = qnt;                          // Atribui a quantidade desejada para o novo item no carrinho
        (*contCarrinho)++;                                                                       // Incrementa o contador do carrinho para refletir a adição do novo item
        produto[produtoIndex].estoque -= qnt;                                                    // Atualiza o estoque
        salvarEstoque(produto, *contCarrinho);                                                   // Salva o estoque atualizado
        return 0;
    }
}

// Função para exibir carrinho de compras
void exibirCarrinho(struct Usuario usuario[MAX_USERS], int contCarrinho)
{
    printf("\n\t\tCARRINHO\n");
    for (int i = 0; i < contCarrinho; i++) // Loop para percorrer todos os itens no carrinho
    {
        printf("\n\n\t* Produto: %s", usuario[i].carrinho[i].nome);
        printf("\n\tUnidade: R$%.2f", usuario[i].carrinho[i].valor);
        printf("\n\tQuantidade: %d", usuario[i].carrinho[i].qntPedido);
        printf("\n\tTotal produto: R$%.2f", usuario[i].carrinho[i].qntPedido * usuario[i].carrinho[i].valor);
    }
    printf("\n\n");
}
// Função para remover item do carrinho
void removerDoCarrinho(struct Usuario usuario[MAX_USERS], int *contCarrinho, char *nome)
{
    int indice = -1;

    // Procurando o índice do item pelo nome
    for (int i = 0; i < *contCarrinho; i++)
    {
        if (strcmp(usuario[i].carrinho[i].nome, nome) == 0)
        {
            indice = i;
            break;
        }
    }

    if (indice != -1)
    {
        // Move os itens subsequentes uma posição para trás, começando do item a ser removido
        for (int j = indice; j < *contCarrinho - 1; j++)
        {
            strcpy(usuario[j].carrinho[j].nome, usuario[j + 1].carrinho[j + 1].nome);
            usuario[j].carrinho[j].valor = usuario[j + 1].carrinho[j + 1].valor;
            usuario[j].carrinho[j].qntPedido = usuario[j + 1].carrinho[j + 1].qntPedido;
        }

        // Limpar os dados do último item no carrinho
        strcpy(usuario[*contCarrinho - 1].carrinho[*contCarrinho - 1].nome, "");
        usuario[*contCarrinho - 1].carrinho[*contCarrinho - 1].valor = 0.0;
        usuario[*contCarrinho - 1].carrinho[*contCarrinho - 1].qntPedido = 0;

        // Decrementa o contador de carrinho após a remoção
        (*contCarrinho)--;
        printf("\nProduto %s removido do carrinho!\n", nome);
    }
    else
    {
        printf("\nProduto %s não encontrado no carrinho.\n", nome);
    }
}

// Função para exibir um comprovante de compra
void exibirComprovante(struct Usuario usuario[MAX_USERS], int contCarrinho, int usrIndex)
{
    float total = 0; // Total da compra

    // Exibe o cabeçalho do comprovante
    printf("\n\t\t==================== COMPROVANTE ================\n\n");
    printf("\t\t-------------------------------------------------\n\n");
    printf("\t\tCLIENTE: %s\n\n", usuario[usrIndex].nome);
    printf("\t\tID_CLIENTE: %d\n\n", usuario[usrIndex].ID);

    // Loop para percorrer todos os itens no carrinho
    for (int i = 0; i < contCarrinho; i++)
    {
        // Exibe detalhes de cada item no carrinho
        printf("\t\t%s\t\tx%d", usuario[i].carrinho[i].nome, usuario[i].carrinho[i].qntPedido);
        printf("\n\t\tPREÇO UNITÁRIO: R$%.2f", usuario[i].carrinho[i].valor);
        printf("\n\t\tSUBTOTAL DE PRODUTO: R$%.2f\n\n", usuario[i].carrinho[i].valor * usuario[i].carrinho[i].qntPedido);

        // Calcula o total acumulado
        total += usuario[i].carrinho[i].qntPedido * usuario[i].carrinho[i].valor;
    }

    // Exibe o total da compra e o rodapé do comprovante
    printf("\n\n\t\t-----------------------------------------------------\n");
    printf("\n\t\tTOTAL DA COMPRA: R$%.2f\n\n", total);
    printf("\t\t-----------------------------------------------------\n");
    printf("\t\t\tOBRIGADO POR ESCOLHER Plaza Mercantil SA\n");
    printf("\t\t=====================================================\n\n");
}

// Função para salvar os detalhes do pedido em um arquivo
void salvarPedidos(struct Usuario usuario[MAX_USERS], int contCarrinho, int usrIndex)
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

    float total = 0; // Total da compra

    // Escreve no arquivo os detalhes do pedido
    fprintf(arquivo, "\n\n* PEDIDO\n\n");
    fprintf(arquivo, "\t\t==================== Comprovante ================\n\n");
    fprintf(arquivo, "\t\t-------------------------------------------------\n\n");
    fprintf(arquivo, "\t\tCLIENTE: %s\n\n", usuario[usrIndex].nome);
    fprintf(arquivo, "\t\tID_CLIENTE: %d\n\n", usuario[usrIndex].ID);

    // Loop para percorrer todos os itens no carrinho
    for (int i = 0; i < contCarrinho; i++)
    {
        fprintf(arquivo, "\t\t%s\t\tx %d", usuario[i].carrinho[i].nome, usuario[i].carrinho[i].qntPedido);
        fprintf(arquivo, "\n\t\tPREÇO UNITÁRIO: R$%.2f", usuario[i].carrinho[i].valor);
        fprintf(arquivo, "\n\t\tSUBTOTAL DE PRODUTO: R$%.2f\n\n", usuario[i].carrinho[i].valor * usuario[i].carrinho[i].qntPedido);

        // Calcula o total acumulado
        total += usuario[i].carrinho[i].qntPedido * usuario[i].carrinho[i].valor;
    }

    // Escreve no arquivo o total da compra e o rodapé do comprovante
    fprintf(arquivo, "\n\n\t\t-----------------------------------------------------\n");
    fprintf(arquivo, "\n\t\tTOTAL DA COMPRA: R$%.2f\n\n", total);
    fprintf(arquivo, "\t\t-----------------------------------------------------\n");
    fprintf(arquivo, "\t\t\tOBRIGADO POR ESCOLHER Plaza Mercantil SA\n");
    fprintf(arquivo, "\t\t=====================================================\n\n");

    // Fecha o arquivo
    fclose(arquivo);
}

void fazerPedido(struct Produto produto[MAX_PRODUCTS], struct Usuario usuario[MAX_USERS], int cont, int contUsr)
{
    // Variáveis para armazenar dados do pedido
    char nomeProduto[MAX_NAME_LENGTH];
    int id;
    int qntComprada = 0, flagProduto = 0, flagUsr = 0;
    int opcaoContinue;
    int contPedidos = 0;
    int contCarrinho = 0;
    char input[MAX_NAME_LENGTH];
    int valid;
    
    do
    {
        // Solicita a entrada do usuário como uma string
        printf("\nInforme o ID do usuário: ");
        scanf("%s", input);

        // Verifica se cada caractere da string é um dígito
        int i, valid = 1;
        for (i = 0; input[i] != '\0'; i++)
        {
            if (!isdigit(input[i]))
            {
                valid = 0;
                break;
            }
        }

    } while (!valid);

    // Converte a string para um inteiro
    sscanf(input, "%d", &id);

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

            int controleDeFluxoDeQuantidade = 0; // Indicador para verificar se o usuário excedeu a quantidade em estoque do produto
            if (produtoEncontrado != -1)
            {
                do // Loop para controlar o fluxo caso  o usuário exceda a quantidade em estoque do produto, para que retorne desse ponto
                {
                    int ocorrenciaProdutoNoCarrinho = 0; // Verificador de produto exitente no carrinho

                    for (int i = 0; i < contCarrinho; i++)
                    {
                        if (strcmp(usuario[usuarioEncontrado].carrinho[i].nome, produto[produtoEncontrado].nome) == 0) // Loop para verificar se o produto já existe no carrinho
                        {
                            ocorrenciaProdutoNoCarrinho = 1;
                        }
                    }

                    if (ocorrenciaProdutoNoCarrinho == 0)
                    {
                        limparBuffer();
                        // Solicita a quantidade desejada do produto
                        printf("\nInforme a quantidade de %s que deseja comprar (Estoque %d): ", produto[produtoEncontrado].nome, produto[produtoEncontrado].estoque);
                        scanf("%d", &qntComprada);
                    }

                    // Limpa o buffer do teclado

                    controleDeFluxoDeQuantidade = 0; // Inicializa indicador com zero para garantir uma verificação correta após o usuário exceder a quantidade em estoque do produto

                    if (qntComprada <= produto[produtoEncontrado].estoque && qntComprada > 0)
                    {
                        printf("\nAdicionado ao Carrinho de compras.\n");

                        // Adiciona o produto ao carrinho
                        adicionarAoCarrinho(usuario, produto, &contCarrinho, produtoEncontrado, qntComprada, produto[produtoEncontrado].estoque);

                        // Exibe o carrinho
                        exibirCarrinho(usuario, contCarrinho);

                        // Incrementa o contador de pedidos
                        contPedidos++;

                        int controleDeFluxoDeRemocao = 0; // Indicador para verificar se o usuário informou o nome de um produto para remover não existente no estoque

                        do // Loop para controlar o fluxo caso o usuário informe o nome de um produto para remover não existente no estoque, para que retorne desse ponto
                        {
                            // Limpa o buffer do teclado
                            limparBuffer();

                            printf("\n\
                            Continuar compra ou finalizar?\n\
                            0 - Cancelar compra\n\
                            1 - Continuar\n\
                            2 - Finalizar\n\
                            3 - Remover item\n\
                            ");
                            scanf("%d", &opcaoContinue);

                            char nomeProdutoRemovido[MAX_NAME_LENGTH]; // Guarda o nome do produto infromado pelo usuário para ser removido do estoque

                            switch (opcaoContinue) // Condições para opções do usuário
                            {
                            case CANCEL_PURCHASE: // Se o usuário cancelar a compra

                                printf("\nCompra cancelada!\n");
                                break;
                            case CONTINUE_SHOPPING: // Se o usuário escolher continuar adicionando produtos no carrinho
                                
                                printf("\nContinuar...\n");
                                controleDeFluxoDeRemocao = 0;
                                break;
                            case FINALIZE_PURCHASE: // Finaliza compra

                                    // Atualiza o estoque do produto original e salva os pedidos
                                for (int j = 0; j < contCarrinho; j++)
                                {
                                    for (int i = 0; i < cont; i++)
                                    {
                                        if (strcmp(usuario[i].carrinho[j].nome, produto[i].nome) == 0)
                                        {
                                            produto[i].estoque -= usuario[i].carrinho[j].qntPedido; // Atualiza estoque
                                            // Salva o estoque atualizado
                                            salvarEstoque(produto, cont);
                                        }
                                    }
                                }

                                salvarPedidos(usuario, contCarrinho, usuarioEncontrado); // Salva pedidos em um arquivo
                                printf("\nCompras realizadas com sucesso!\n");
                                exibirComprovante(usuario, contCarrinho, usuarioEncontrado); // Exibe o comprovante da compra

                                opcaoContinue = 0; // Sinaliza para sair do loop após finalizar compras
                                controleDeFluxoDeRemocao = 0;

                                break;
                            case REMOVE_ITEM: // Remover produto o carrinho
                            
                                // Limpa o buffer do teclado
                                limparBuffer();

                                // Solicita o nome do produto a ser removido do carrinho
                                printf("\nNome do produto que deseja remover do carrinho: ");
                                scanf("%99[^\n]", nomeProdutoRemovido);

                                // Remove o produto do carrinho
                                removerDoCarrinho(usuario, &contCarrinho, nomeProdutoRemovido);

                                // Exibe o carrinho
                                exibirCarrinho(usuario, contCarrinho);

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

void carregarUsuarios(struct Usuario usuario[MAX_USERS], int *contUser)
{
    // Abre o arquivo "usuarios.txt" no modo de leitura.
    FILE *arquivo = fopen("storage/usuarios.txt", "r");

    // Verifica se o arquivo foi aberto corretamente.
    if (arquivo == NULL)
    {
        perror("Arquivo de dados não encontrado. Iniciando com vetor vazio.");
        *contUser = 0;
        return;
    }

    // Lê o valor de contUser (número de usuários) do arquivo.
    fscanf(arquivo, "%d", contUser);

    // Verifica se o número de usuários não excede o limite máximo (MAX_USERS).
    if (*contUser > MAX_USERS)
    {
        fprintf(stderr, "Número de usuários excede o limite. Ajuste o MAX_USERS.\n");
        *contUser = 0;
        fclose(arquivo);
        return;
    }

    // Loop para ler cada usuário do arquivo.
    for (int i = 0; i < *contUser; i++)
    {
        char tipoStr[20];
        // Lê o tipo de usuário (administrador ou não).
        fscanf(arquivo, "\n* Usuário %*d\nPrivilégio: %19s", tipoStr);
        usuario[i].tipo = (strcmp(tipoStr, "Administrador") == 0) ? 2 : 1;

        // Limpa o buffer do nome antes da leitura.
        while (fgetc(arquivo) != '\n')
            ;

        // Lê o nome.
        fscanf(arquivo, "Nome: %49[^\n]", usuario[i].nome);

        // Lê o ID.
        fscanf(arquivo, "\nID: %d", &usuario[i].ID);

        // Se o usuário for do tipo administrador, ler também a senha.
        if (usuario[i].tipo == 2)
        {
            fscanf(arquivo, "\nSenha: %19s", usuario[i].senha);
        }
        else
        {
            // Consumir a nova linha depois do ID para garantir que a leitura continue corretamente.
            fgetc(arquivo);
        }
    }

    // Fecha o arquivo após a leitura.
    fclose(arquivo);
}

void carregarEstoque(struct Produto produto[MAX_PRODUCTS], int *contProduto)
{
    // Abre o arquivo "estoque.txt" no modo de leitura.
    FILE *arquivo = fopen("storage/estoque.txt", "r");

    // Verifica se o arquivo foi aberto corretamente.
    if (arquivo == NULL)
    {
        perror("Arquivo de dados não encontrado. Iniciando com vetor vazio.");
        *contProduto = 0;
        return;
    }

    // Lê o valor de contProduto (número de produtos) do arquivo.
    fscanf(arquivo, "%d", contProduto);

    // Verifica se o número de produtos não excede o limite máximo (MAX_PRODUCTS).
    if (*contProduto > MAX_PRODUCTS)
    {
        fprintf(stderr, "Número de produtos excede o limite. Ajuste o MAX_PRODUCTS.\n");
        *contProduto = 0;
        fclose(arquivo);
        return;
    }

    // Loop para ler cada produto do arquivo.
    for (int i = 0; i < *contProduto; i++)
    {
        // Utiliza variáveis temporárias para armazenar os valores lidos.
        char nomeProduto[MAX_NAME_LENGTH];
        int estoqueProduto;
        float valorProduto;

        // Lê os valores do arquivo.
        fscanf(arquivo, "\n* Produto %*d\nNome: %49s\nEstoque: %d\nValor: R$%f\nNome do Pedido: %49s", nomeProduto, &estoqueProduto, &valorProduto, produto[i].nomePedido);

        // Atribui os valores lidos à struct Produto.
        strncpy(produto[i].nome, nomeProduto, sizeof(produto[i].nome) - 1);
        produto[i].nome[sizeof(produto[i].nome) - 1] = '\0'; // Garante que a string seja terminada corretamente.
        produto[i].estoque = estoqueProduto;
        produto[i].valor = valorProduto;
    }

    // Fecha o arquivo após a leitura.
    fclose(arquivo);
}
