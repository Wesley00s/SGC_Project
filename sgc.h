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
    int estoque;
    char nomePedido[MAX];
};

struct Usuario
{
    char nome[MAX];
    char senha[50];
    int tipo;
    int ID;
};

struct Caixa
{
    int numVendas;
    float totalEmCaixa;
};

void opcaoCompra(struct ItemCarrinho carrinho[MAX], struct Produto produto[MAX], struct Usuario usuario[MAX], int opcaoContinue, int contPedidos, int cont, int contCarrinho, int usuarioEncontrado);
void salvarUsuarios(struct Usuario usuario[MAX], int cont);
void salvarEstoque(struct Produto produto[MAX], int cont);
void adicionarAoCarrinho(struct ItemCarrinho carrinho[MAX], struct Produto produto[MAX], int *contCarrinho, int produtoIndex, int qnt);
void removerDoCarrinho(struct ItemCarrinho carrinho[MAX], int *contCarrinho, char *nome);
void exibirCarrinho(struct ItemCarrinho carrinho[MAX], int contCarrinho);
void exibirComprovante(struct ItemCarrinho carrinho[MAX], int contCarrinho, struct Usuario usuario[MAX], int usrIndex);
void salvarPedidos(struct ItemCarrinho carrinho[MAX], int contCarrinho, struct Usuario usuario[MAX], int usrIndex);

void criarUsuarioComum(struct Usuario usuario[MAX], int cont);
void criarAdm(struct Usuario usuario[MAX], int cont);
void adicionarProduto(struct Produto produto[MAX], int cont);
void removerProduto(struct Produto produto[MAX], int cont);
void adicionarUsuario(struct Usuario usuario[MAX], int cont);
void listarUsuarios(struct Usuario usuario[MAX], int cont);
void removerUsuario(struct Usuario usuario[MAX], int cont);
void listarProdutos(struct Produto produto[MAX], int cont);
void fazerPedido(struct Produto produto[MAX], struct Usuario usuario[MAX], struct ItemCarrinho carrinho[MAX], int cont, int contUsr);
void carrinhoDeCompras(struct Produto produto[MAX], char nomeProduto[MAX], int qnt, int opcaoCarrinho, int cont);

#endif