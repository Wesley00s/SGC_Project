#include "sgc.h" // Inclui o cabeçalho do sistema

int main()
{
    // Aloca memória para as structs
    struct Usuario *usuario = malloc(MAX_USERS * sizeof(struct Usuario));
    struct Produto *produto = malloc(MAX_PRODUCTS * sizeof(struct Produto));
    struct ItemCarrinho *carrinho = malloc(MAX_CART_ITEMS * sizeof(struct ItemCarrinho));

    char senhaAdm[MAX_NAME_LENGTH];               // Armazena a senha do administrador
    char nomeAdm[MAX_NAME_LENGTH];                // Armazena o nome do administrador
    int contUser = 0;                             // Contador de usuários
    int contProdutos = 0;                         // Contador de produtos
    int opcaoMenuPrincipal;                       // Variável para armazenar a opção do menu principal
    int opcaoMenuAdm;                             // Variável para armazenar a opção do menu de administração
    int opcaoMenuUser;                            // Variável para armazenar a opção do menu de administração de usuários
    int opcaoTipoUsuario;                         // Variável para armazenar o tipo de usuário
    int opcaoUsrComum;                            // Variável para armazenar a opção do menu do usuário comum
    int verifyAdm = 0;                            // Sinaliza se já existe algum administrador cadastrado (1 se sim, 0 se não)

    // Carrega os dados dos arquivos de texto
    carregarUsuarios(usuario, &contUser);
    carregarEstoque(produto, &contProdutos);

    printf("\n\t========================================================================================================\n");
    printf("\n\tDe Plaza Mercantil SA: Bem-vindo ao nosso sistema! Explore, descubra, compre. É um prazer tê-lo conosco!\n");
    printf("\n\t========================================================================================================\n");

    // Criação do primeiro administrador
    for (int i = 0; i < contUser; i++) // Loop para verificar se já existe algum administrador cadastrado
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
        usuario[contUser].tipo = 2;  // Define o tipo de usuário como administrador
        criarAdm(usuario, contUser); // Chama a função para cadastrar um administrador
        contUser++;
    }

    do
    {
        int encontrouAdm = 0;  // Inicializa a variável para verificar se o administrador foi encontrado
        strcpy(nomeAdm, " ");  // Reinicializa a variável que armazena o nome do administrador
        strcpy(senhaAdm, " "); // Reinicializa a variável que armazena a senha do administrador

        // Menu principal para escolher o tipo de usuário
        printf("\n\t\tUSUÁRIO - Deslogado\n");

        printf("\n\
        Qual tipo de usuário você é:\n\
        0 - Encerrar programa.\n\
        1 - Administrador (Senha requerida).\n\
        2 - Usuário comum.\n\
        ");
        scanf("%d", &opcaoTipoUsuario);

        switch (opcaoTipoUsuario)
        {
        case EXIT_PROGRAM:

            printf("\nObrigado por nos escolher. Encerrando programa...\n");
            break;
        case ADMINISTRATOR_OPTION:

            encontrouAdm = 0;
            printf("\n\t\tADMINISTRADOR - Logado\n");
            limparBuffer();
            printf("\nInforme o nome do administrador: ");
            scanf("%99[^\n]", nomeAdm);

            limparBuffer();
            printf("Digite a senha de administrador correspondente ao admin %s: ", nomeAdm);
            scanf("%99[^\n]", senhaAdm);

            // Loop para encontrar o administrador correspondente ao nome e senha informados
            for (int i = 0; i < contUser; i++)
            {
                if (usuario[i].tipo == 2 && strcmp(senhaAdm, usuario[i].senha) == 0 && strcmp(nomeAdm, usuario[i].nome) == 0)
                {
                    encontrouAdm = 1;
                    // Menu de administração para o administrador autenticado
                    printf("\n\
                    Olá %s, o que você deseja?\n\
                    0 - Sair da administração.\n\
                    1 - Administrar usuários.\n\
                    2 - Administrar produtos.\n\
                    ", usuario[i].nome);
                    scanf("%d", &opcaoMenuAdm);

                    switch (opcaoMenuAdm)
                    {
                    case 0:
                        printf("\nEncerrando administração...\n");
                        break;
                    case 1:
                        printf("\n\t\tADMINISTRAÇÃO DE USUÁRIOS\n");
                        do
                        {
                            // Submenu para administrar usuários
                            printf("\n\
                            Opções:\n\
                            0 - Encerrar administração de usuário.\n\
                            1 - Adicionar usuário.\n\
                            2 - Listar usuários.\n\
                            3 - Remover usuário.\n\
                            ");
                            scanf("%d", &opcaoMenuUser);
                            switch (opcaoMenuUser)
                            {
                            case 0:
                                printf("\nEncerrando administração de usuários...\n");
                                break;
                            case 1:
                                if (adicionarUsuario(usuario, contUser) == 0)
                                    contUser++;
                                break;
                            case 2:
                                listarUsuarios(usuario, contUser);
                                break;
                            case 3:
                                if (removerUsuario(usuario, usuario[i].ID, contUser) == 0)
                                    contUser--;
                                break;
                            default:
                                printf("\nOpção inválida!\n");
                            }

                        } while (opcaoMenuUser != 0);
                        break;
                    case 2:
                        do
                        {
                            // Submenu para administrar produtos
                            printf("\n\t\tADMINISTRAÇÃO DE PRODUTOS\n");
                            printf("\n\
                            Escolha uma opção.\n\
                            0 - Encerrar administração de produtos.\n\
                            1 - Adicionar produto.\n\
                            2 - Listar produtos.\n\
                            3 - Remover produto.\n\
                            ");
                            scanf("%d", &opcaoMenuPrincipal);
                            limparBuffer();
                            switch (opcaoMenuPrincipal)
                            {
                            case 0:
                                printf("\nEncerrando administração de produtos...\n");
                                break;
                            case 1:
                                if (adicionarProduto(produto, contProdutos) == 0)
                                    contProdutos++;
                                break;
                            case 2:
                                listarProdutos(produto, contProdutos);
                                break;
                            case 3:
                                if (removerProduto(produto, contProdutos) == 0)
                                    contProdutos--;
                                break;
                            default:
                                printf("Opção inválida\n");
                            }
                        } while (opcaoMenuPrincipal != 0);
                        break;

                    default:
                        printf("\nOpção inválida!\n");
                    }
                    break;
                }
            }
            if (encontrouAdm == 0)
            {
                printf("\nCombinação de senha e admin incorreto!\n");
            }
            break;
        case COMMON_USER_OPTION:

            printf("\n\t\tUSUÁRIO COMUM\n");
            printf("\n\
            O que deseja?\n\
            1 - Fazer pedido\n\
            2 - Listar Produtos\n\
            ");
            scanf("%d", &opcaoUsrComum);

            switch (opcaoUsrComum)
            {
            case 1:
                fazerPedido(produto, usuario, contProdutos, contUser);
                break;
            case 2:
                listarProdutos(produto, contProdutos);
                break;
            default:
                printf("\nOpção inválida!\n");
            }
            break;
        default:
            printf("\nOpção inválida!\n");
        }
    } while (opcaoTipoUsuario != EXIT_PROGRAM); // Loop principal, continua até a opção 0 ser escolhida
    // Salva os arquivos de texto antes de fechar o programa
    salvarUsuarios(usuario, contUser);
    salvarEstoque(produto, contProdutos);

    free(usuario);
    free(produto);
    free(carrinho);
    return 0;
}