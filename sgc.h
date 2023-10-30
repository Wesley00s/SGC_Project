#ifndef LIB_H
#define LIB_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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
    int qntPedido;
    int estoque;
    char nomePedido[MAX];
};

struct Usuario
{
    char nome[MAX];
    char senha[10];
    int tipo;
    int ID;
};

void adicionarAoCarrinho(struct ItemCarrinho carrinho[MAX], struct Produto produto[MAX], int *contCarrinho, int produtoIndex, int qnt);
void exibirCarrinho(struct ItemCarrinho carrinho[MAX], int contCarrinho, struct Usuario usuario[MAX], int usrIndex);
void salvarUsuarios(struct Usuario usuario[MAX], int cont);
void salvarEstoque(struct Produto produto[MAX], int cont);
void salvarPedidos(struct ItemCarrinho carrinho[MAX], int contCarrinho, struct Usuario usuario[MAX], int usrIndex);

void adicionarProduto(struct Produto produto[MAX], int cont);
void removerProduto(struct Produto produto[MAX], int cont);
void adicionarUsuario(struct Usuario usuario[MAX], int cont);
void listarUsuarios(struct Usuario usuario[MAX], int cont);
void removerUsuario(struct Usuario usuario[MAX], int cont);
void listarProdutos(struct Produto produto[MAX], int cont);
void fazerPedido(struct Produto produto[MAX], struct Usuario usuario[MAX], int cont, int contUsr);
void carrinhoDeCompras(struct Produto produto[MAX], char nomeProduto[MAX], int qnt, int opcaoCarrinho, int cont);

#endif