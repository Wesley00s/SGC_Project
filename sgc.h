#ifndef LIB_H
#define LIB_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Constantes para tipos de usuários
#define COMMON_USER 1
#define ADMINISTRATOR 2

// Constantes para os menus de opções
#define EXIT_PROGRAM 0
#define ADMINISTRATOR_OPTION 1
#define COMMON_USER_OPTION 2

// Constantes para controlar o fluxo
#define CANCEL_PURCHASE 0
#define CONTINUE_SHOPPING 1
#define FINALIZE_PURCHASE 2
#define REMOVE_ITEM 3

// Constantes para tamanho de arrays
#define MAX_USERS 100
#define MAX_PRODUCTS 200
#define MAX_CART_ITEMS 500
#define MAX_NAME_LENGTH 50

// Constantes para opções extras
#define EXIT 0
#define UPDATE_INVENTORY 1
#define UPDATE_PRICE 2

// Função para limpar buffer do teclado
void limparBuffer();

struct ItemCarrinho
{
    char nome[MAX_NAME_LENGTH];
    float valor;
    int qntPedido;
};

struct Produto
{
    char nome[MAX_NAME_LENGTH];
    float valor;
    int estoque;
    char nomePedido[MAX_NAME_LENGTH];
};

struct Usuario
{
    struct ItemCarrinho carrinho[MAX_CART_ITEMS];
    char nome[MAX_NAME_LENGTH];
    char senha[50];
    int tipo;
    int ID;
};

// Funções relacionadas aos usuários comuns
void salvarUsuarios(struct Usuario usuario[MAX_USERS], int cont);
void salvarEstoque(struct Produto produto[MAX_PRODUCTS], int cont);
int adicionarAoCarrinho(struct Usuario usuario[MAX_USERS], struct Produto produto[MAX_PRODUCTS], int *contCarrinho, int produtoIndex, int qnt, int estoqueAtualizado);
void removerDoCarrinho(struct Usuario usuario[MAX_USERS], int *contCarrinho, char *nome);
void exibirCarrinho(struct Usuario usuario[MAX_USERS], int contCarrinho);
void exibirComprovante(struct Usuario usuario[MAX_USERS], int contCarrinho, int usrIndex);
void salvarPedidos(struct Usuario usuario[MAX_USERS], int contCarrinho, int usrIndex);
void fazerPedido(struct Produto produto[MAX_PRODUCTS], struct Usuario usuario[MAX_USERS], int cont, int contUsr);
void carrinhoDeCompras(struct Produto produto[MAX_PRODUCTS], char nomeProduto[MAX_NAME_LENGTH], int qnt, int opcaoCarrinho, int cont);
int verificarEntrada(char *nome);

// Funções relacionadas aos adimnistradores
void criarUsuarioComum(struct Usuario usuario[MAX_USERS], int cont);
void criarAdm(struct Usuario usuario[MAX_USERS], int cont);
int adicionarProduto(struct Produto produto[MAX_PRODUCTS], int cont);
int removerProduto(struct Produto produto[MAX_PRODUCTS], int cont);
int adicionarUsuario(struct Usuario usuario[MAX_USERS], int cont);
void listarUsuarios(struct Usuario usuario[MAX_USERS], int cont);
int removerUsuario(struct Usuario usuario[MAX_USERS], int idUserAtual, int cont);
void listarProdutos(struct Produto produto[MAX_PRODUCTS], int cont);

#endif