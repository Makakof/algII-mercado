#ifndef PRODUTO_H
#define PRODUTO_H

typedef struct Produto
{
    int codigo;
    char descricao[30];
    int quantidade;
    float preco;
    struct Produto *prox;
}Produto;

#endif