#include <stdio.h>
#include <stdlib.h>
#include "arquivos.h"
#include "listas.h"
#include "produto.h"

int importaProdutosTxt(Produto **lista,char nome[30],int *contaProdutos)
{
    FILE *arquivo;
    int codigo, quantidade, produtosTotais, i;
    float preco;
    char descricao[30];

    arquivo = fopen(nome, "r");
    if(arquivo == NULL)
        return 0;
    
    fscanf(arquivo,"%d",&produtosTotais);
    for(i = 0;i < produtosTotais;i++)
    {
        fscanf(arquivo,"%d;%[^;];%d;%f",&codigo,descricao,&quantidade,&preco);
        if(validaCodigo(*lista,codigo))
        {
            insereEmOrdem(lista,codigo,descricao,quantidade,preco);
            (*contaProdutos)++;
        }
        else
            printf("Codigo %d ja esta em uso\n");
    }
    fclose(arquivo);

    return produtosTotais;
}

int carregaProdutosDat(Produto **listadeProdutos)
{
    FILE *arquivo;
    Produto *novo;
    int quantidadeProdutos = 0, i;
    arquivo = fopen("Produtos.dat","rb");
    fread(&quantidadeProdutos, sizeof(int), 1, arquivo);
    for(i = 0;i < quantidadeProdutos;i++)
    {
        novo = (Produto *) malloc(sizeof(Produto));
        if(novo == NULL)
        {
            salvaProdutosDat(*listadeProdutos);
            exit(1);
        }
        fread(novo, sizeof(Produto), 1, arquivo);
        insereEmOrdem(listadeProdutos,novo->codigo,novo->descricao,novo->quantidade,novo->preco);
    }
    fclose(arquivo);
    return quantidadeProdutos;
}

void salvaProdutosDat(Produto *listadeProdutos)
{
    FILE *arquivo;
    Produto *q;
    int quantidadeProdutos;
    
    quantidadeProdutos = contaListaProdutos(listadeProdutos);
    q = listadeProdutos;
    arquivo = fopen("Produtos.dat","wb");
    fwrite(&quantidadeProdutos, sizeof(int), 1, arquivo);
    while(q != NULL)
    {
        fwrite(q, sizeof(Produto), 1, arquivo);
        q = q->prox;
    }
    fclose(arquivo);
}

void geraCompraTxt(Produto *listaDeReposicao)
{
    FILE *arquivo;
    Produto *q;
    q = listaDeReposicao;
    arquivo = fopen("Comprar.txt","w");
    while(q != NULL)
    {
        fprintf(arquivo,"%d;%s;%d\n",q->codigo,q->descricao,q->quantidade);
        q = q->prox;
    }
    fclose(arquivo);
}

void help(char nome[30])
{
    FILE *arquivo;
    char c;
    arquivo = fopen(nome,"r");
    while(c != EOF)
    {
        c = fgetc(arquivo);
        printf("%c",c);
    }
    printf("\n");
    fclose(arquivo);
}