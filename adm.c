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
    FILE *arquivo2 = fopen("storage/estoque.txt", "w");

    if (arquivo2 == NULL)
    {
        perror("\nErro ao abrir arquivo!\n");
        exit(1);
    }

    for (int i = 0; i < cont; i++)
    {
        fprintf(arquivo2, "\nProduto %d\n", i + 1);
        fprintf(arquivo2, "Nome: %s\n", produto[i].nome);
        fprintf(arquivo2, "Estoque: %d\n", produto[i].estoque);
        fprintf(arquivo2, "Valor: %.2lf\n", produto[i].valor);
    }

    fclose(arquivo2);
}

void adicionarProduto(struct Produto produto[MAX], int cont)
{
    char nome[MAX];
    int qnt;
    float val;

    limparBuffer();
    printf("\nProduto\n");
    printf("Nome do produto: ");
    scanf("%99[^\n]", nome);
    printf("Estoque do produto: ");
    scanf("%d", &qnt);

    if (qnt >= 0)
    {
        printf("Valor do produto: ");
        scanf("%f", &val);

        strcpy(produto[cont].nome, nome);
        produto[cont].estoque = qnt;
        produto[cont].valor = val;

        printf("\nProduto adicionado com sucesso!\n");
        salvarEstoque(produto, cont + 1);
    }
    else
    {
        printf("\nDigite um estoque válido!\n");
    }
}

void listarProdutos(struct Produto produto[MAX], int cont)
{
    for (int i = 0; i < cont; i++)
    {
        printf("\nProduto %d\n", i + 1);
        printf("Nome: %s\n", produto[i].nome);
        printf("Estoque: %d\n", produto[i].estoque);
        printf("Valor: %.2lf\n", produto[i].valor);
    }
}

void removerProduto(struct Produto produto[MAX], int cont)
{
    char nome[MAX];
    int control = 0;

    limparBuffer();
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

void adicionarUsuario(struct Usuario usuario[MAX], int cont)
{
    char senha[MAX];
    char nome[MAX];
    int tipo;

    if (cont == 0)
    {
        printf("\nPressione enter para criar um administrador.");
        usuario[cont].tipo = 2;
        tipo = 2;
    }
    else
    {
        printf("\nInforme o tipo de usuário:\n1 - Usuário comum.\n2 - Administrador.\n");
        scanf("%d", &tipo);
    }

    switch (tipo)
    {
    case 1:
        limparBuffer();

        printf("\nInforme o nome do usuario: ");
        scanf("%99[^\n]", nome);

        strcpy(usuario[cont].nome, nome);
        strcpy(usuario[cont].senha, " ");
        usuario[cont].tipo = 1;

        cont++;
        usuario[cont].ID = cont;
        printf("\nUsuário criado com sucesso!\n");
        salvarUsuarios(usuario, cont);

        break;
    case 2:
        limparBuffer();

        printf("\nInforme o nome do administrador: ");
        scanf("%99[^\n]", nome);
        limparBuffer();

        printf("Informe a senha do administrador: ");
        scanf("%99[^\n]", senha);

        strcpy(usuario[cont].nome, nome);
        strcpy(usuario[cont].senha, senha);
        usuario[cont].tipo = 2;

        cont++;
        usuario[cont].ID = cont;
        printf("\nUsuário criado com sucesso!\n");
        salvarUsuarios(usuario, cont);

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