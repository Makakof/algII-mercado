#ifndef ARQUIVOS_H
#define ARQUIVOS_H
#include "produto.h"

int importaProdutosTxt(Produto **lista,char nome[30],int *contaProdutos);
int carregaProdutosDat(Produto **listadeProdutos);
void salvaProdutosDat(Produto *listadeProdutos);
void geraCompraTxt(Produto *listaDeReposicao);
void help(char nome[30]);

#endif