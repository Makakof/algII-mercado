#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "listas.h"
#include "produto.h"
#include "arquivos.h"
#define alfabeto "ABCDEFGHIJKLMNOPQRSTUVXYWZ\0";


void insereEmOrdem(Produto **lista,int codigo,char descricao[],int quantidade,float preco)
{
    Produto *q,*p,*novo;
    q = *lista;
    p = NULL;

    novo = (Produto *) malloc(sizeof (Produto));
    if(novo == NULL)
    {
        salvaProdutosDat(q);
        exit(1);
    }
    novo->codigo = codigo;
    strcpy(novo->descricao,descricao);
    novo->quantidade = quantidade;
    novo->preco = preco;
    novo->prox = NULL;

    while(q != NULL && strcmp(descricao,q->descricao) > 0)
    {
        p = q;
        q = q->prox;
    }
    novo->prox = q;
    if(p == NULL)
        *lista = novo;
    else
    {
        p->prox = novo;
    }
}

void mostraLista(Produto *lista)
{
    Produto *q;
    printf("\n");
    for(q = lista;q != NULL;q = q->prox)
        printf("%d - %s - %d - %0.2f\n",q->codigo,q->descricao,q->quantidade,q->preco);
    printf("\n");
}

void excluiProduto(Produto **lista, int codigo)
{
    Produto *q,*p;
    q = *lista;
    p = NULL;

    while(q != NULL && q->codigo != codigo)
    {
        p = q;
        q = q->prox;
    }
    if(q != NULL)
    {
        if(p != NULL)
            p->prox = q->prox;
        else
            *lista = q->prox;
        free(q);
    }
}

void atualizaProduto(Produto **listadeProdutos, char parametro[],int codigo, float valor)
{
    Produto *q;
    q = *listadeProdutos;

    while(q != NULL && q->codigo != codigo)
        q = q->prox;

    if(strcmp("-q",parametro) == 0)
        q->quantidade = (int)valor;
    else
        q->preco = valor;
}

int contaListaProdutos(Produto *listadeProdutos)
{
    int cont = 0;
    Produto *p;

    p = listadeProdutos;
    if(p == NULL)
        return 0;
    else
    {
        while (p != NULL)
        {
            cont++;
            p = p->prox;
        }
    }
    return cont;
}

Produto *buscaProduto(Produto *listadeProdutos,int codigo)
{
    Produto *q;

    q = listadeProdutos;
    while(q != NULL && q->codigo != codigo)
        q = q->prox;
    
    return q;
}

void insereNoInicio(Produto **listadeVenda, Produto *novo)
{
    Produto *q;
    q = *listadeVenda;

    if(*listadeVenda == NULL)
        *listadeVenda = novo;
    else
    {
        novo->prox = q;
        *listadeVenda = novo;        
    }
}

int consultarProdutos(Produto *listadeProdutos,char nome[])
{
    Produto *q;
    char *verifica;

    q = listadeProdutos;
    if(q == NULL)
        return 0;
    else
    {
        while(q != NULL)
        {
            verifica = strstr(q->descricao,nome);
            if(verifica != NULL)
                return 1;
            q = q->prox;
        }
        return 0;
    }
}

void exibeConsultaProdutos(Produto *listadeProdutos,char nome[])
{
    Produto *q;
    char *verifica;
    q = listadeProdutos;

    while(q != NULL)
    {
        verifica = strstr(q->descricao,nome);
        if(verifica != NULL)
            printf("%d - %s - %d - %0.2f \n",q->codigo,q->descricao,q->quantidade,q->preco);
        q = q->prox;
    }
}

void relatorioDeProdutos(Produto *listadeProdutos)
{
    Produto *q;
    char *p;
    p = alfabeto;
    q = listadeProdutos;
    while(q != NULL && *p <= 'Z')
    {
        printf("%c\n",*p);
        while(q != NULL && q->descricao[0] == *p)
        {
            printf("\t%d - %s - %d - %0.2f\n",q->codigo,q->descricao,q->quantidade,q->preco);
            q = q->prox;
        }
        while(q != NULL && *p != q->descricao[0])
            p++;
    }
}

void insereEmOrdemQuantidade(Produto *listadeProdutos,Produto **listaDeReposicao, Produto *produto)
{
    Produto *q,*p, *novo;
    p = NULL;
    
    novo = (Produto *) malloc(sizeof(Produto));
    if(novo == NULL)
    {
        salvaProdutosDat(listadeProdutos);
        exit(1);
    }
    novo->codigo = produto->codigo;
    strcpy(novo->descricao,produto->descricao);
    novo->quantidade = produto->quantidade;
    novo->preco = produto->preco;

    q = *listaDeReposicao;
    while(q != NULL && q->quantidade < novo->quantidade)
    {
        p = q;
        q = q->prox;
    }
    novo->prox = q;
    if(p == NULL)
        *listaDeReposicao = novo;
    else
        p->prox = novo;
}

void geraListaReposicao(Produto *listadeProdutos, Produto **listaDeReposicao)
{
    Produto *q;
    
    q = listadeProdutos;
    while(q != NULL)
    {
        if(q->quantidade < 15)
            insereEmOrdemQuantidade(listadeProdutos,listaDeReposicao,q);
        q = q->prox;
    }
}

int validaCodigo(Produto *lista, int codigo)
{
    Produto *q;
    q = lista;

    if (codigo <= 0)
        return 0;
    else
    {
        while (q != NULL)
        {
            if (q->codigo == codigo)
                return 0;
            q = q->prox;
        }
        return 1;
    }
}

void totalDeVenda(float *total, Produto *produto)
{
    *total = *total + produto->preco;
    produto->quantidade = produto->quantidade - 1;
}