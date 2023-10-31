#include "sgc.h"

void limparBuffer()
{
    while (getchar() != '\n')
        ;
}

void salvarUsuarios(struct Usuario usuario[MAX], int cont)
{
    FILE *arquivo = fopen("storage/usuarios.txt", "w");

    if (arquivo == NULL)
    {
        printf("\nErro ao abrir o arquivo!\n");
        exit(1);
    }

    for (int i = 0; i < cont; i++)
    {
        fprintf(arquivo, "\nUsuário %d", i + 1);
        fprintf(arquivo, "\nPrivilégio: %s", (usuario[i].tipo == 1) ? "Usuário Comum" : "Administrador");
        fprintf(arquivo, "\nNome: %s", usuario[i].nome);
        fprintf(arquivo, "\nID: %d\n", usuario[i].ID);

        if (usuario[i].tipo == 2)
        {
            fprintf(arquivo, "Senha: %s\n", usuario[i].senha);
        }
    }

    fclose(arquivo);
}

void salvarEstoque(struct Produto produto[MAX], int cont)
{
    FILE *arquivo = fopen("storage/estoque.txt", "w");

    if (arquivo == NULL)
    {
        perror("\nErro ao abrir arquivo!\n");
        exit(1);
    }

    for (int i = 0; i < cont; i++)
    {
        if (produto[i].valor > 0)
        {
            fprintf(arquivo, "\n* Produto\n");
            fprintf(arquivo, "Nome: %s\n", produto[i].nome);
            fprintf(arquivo, "Estoque: %d\n", produto[i].estoque);
            fprintf(arquivo, "Valor: %.2lf\n", produto[i].valor);
        }
    }

    fclose(arquivo);
}

void adicionarProduto(struct Produto produto[MAX], int cont)
{
    char nome[MAX];
    int qntMudarEstoque;
    float novoValProduto;
    int encontrouOcorencia = 0;
    int operacaoRealizada = 0;

    limparBuffer();
    printf("\n* Produto\n");
    printf("Nome do produto: ");
    scanf("%99[^\n]", nome);

    for (int i = 0; i < cont; i++)
    {
        if (strcmp(produto[i].nome, nome) == 0)
        {
            encontrouOcorencia = 1;
            int opc;
            int opcEstoque;
            printf("\nProduto já presente no estoque. Deseja atualizar estoque ou preço?\n0 - Sair.\n1 - Estoque.\n2 - Preço.\n");
            scanf("%d", &opc);

            switch (opc)
            {
            case 0:
                encontrouOcorencia = 0;
                printf("\nSaindo...\n");
                break;
            case 1:
                printf("\n1 - Adicionar\n2 - Remover\n");
                scanf("%d", &opcEstoque);

                printf("\nInforme a quantidade que deseja %s", (opcEstoque == 1) ? "adicionar" : "remover: ");
                scanf("%d", &qntMudarEstoque);
                if (qntMudarEstoque <= 0)
                {
                    printf("\nQuantidade inválida\n");
                    break;
                }
                produto[i].estoque += (opcEstoque == 1) ? qntMudarEstoque : (-qntMudarEstoque);
                printf("\nEstoque atualizado!\n");
                operacaoRealizada = 1;
                break;
            case 2:
                printf("\nNovo preço do produto. Preço atual R$%.2f: ", produto[i].valor);
                scanf("%f", &novoValProduto);
                produto[i].valor = novoValProduto;
                printf("\nPreço atualizado.\n");
                operacaoRealizada = 1;
                break;
            default:
                printf("\nOpção inválida!\n");
            }
        }
    }

    if (!encontrouOcorencia)
    {
        printf("Estoque do produto: ");
        scanf("%d", &qntMudarEstoque);

        if (qntMudarEstoque >= 0)
        {
            printf("Valor do produto: ");
            scanf("%f", &novoValProduto);

            if (novoValProduto > 0)
            {
                strcpy(produto[cont].nome, nome);
                produto[cont].estoque = qntMudarEstoque;
                produto[cont].valor = novoValProduto;
                printf("\nProduto adicionado com sucesso!\n");
                operacaoRealizada = 1;
            }
            else
            {
                printf("\nO valor tem ser maior que zero!\n");
            }
        }
        else
        {
            printf("\nDigite um estoque válido!\n");
        }
    }

    if (operacaoRealizada = 1)
    {
        salvarEstoque(produto, cont + 1);
    }
}

void listarProdutos(struct Produto produto[MAX], int cont)
{
    for (int i = 0; i < cont; i++)
    {
        if (produto[i].valor > 0)
        {
            printf("\nAdicionar produto\n");
            printf("Nome: %s\n", produto[i].nome);
            printf("Estoque: %d\n", produto[i].estoque);
            printf("Valor: %.2lf\n", produto[i].valor);
        }
    }
}

void removerProduto(struct Produto produto[MAX], int cont)
{
    char nome[MAX];
    int control = 0;

    limparBuffer();
    printf("\nRemover produto\n");
    printf("\nInforme o nome do produto: ");
    scanf("%99[^\n]", nome);

    for (int i = 0; i < cont; i++)
    {
        if (strcmp(produto[i].nome, nome) == 0)
        {
            for (int j = i; j < cont - 1; j++)
            {
                produto[j] = produto[j + 1];
            }
            cont--;
            control = 1;
            break;
        }
    }
    if (control)
    {
        printf("Produto removido com sucesso!\n");
        salvarEstoque(produto, cont);
    }
    else
    {
        printf("\nProduto não encontrado!\n");
    }
}

void criarAdm(struct Usuario usuario[MAX], int cont)
{
    char senha[MAX];
    char nome[MAX];

    limparBuffer();

    printf("\nCadastrar o nome do administrador: ");
    scanf("%99[^\n]", nome);
    limparBuffer();

    printf("Cadastrar a senha do administrador: ");
    scanf("%49[^\n]", senha);

    strcpy(usuario[cont].nome, nome);
    strcpy(usuario[cont].senha, senha);
    usuario[cont].tipo = 2;

    cont++;
    usuario[cont].ID = cont;
    printf("\nUsuário criado com sucesso!\n");
    salvarUsuarios(usuario, cont);
}

void criarUsuarioComum(struct Usuario usuario[MAX], int cont)
{
    char senha[MAX];
    char nome[MAX];

    limparBuffer();

    printf("\nCadastrar o nome do usuario: ");
    scanf("%99[^\n]", nome);

    strcpy(usuario[cont].nome, nome);
    strcpy(usuario[cont].senha, " ");
    usuario[cont].tipo = 1;

    cont++;
    usuario[cont].ID = cont;
    printf("\nUsuário criado com sucesso!\n");
    salvarUsuarios(usuario, cont);
}

void adicionarUsuario(struct Usuario usuario[MAX], int cont)
{
    int tipo;

        printf("\nInforme o tipo de usuário:\n1 - Usuário comum.\n2 - Administrador.\n");
        scanf("%d", &tipo);

        switch (tipo)
        {
        case 1:
            criarUsuarioComum(usuario, cont);
            break;
        case 2:
            criarAdm(usuario, cont);
            break;
        default:
            printf("\nTipo iválido!\n");
            break;
    }
}

void listarUsuarios(struct Usuario usuario[MAX], int cont)
{
    for (int i = 0; i < cont; i++)
    {
        printf("\nUsuário %d", i + 1);
        printf("\nPrivilégio: %s", (usuario[i].tipo == 1) ? "Usuário Comum" : "Administrador");
        printf("\nNome: %s", usuario[i].nome);
        printf("\nID: %d\n", usuario[i].ID);

        if (usuario[i].tipo == 2)
        {
            printf("Senha: %s\n", usuario[i].senha);
        }
    }
}

void removerUsuario(struct Usuario usuario[MAX], int cont)
{
    int id;

    printf("\nInforme o ID do usuário: ");
    scanf("%d", &id);

    if (id >= 0 && id <= cont)
    {
        for (int i = id; i < cont - 1; i++)
        {
            usuario[i] = usuario[i + 1];
        }
        cont--;
        printf("Usuário removido com sucesso!\n");
        salvarUsuarios(usuario, cont);
    }
    else
    {
        printf("\nUsuário não encontrado!\n");
    }
}