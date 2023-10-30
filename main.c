#include "sgc.h"

int main(void)
{
    struct Produto produto[MAX];
    struct Usuario usuario[MAX];
    char senhaAdm[MAX];
    char nomeAdm[MAX];
    int cont = 0;
    int contUser = 0;
    int opcao;
    int opcaoAdm;
    int opcaoUser;
    int opcaoTipo;
    int opcaoUsrComum;
    int encontrouAdm = 0;

    adicionarUsuario(usuario, contUser);
    contUser++;

    do
    {
        printf("\nQual tipo de usuário você é:\n0 - Encerrar programa.\n1 - Administrador.\n2 - Usuário comum.\n");
        scanf("%d", &opcaoTipo);
        
        switch (opcaoTipo)
        {
        case 0:
            printf("\nEncerrando programa...\n");
            break;
        case 1:
            printf("\n\t\tADMINISTRADOR\n");
            encontrouAdm = 1;
            limparBuffer();
            printf("\nInforme o nome do administrador: ");
            scanf("%99[^\n]", nomeAdm);

            limparBuffer();
            printf("\nDigite a senha de administrador: ");
            scanf("%99[^\n]", senhaAdm);

            for (int i = 0; i < contUser; i++)
            {
                if (strcmp(senhaAdm, usuario[i].senha) == 0 && strcmp(nomeAdm, usuario[i].nome) == 0)
                {
                    encontrouAdm = 1;
                    printf("\nOlá %s, que você deseja?\n0 - Sair da administração.\n1 - Administrar usuários.\n2 - Administrar produtos.\n", usuario[i].nome);
                    scanf("%d", &opcaoAdm);
                    
                    switch (opcaoAdm)
                    {
                    case 0:
                        printf("\nEncerrando administração...\n");
                        break;
                    case 1:
                        printf("\n\t\tADIMINISTRAÇÃO DE USUÁRIOS\n");
                        do
                        {
                            printf("\nOpções:\n0 - Encerrar administração de usuário.\n1 - Adicionar usuário.\n2 - Listar usuários.\n3 - Remover usuário.\n");
                            scanf("%d", &opcaoUser);
                            switch (opcaoUser)
                            {
                            case 0:
                                printf("\nEncerrando adiministração de usuários...\n");
                                break;
                            case 1:
                                adicionarUsuario(usuario, contUser);
                                contUser++;
                                break;
                            case 2:
                                listarUsuarios(usuario, contUser);
                                break;
                            case 3:
                                removerUsuario(usuario, contUser);
                                contUser--;
                                break;
                            default:
                                printf("\nOpção inválida!\n");
                            }

                        } while (opcaoUser != 0);
                        break;
                    case 2:
                        do
                        {
                            printf("\n\t\tADIMINISTRAÇÃO DE PRODUTOS\n");
                            printf("\nEscolha uma opção.\n0 - Encerrar administração de produtos.\n1 - Adicionar produto.\n2 - Listar produtos.\n3 - Remover produto.\n");
                            scanf("%d", &opcao);
                            
                            switch (opcao)
                            {
                            case 0:
                                printf("\nEncerrando administração de produtos...\n");
                                break;
                            case 1:
                                adicionarProduto(produto, cont);
                                cont++;
                                break;
                            case 2:
                                listarProdutos(produto, cont);
                                break;
                            case 3:
                                removerProduto(produto, cont);
                                cont--;
                                break;
                            default:
                                printf("Opção inválida\n");
                            }
                        } while (opcao != 0);
                        break;
                    default:
                        printf("\nOpção inválida!\n");
                    }
                    break;
                }
                
            }
            if (encontrouAdm && opcaoUser != 0)
            {
                printf("\nSenha ou admin incorreto!\n");
            }
        break;
        case 2:
            printf("\n\t\tUSUÁRIO COMUM\n");
            printf("\nO que deseja?\n1 - Fazer pedido\n2 - Listar Produtos\n");
            scanf("%d", &opcaoUsrComum);
            
            switch (opcaoUsrComum)
            {
                case 1:
                    fazerPedido(produto, usuario, cont, contUser);
                    break;
                case 2:
                    listarProdutos(produto, cont);
                break;
                default:
                    printf("\nOpção inválida!\n");
                }
            break;
        default:
            printf("\nOpção inválida!\n");
        }
    } while (opcaoTipo != 0);

    return 0;
}
