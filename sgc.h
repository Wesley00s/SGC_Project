#ifndef LIB_H
#define LIB_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX 100

void limparBuffer();

struct ItemCarrinho
{
    char nome[MAX];
    float valor;
    int qntPedido;
};

struct Produto
{
    char nome[MAX];
    float valor;
    int estoque;
    char nomePedido[MAX];
};

struct Usuario
{
    struct ItemCarrinho carrinho[MAX];
    char nome[MAX];
    char senha[50];
    int tipo;
    int ID;
};

// Funções relacionadas aos usuários comuns
void salvarUsuarios(struct Usuario usuario[MAX], int cont);
void salvarEstoque(struct Produto produto[MAX], int cont);
int adicionarAoCarrinho(struct Usuario usuario[MAX], struct Produto produto[MAX], int *contCarrinho, int produtoIndex, int qnt, int estoqueAtualizado);
void removerDoCarrinho(struct Usuario usuario[MAX], int *contCarrinho, char *nome);
void exibirCarrinho(struct Usuario usuario[MAX], int contCarrinho);
void exibirComprovante(struct Usuario usuario[MAX], int contCarrinho, int usrIndex);
void salvarPedidos(struct Usuario usuario[MAX], int contCarrinho, int usrIndex);
void fazerPedido(struct Produto produto[MAX], struct Usuario usuario[MAX], int cont, int contUsr);
void carrinhoDeCompras(struct Produto produto[MAX], char nomeProduto[MAX], int qnt, int opcaoCarrinho, int cont);
int verificarEntrada(char *nome);

// Funções relacionadas aos adimnistradores
void criarUsuarioComum(struct Usuario usuario[MAX], int cont);
void criarAdm(struct Usuario usuario[MAX], int cont);
int adicionarProduto(struct Produto produto[MAX], int cont);
int removerProduto(struct Produto produto[MAX], int cont);
int adicionarUsuario(struct Usuario usuario[MAX], int cont);
void listarUsuarios(struct Usuario usuario[MAX], int cont);
int removerUsuario(struct Usuario usuario[MAX], int idUserAtual, int cont);
void listarProdutos(struct Produto produto[MAX], int cont);

#endif