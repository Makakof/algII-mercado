#ifndef LISTAS_H
#define LISTAS_H
#include "produto.h"

void insereEmOrdem(Produto **lista,int codigo,char descricao[],int quantidade,float preco);
void mostraLista(Produto *lista);
void excluiProduto(Produto **lista, int codigo);
void atualizaProduto(Produto **listadeProdutos, char parametro[],int codigo, float valor);
int contaListaProdutos(Produto *listadeProdutos);
Produto *buscaProduto(Produto *listadeProdutos,int codigo);
void insereNoInicio(Produto **listadeVenda, Produto *novo);
int consultarProdutos(Produto *listadeProdutos,char nome[]);
void exibeConsultaProdutos(Produto *listadeProdutos,char nome[]);
void relatorioDeProdutos(Produto *listadeProdutos);
void insereEmOrdemQuantidade(Produto *listadeProdutos,Produto **listaDeReposicao, Produto *produto);
void geraListaReposicao(Produto *listadeProdutos, Produto **listaDeReposicao);
int validaCodigo(Produto *lista, int codigo);
void totalDeVenda(float *total, Produto *produto);

#endif