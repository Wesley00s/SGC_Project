#include "sgc.h"

void limparBuffer()
{
    while (getchar() != '\n')
        ;
}

// Função para salvar usuários em um arquivo de texto
void salvarUsuarios(struct Usuario usuario[MAX], int cont)
{
     // Abre o arquivo "usuarios.txt" para escrita
    FILE *arquivo = fopen("storage/usuarios.txt", "w");

    if (arquivo == NULL) // Verifica se o arquivo foi aberto corretamente

    {
        printf("\nErro ao abrir o arquivo!\n");
        exit(1);
    }
    
    // Verifica se o arquivo foi aberto corretamente
    for (int i = 0; i < cont; i++)
    {
        // Escreve as informações do usuário no arquivo
        fprintf(arquivo, "\n* Usuário %d", i + 1);
        fprintf(arquivo, "\nPrivilégio: %s", (usuario[i].tipo == 1) ? "Usuário Comum" : "Administrador");
        fprintf(arquivo, "\nNome: %s", usuario[i].nome);
        fprintf(arquivo, "\nID: %d\n", usuario[i].ID);

        if (usuario[i].tipo == 2) // Se o usuário for do tipo administrador, escreve também a senha
        {
            fprintf(arquivo, "Senha: %s\n", usuario[i].senha);
        }
    }

    fclose(arquivo); // Fecha o arquivo
}

// Função para salvar estoque em um arquivo de texto
void salvarEstoque(struct Produto produto[MAX], int cont)
{
    // Abre o arquivo "estoque.txt" para escrita
    FILE *arquivo = fopen("storage/estoque.txt", "w");

    if (arquivo == NULL) // Verifica se o arquivo foi aberto corretamente
    {
        perror("\nErro ao abrir arquivo!\n");
        exit(1);
    }

    // Loop para percorrer todos os produtos e escrever suas informações no arquivo
    for (int i = 0; i < cont; i++)
    {
        fprintf(arquivo, "\n* Produto %d\n", i + 1);
        fprintf(arquivo, "Nome: %s\n", produto[i].nome);
        fprintf(arquivo, "Estoque: %d\n", produto[i].estoque);
        fprintf(arquivo, "Valor: R$%.2lf\n", produto[i].valor);
    }

    fclose(arquivo); // Fecha o arquivo
}

// Função para adicionar um produto ao estoque
int adicionarProduto(struct Produto produto[MAX], int cont)
{
    char nome[MAX]; // Armazena o nome do produto fornecido pelo usuário
    int qntMudarEstoque; // Armazena a quantidade que o usuário deseja adicionar ou remover do estoque do produto
    float novoValProduto; // Armazena o novo valor do produto fornecido pelo usuário
    int encontrouOcorencia = 0; // Sinaliza se o produto já está presente no estoque (1 se encontrado, 0 se não encontrado)
    int operacaoRealizada = 0;  // Sinaliza se alguma operação (adicionar, remover, atualizar preço) foi realizada com sucesso (1 se sim, 0 se não)

    limparBuffer(); // Limpa o buffer do teclado

    printf("\n* Adicionar produto %d\n", cont + 1);
    printf("Nome do produto: ");
    scanf("%99[^\n]", nome);

    for (int i = 0; i < cont; i++) // Loop para verificar se o produto já está no estoque
    {
        if (strcmp(produto[i].nome, nome) == 0)
        {
            operacaoRealizada = 1;  // Indica que uma operação será realizada no produto
            encontrouOcorencia = 1; // Indica que o produto já está presente no estoque

            int opc; // Opção para indicar qual ação o usuário vai tomar após encontrar um produuto já exitente no estoque
            int opcEstoque; // Indica a opção adicionar ou remover

            // Exibe opções ao usuário para atualizar estoque ou preço
            printf("\n\
            Produto %s já presente no estoque!\n\
            Deseja atualizar estoque (atual %d) ou preço (atual R$%.2f)?\n\
            0 - Sair.\n\
            1 - Estoque.\n\
            2 - Preço.\n\
            ", produto[i].nome, produto[i].estoque, produto[i].valor);
            scanf("%d", &opc);

            switch (opc) // Loop para opções do usuário
            {
            case 0: 
                encontrouOcorencia = 0;
                printf("\nSaindo...\n");
                return -1;
                break;
            case 1: // Opções para adicionar ou remover do estoque
                printf("\n\
                1 - Adicionar\n\
                2 - Remover\n\
                ");
                scanf("%d", &opcEstoque);

                if (opcEstoque >= 1 && opcEstoque <= 2)
                {
                    printf("\nInforme a quantidade que deseja %s", (opcEstoque == 1) ? "adicionar: " : "remover: ");
                    scanf("%d", &qntMudarEstoque);
                }
                else
                {
                    printf("\nOpção iválida!\n");
                }
                if (qntMudarEstoque <= 0 || opcEstoque == 2 && qntMudarEstoque > produto[i].estoque)
                {
                    printf("\nOperação não permitida. Verifique se a quantidade que deseja modificar no estoque é permitida!\n");
                    break;
                }
                // Atualiza o estoque do produto
                produto[i].estoque += (opcEstoque == 1) ? qntMudarEstoque : (-qntMudarEstoque);
                printf("\nEstoque atualizado!\n");
                break;
            case 2: // Atualiza o preço do produto

                printf("\nNovo preço do produto. Preço atual R$%.2f: R$ ", produto[i].valor);
                scanf("%f", &novoValProduto); 
                if (novoValProduto > 0)
                {
                    produto[i].valor = novoValProduto;
                    printf("\nPreço atualizado.\n");
                }
                else
                {
                    printf("\nO preço tem ser maior que zero!\n");
                }
                break;
            default:
                printf("\nOpção inválida!\n");
                return -1; // Retorna -1 para indicar a saída da função
            }
        }
    }

    if (!encontrouOcorencia) // Se o produto não foi encontrado no estoque
    {
        printf("Estoque do produto: ");
        scanf("%d", &qntMudarEstoque); // Solicita ao usuário que informe a quantidade do novo produto a ser adicionada ao estoque

        if (qntMudarEstoque >= 0) // Verifica se a quantidade fornecida é válida (não negativa)
        {
            printf("Valor do produto: R$ ");
            scanf("%f", &novoValProduto); // Solicita ao usuário que informe o valor do novo produto

            if (novoValProduto > 0) // Verifica se o valor fornecido é válido (maior que zero)
            {
                strcpy(produto[cont].nome, nome);        // Copia o nome do produto fornecido para a estrutura do produto no estoque
                produto[cont].estoque = qntMudarEstoque; // Define o estoque do novo produto
                produto[cont].valor = novoValProduto;    // Define o valor do novo produto
                printf("\nProduto adicionado com sucesso!\n");
                salvarEstoque(produto, cont + 1); // Salva o estoque atualizado no arquivo (cont + 1)

                return 0; // Retorna 0 para indicar sucesso na operação
            }
            else
            {
                printf("\nO valor tem ser maior que zero!\n"); // Mensagem de erro se o valor fornecido não for válido
            }
        }
        else
        {
            printf("\nDigite um estoque válido!\n"); // Mensagem de erro se a quantidade fornecida não for válida
        }
    }

    if (operacaoRealizada == 1) // Se alguma operação for diferente de adicionar produto
    {
        salvarEstoque(produto, cont); // Atualiza o estoque no arquivo
        return -1;                    // Retorna -1 para indicar a saída da função
    }
}

// Função para listar produtos
void listarProdutos(struct Produto produto[MAX], int cont)
{
    for (int i = 0; i < cont; i++) // Loop para peercorrer todos os produtos listados
    {
        printf("\n* Produto %d\n", i + 1);
        printf("Nome: %s\n", produto[i].nome);
        printf("Estoque: %d\n", produto[i].estoque);
        printf("Valor: R$%.2lf\n", produto[i].valor);
    }
}

int removerProduto(struct Produto produto[MAX], int cont)
{
    char nome[MAX];  // Armazena o nome do produto fornecido pelo usuário
    int control = 0; // Sinaliza se a operação de remoção foi realizada com sucesso (1 se sim, 0 se não)

    limparBuffer(); // Limpa o buffer do teclado

    printf("\n* Remover produto\n");
    printf("\nInforme o nome do produto: ");
    scanf("%99[^\n]", nome); // Solicita ao usuário que informe o nome do produto a ser removido

    for (int i = 0; i < cont; i++) // Loop para percorrer o estoque e encontrar o produto
    {
        if (strcmp(produto[i].nome, nome) == 0) // Verifica se o nome do produto atual é igual ao fornecido pelo usuário
        {
            for (int j = i; j < cont - 1; j++) // Loop para reorganizar o estoque após a remoção do produto
            {
                produto[j] = produto[j + 1]; // Move os produtos uma posição para trás no array
            }
            cont--;      // Decrementa o contador de produtos no estoque
            control = 1; // Indica que a operação de remoção foi realizada com sucesso
            break;       // Sai do loop após encontrar o produto
        }
    }

    if (control) // Se a operação de remoção foi realizada com sucesso
    {
        printf("Produto removido com sucesso!\n");
        salvarEstoque(produto, cont); // Salva o estoque atualizado no arquivo
        return 0;                     // Retorna 0 para indicar sucesso na operação
    }
    else
    {
        printf("\nProduto não encontrado!\n"); // Mensagem de erro se o produto não foi encontrado no estoque
    }
}

// Função para criar admnistrador
void criarAdm(struct Usuario usuario[MAX], int cont)
{
    char senha[MAX]; // Armazena a senha do administrador fornecida pelo usuário
    char nome[MAX];  // Armazena o nome do administrador fornecido pelo usuário

    limparBuffer(); // Limpa o buffer do teclado

    printf("\nCadastrar o nome do administrador: ");
    scanf("%99[^\n]", nome); // Solicita ao usuário que informe o nome do administrador

    limparBuffer(); // Limpa novamente o buffer

    printf("Cadastrar a senha do administrador: ");
    scanf("%49[^\n]", senha); // Solicita ao usuário que informe a senha do administrador

    strcpy(usuario[cont].nome, nome);   // Copia o nome informado para a estrutura de usuário
    strcpy(usuario[cont].senha, senha); // Copia a senha informada para a estrutura de usuário
    usuario[cont].tipo = 2;             // Define o tipo de usuário como administrador

    cont++;                  // Incrementa o contador de usuários
    usuario[cont].ID = cont; // Atribui um ID ao novo usuário
    printf("\nUsuário criado com sucesso!\n");
    salvarUsuarios(usuario, cont); // Salva os usuários no arquivo
}

// Função para criar usuário comum
void criarUsuarioComum(struct Usuario usuario[MAX], int cont)
{
    char senha[MAX]; // Armazena a senha do usuário comum fornecida pelo usuário
    char nome[MAX];  // Armazena o nome do usuário comum fornecido pelo usuário

    limparBuffer(); // Limpa o buffer do teclado

    printf("\nCadastrar o nome do usuario: ");
    scanf("%99[^\n]", nome); // Solicita ao usuário que informe o nome do usuário comum

    strcpy(usuario[cont].nome, nome); // Copia o nome informado para a estrutura de usuário
    strcpy(usuario[cont].senha, " "); // Define uma senha padrão para usuários comuns
    usuario[cont].tipo = 1;           // Define o tipo de usuário como usuário comum

    cont++;                  // Incrementa o contador de usuários
    usuario[cont].ID = cont; // Atribui um ID ao novo usuário
    printf("\nUsuário criado com sucesso!\n");
    salvarUsuarios(usuario, cont); // Salva os usuários no arquivo
}

// Função para adicionar usuários
int adicionarUsuario(struct Usuario usuario[MAX], int cont)
{
    int tipo; // Armazena o tipo de usuário fornecido pelo usuário (1 para comum, 2 para administrador)

    int verifyAdm = 0; // Sinaliza se já existe algum administrador cadastrado (1 se sim, 0 se não)

    for (int i = 0; i < cont; i++) // Loop para verificar se já existe algum administrador cadastrado
    {
        if (usuario[i].tipo == 2)
        {
            verifyAdm = 1; // Indica que já existe um administrador cadastrado
            break;
        }
    }

    if (verifyAdm == 0) // Se não existe administrador cadastrado
    {
        printf("\nNenhum administrador cadastrado, por favor, efetue o cadastro de um administrador para prosseguir.\n");
        usuario[cont].tipo = 2;  // Define o tipo de usuário como administrador
        criarAdm(usuario, cont); // Chama a função para cadastrar um administrador
        return 0;
    }
    else
    {
        printf("\n\
        Informe o tipo de usuário:\n\
        1 - Usuário comum.\n\
        2 - Administrador.\n");
        scanf("%d", &tipo); // Solicita ao usuário que informe o tipo de usuário

        switch (tipo)
        {
        case 1:
            criarUsuarioComum(usuario, cont); // Chama a função para cadastrar um usuário comum
            return 0;
            break;
        case 2:
            criarAdm(usuario, cont); // Chama a função para cadastrar um administrador
            return 0;
            break;
        default:
            printf("\nTipo inválido!\n"); // Mensagem de erro se o tipo informado não for 1 nem 2
            return -1;
            break;
        }
    }
}

// Função para listar usuários
void listarUsuarios(struct Usuario usuario[MAX], int cont)
{
    for (int i = 0; i < cont; i++) // Loop para percorrer todos os usuários
    {
        printf("\n* Usuário %d", i + 1);
        printf("\nPrivilégio: %s", (usuario[i].tipo == 1) ? "Usuário Comum" : "Administrador"); // Exibe o tipo de usuário
        printf("\nNome: %s", usuario[i].nome);                                                  // Exibe o nome do usuário
        printf("\nID: %d\n", usuario[i].ID);                                                    // Exibe o ID do usuário

        if (usuario[i].tipo == 2) // Se o usuário for um administrador
        {
            printf("Senha: %s\n", usuario[i].senha); // Exibe a senha do administrador
        }
    }
}

// Função para remover usuário
int removerUsuario(struct Usuario usuario[MAX], int idUserAtual, int cont)
{
    int id;

    printf("\nInforme o ID do usuário: ");
    scanf("%d", &id); // Solicita ao usuário que informe o ID do usuário a ser removido

    if (usuario[idUserAtual].tipo == 2 && usuario[idUserAtual].ID == id) // Se o usuário atual for um administrador e tentar remover a si mesmo
    {
        printf("\nUm administrador não pode se auto-remover. %s, por favor, cadastre outro admin para realizar a remoção!\n", usuario[idUserAtual].nome);
    }
    else
    {
        if (id >= 0 && id < cont) // Se o ID informado estiver dentro dos limites válidos
        {
            for (int i = id; i < cont - 1; i++) // Loop para reorganizar o array após a remoção do usuário
            {
                usuario[i] = usuario[i + 1];
            }
            cont--; // Decrementa o contador de usuários
            printf("Usuário removido com sucesso!\n");
            salvarUsuarios(usuario, cont); // Salva os usuários no arquivo
            return 0;
        }
        else
        {
            printf("\nUsuário não encontrado!\n"); // Mensagem de erro se o ID informado não for válido
            return -1;
        }
    }
}
